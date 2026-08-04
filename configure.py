#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    Platform,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "G5SE7D",    # 0 - GameCube PAL
    "PS2",  # 1 - PS2 PAL
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.compilers_tag = "20251015"

if version_num in [0]:
    config.platform = Platform.GC_WII
    config.dtk_tag = "v1.8.3"
    config.binutils_tag = "2.42-1"
elif version_num in [1]:
    config.platform = Platform.PS2
    config.binutils_tag = "2.45"

config.objdiff_tag = "v3.7.0"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "1.0.0"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"

if config.platform == Platform.GC_WII:
    config.asflags = [
        "-mgekko",
        "--strip-local-absolute",
        "-I include"
        "-I include/GC",
        f"-I build/{config.version}/include",
        f"--defsym BUILD_VERSION={version_num}",
    ]

    ldscript_path = Path("config") / config.version / "ldscript.ld"
    config.ldflags = ["-T", str(ldscript_path)]

    # Optional numeric ID for decomp.me preset
    # Can be overridden in libraries or objects
    config.scratch_preset_id = None
elif config.platform == Platform.PS2:
    config.asflags = [
        "-no-pad-sections",
        "-EL",
        "-march=5900",
        "-mabi=eabi",
        "-I include",
        "-I include/PS2",
    ]
    ldscript_path = Path("build") / config.version / "ldscript.ld"
    config.ldflags = [
        "-EL",
        "-T",
        str(ldscript_path),
    ]  # TODO what about undefined_syms_auto.txt?

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
if config.platform == Platform.GC_WII:
    config.linker_version = "ProDG/3.9.3"

    cflags_base_mwcc = [
        "-nodefaults",
        "-proc gekko",
        "-align powerpc",
        "-enum int",
        "-fp hardware",
        "-Cpp_exceptions off",
        # "-W all",
        "-O4,p",
        "-inline auto",
        '-pragma "cats off"',
        '-pragma "warn_notinlined off"',
        "-maxerrors 1",
        "-nosyspath",
        "-RTTI off",
        "-fp_contract on",
        "-str reuse",
        "-i include/GC",
        "-i include/GC/libc",
        "-ir src/Gamecube/dolphin",
        "-DGEKKO",
        "-D__GEKKO__",
        f"-i build/{config.version}/include",
        "-multibyte",
        f"-DVERSION={version_num}",
    ]

    # TODO move some of these to the game flags
    cflags_base_prodg = [
        "-O2",
        "-gdwarf",
        # "-lang=cplusplus",
        # "-Wa,-L",
        # "-Wall",
        # "-Wreturn-type", # enable at some point
        "-Wno-ctor-dtor-privacy",  # because of AttribSys for example
        "-Woverloaded-virtual",
        "-I include/GC",
        "-I ./",
        "-I include/GC/Spyro/Code",
        "-I src",
        "-DEA_PLATFORM_GAMECUBE",
        "-DEA_REGION_AMERICA",
        "-D__GEKKO__",
        "-D_USE_MATH_DEFINES",
        f"-I build/{config.version}/include",
        f"-DBUILD_VERSION={version_num}",
        f"-DVERSION_{config.version}",
    ]

    config.context_defines = [
        "EA_PLATFORM_GAMECUBE",
        "EA_REGION_AMERICA",
        "GEKKO",
        "_USE_MATH_DEFINES",
        "__SN__",
        "SN_TARGET_NGC",
    ]

    # Debug flags
    if args.debug:
        cflags_base_prodg.append("-DDEBUG=1")
    else:
        cflags_base_prodg.append("-DNDEBUG=1")

    cflags_game = [
        *cflags_base_prodg,
        # "-mps-nodf",
        # "-mfast-cast",
        "-G4",
        # "-fnew-abi",
        "-ffast-math",
        "-fno-common",
        "-fvtable-thunks",
        # "-fno-vtable-thunks",
        # "-DWRITABLE_VTABLES",
        # "-fno-strength-reduce",
        # "-fforce-addr",
        "-fcse-follow-jumps",
        "-fcse-skip-blocks",
        "-fforce-mem",
        "-fgcse",
        "-frerun-cse-after-loop",
        "-fschedule-insns",
        "-fschedule-insns2",
        "-fexpensive-optimizations",
        "-frerun-loop-opt",
        "-fmove-all-movables",
        # "-fno-defer-pop",
        # "-fno-function-cse",
        # "-fpeephole",
        # "-fregmove",
        # "-fno-thread-jumps",
        # "-freduce-all-givs",
        # "-fcaller-saves",
        # "-ffloat-store",
        # "-funroll-all-loops",
        "-DLUA_NUMBER=float",
    ]

    config.extra_clang_flags = [
        "-std=gnu++98",
        "-DSN_TARGET_NGC",
        "-D__SN__",
        "-D_STLP_VENDOR_EXCEPT_STD=std",
        "-DCLANGD_DAMNIT",  # used in cases where intellisense breaks
    ]

    cflags_dolphin = [*cflags_base_mwcc]

    # Metrowerks library flags
    cflags_runtime = [*cflags_base_mwcc]

    cflags_odemuexi = [*cflags_base_mwcc]

    cflags_amcstub = [*cflags_base_mwcc]

    # Helper function for Dolphin libraries
    def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
        return {
            "lib": lib_name,
            "src_dir": "src/Gamecube",
            "toolchain_version": "GC/1.2.5n",
            "cflags": cflags_dolphin,
            "progress_category": "dsdk",
            "objects": objects,
        }

elif config.platform == Platform.PS2:
    config.linker_version = "PS2/ee-gcc2.9-991111"

    cflags_base_prodg = [
        "-O2",
        "-g2",
        "-Wno-ctor-dtor-privacy",  # because of AttribSys for example
        "-Woverloaded-virtual",
        # "-Wall",
        "-I include",
        "-I include/Spyro/Code",
        "-I src/Packages",
        "-I src",
        "-DEA_PLATFORM_PLAYSTATION2",
        "-DEA_BUILD_A124",
        "-D_NOTHREADS",  # TODO is this necessary?
        f"-I build/{config.version}/include",
        f"-DBUILD_VERSION={version_num}",
        # f"-DVERSION_{config.version}", # TODO it's broken because of the dash?
    ]

    config.context_defines = [
        "EA_PLATFORM_PLAYSTATION2",
        "EA_REGION_AMERICA",
        "EA_BUILD_A124",
        "_NOTHREADS",
    ]

    # Debug flags
    # TODO
    # if args.debug:
    # cflags_base.append("-DDEBUG=1")
    # else:
    #     cflags_base.append("-DNDEBUG=1")

    cflags_game = [
        *cflags_base_prodg,
        "-G0",
        "-ffast-math",
        "-fno-exceptions",
        "-fno-rtti",
        # "-funaligned-pointers",
        # "-funaligned-struct-hack",
        # "-fsched-interblock",
        # "-fsched-spec",
        # "-fsched-spec-load-dangerous",
        # "-fedge-sm",
        # "-fedge-lm",
        # "-fedge-lcm",
        # "-fforce-addr",
        # "-fcse-follow-jumps",
        # "-fcse-skip-blocks",
        # "-fforce-mem",
        # "-fgcse",
        # "-fstrength-reduce",
        # "-frerun-cse-after-loop",
        # "-fschedule-insns",
        # "-fschedule-insns2",
        # "-fexpensive-optimizations",
        # "-frerun-loop-opt",
        # "-fmove-all-movables",
        # "-fregmove",
        # "-fcaller-saves",
        "-DLUA_NUMBER=float",
        "-DMILESTONE_OPT",
    ]

    config.extra_clang_flags = [
        "-std=gnu++98",
    ]

cflags_cmn = [
    *cflags_game,
    #    "-x c++"
]

cflags_libc = [*cflags_base_prodg]

Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


if config.platform != Platform.PS2:
    config.warn_missing_config = True

config.warn_missing_source = False

# PS2: auto-download ee-gcc2.9-991111 into build/compilers/PS2/ as a pre-compile step
if config.platform == Platform.PS2:
    ps2_cc_path = config.build_dir / "compilers" / "PS2" / "ee-gcc2.9-991111"
    config.custom_build_rules = [
        {
            "name": "download_ps2_cc",
            "command": "$python tools/download_tool.py ps2_compilers $out --tag ee-gcc2.9-991111",
            "description": "TOOL $out",
        }
    ]
    config.custom_build_steps = {
        "pre-compile": [
            {
                "outputs": str(ps2_cc_path),
                "rule": "download_ps2_cc",
                "implicit": "tools/download_tool.py",
            }
        ]
    }

config.libs = []

if config.platform == Platform.GC_WII:
    config.libs.extend(
        [
            {
                "lib": "libsn",
                "src_dir": "src/Gamecube",
                "toolchain_version": config.linker_version,
                "cflags": cflags_base_prodg,
                "host": False,
                "progress_category": "libs",  # str | List[str]
                "objects": [
                    Object(NonMatching, "prodg_fixes.cpp"),
                    Object(NonMatching, "sn/SNDebug.cpp"),
                    Object(NonMatching, "sn/PCSerial.c"),
                    Object(NonMatching, "sn/SNInitEXI2TCHandler.c"),
                    Object(NonMatching, "sn/SNDVDEmu.c"),
                    Object(NonMatching, "sn/SNSerial.c"),
                ],
            },
            {
                "lib": "math",
                "src_dir": "src/Gamecube",
                "toolchain_version": config.linker_version,
                "cflags": cflags_base_prodg,
                "host": False,
                "progress_category": "libc",  # str | List[str]
                "objects": [
                    Object(NonMatching, "math/acosf.c"),
                    Object(NonMatching, "math/asinf.c"),
                    Object(NonMatching, "math/atan2f.c"),
                    Object(NonMatching, "math/fmodf.c"),
                    Object(NonMatching, "math/powf.c"),
                    Object(NonMatching, "math/sqrtf.c"),
                    Object(NonMatching, "math/atanf.c"),
                    Object(NonMatching, "math/ceilf.c"),
                    Object(NonMatching, "math/cosf.c"),
                    Object(NonMatching, "math/fabsf.c"),
                    Object(NonMatching, "math/floorf.c"),
                    Object(NonMatching, "math/sinf.c"),
                    Object(NonMatching, "math/tanf.c"),
                    Object(NonMatching, "math/scalbnf.c"),
                    Object(NonMatching, "math/kernel_cosf.c"),
                    Object(NonMatching, "math/kernel_sinf.c"),
                    Object(NonMatching, "math/kernel_tanf.c"),
                    Object(NonMatching, "math/rem_pio2f.c"),
                    Object(NonMatching, "math/copysignf.c"),
                    Object(NonMatching, "math/kernel_rem_pio2f.c"),
                    Object(NonMatching, "math/pow.c"),
                    Object(NonMatching, "math/sqrt.c"),
                    Object(NonMatching, "math/fabs.c"),
                    Object(NonMatching, "math/sin.c"),
                    Object(NonMatching, "math/scalbn.c"),
                    Object(NonMatching, "math/kernel_cos.c"),
                    Object(NonMatching, "math/kernel_sin.c"),
                    Object(NonMatching, "math/ieee754_rem_pio2.c"),
                    Object(NonMatching, "math/copysign.c"),
                    Object(NonMatching, "math/kernel_rem_pio2.c"),
                    Object(NonMatching, "math/floor.c"),
                ],
            },
            {
                "lib": "gcc",
                "src_dir": "src/Gamecube",
                "toolchain_version": config.linker_version,
                "cflags": cflags_base_prodg,
                "host": False,
                "progress_category": "libs",  # str | List[str]
                "objects": [
                    Object(NonMatching, "gcc/ashldi3.c"),
                    Object(NonMatching, "gcc/ashrdi3.c"),
                    Object(NonMatching, "gcc/divdi3.c"),
                    Object(NonMatching, "gcc/lshrdi3.c"),
                    Object(NonMatching, "gcc/moddi3.c"),
                    Object(NonMatching, "gcc/pure_virtual.c"),
                    Object(NonMatching, "gcc/udivdi3.c"),
                    Object(NonMatching, "gcc/umoddi3.c"),
                    Object(NonMatching, "gcc/terminate.c"),
                    Object(NonMatching, "gcc/do_global_ctors.c"),
                    Object(NonMatching, "gcc/main.c"),
                    Object(NonMatching, "gcc/cmpdi2.c"),
                    Object(NonMatching, "gcc/floatdidf.c"),
                    Object(NonMatching, "gcc/floatdisf.c"),
                    Object(NonMatching, "gcc/ucmpdi2.c"),
                ],
            },
            {
                "lib": "ppc",
                "src_dir": "src/Gamecube",
                "toolchain_version": config.linker_version,
                "cflags": cflags_base_prodg,
                "host": False,
                "progress_category": "libs",  # str | List[str]
                "objects": [
                    Object(NonMatching, "ppc/PPCArch.c"),
                ],
            },
            {
                "lib": "Spyro",
                "src_dir": "src/Gamecube",
                "src_dir": "src",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "game",  # str | List[str]
                "objects": [
                    Object(NonMatching, "Spyro/Code/BASIC_System/BASIC_Interpret.cpp"),
                    Object(NonMatching, "Spyro/Code/BASIC_System/BASIC_InterpretInterfaceLayer.cpp"),
                    Object(NonMatching, "Spyro/Code/BASIC_System/BASIC_InterpretPrivate.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/SETrigger_Default.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/StartPoint.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/Trigger_Special.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItem/XSEItem_Default.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/BallGadget/Player_BallGadget.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Ember/Player_Ember.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Flame/Player_Flame.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Sparx/Player_Sparx.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Blinky/PreBlinky.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Bosses/PreBosses.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Hunter/PreHunter.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/PrePlayer.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/SgtBird/PreSgtBird.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Spyro/PreSpyro.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/PreSXEItemHandler.cpp"),
                    Object(NonMatching, "Spyro/Code/Camera/PreCamera.cpp"),
                    Object(NonMatching, "Spyro/Code/PreCode.cpp"),
                    Object(NonMatching, "Spyro/Code/Generic/PreGeneric.cpp"),
                    Object(NonMatching, "Spyro/Code/GUI/PreGUI.cpp"),
                    Object(NonMatching, "Spyro/Code/Levels/PreLevels.cpp"),
                    Object(NonMatching, "Spyro/Code/Levels/MiniGames/PreMiniGames.cpp"),
                    Object(NonMatching, "Spyro/Code/Panel/PrePanel.cpp"),
                    Object(NonMatching, "Spyro/Code/SE/PreSE.cpp"),
                    Object(NonMatching, "Spyro/Code/Support/PreSupport.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/TriggerList.cpp"),
                ],
            },
            {
                "lib": "EngineX",
                "src_dir": "src/Gamecube",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "engX",  # str | List[str]
                "objects": [
                    Object(NonMatching, "EngineX/EXAnimCache.cpp"),
                    Object(NonMatching, "EngineX/EXApp.cpp"),
                    Object(NonMatching, "EngineX/EXBounds.cpp"),
                    Object(NonMatching, "EngineX/EXCamera.cpp"),
                    Object(NonMatching, "EngineX/EXCollision.cpp"),
                    Object(NonMatching, "EngineX/EXCollisionTypes.cpp"),
                    Object(NonMatching, "EngineX/EXDatum.cpp"),
                    Object(NonMatching, "EngineX/EXDebugTree.cpp"),
                    Object(NonMatching, "EngineX/EXDebugTreeWnd.cpp"),
                    Object(NonMatching, "EngineX/EXDebugWnd.cpp"),
                    Object(NonMatching, "EngineX/EXDisplay.cpp", extra_cflags=["-G8"]),
                    Object(NonMatching, "EngineX/EXDistance.cpp"),
                    Object(NonMatching, "EngineX/EXFile.cpp"),
                    Object(NonMatching, "EngineX/EXFileSys.cpp"),
                    Object(NonMatching, "EngineX/EXGamepad.cpp"),
                    Object(NonMatching, "EngineX/EXGeoAnim.cpp"),
                    Object(NonMatching, "EngineX/EXGeoCommon.cpp"),
                    Object(NonMatching, "EngineX/EXGeoEntity_NavMesh.cpp"),
                    Object(NonMatching, "EngineX/EXGeoEntity.cpp"),
                    Object(NonMatching, "EngineX/EXGeoFace.cpp"),
                    Object(NonMatching, "EngineX/EXGeoFile.cpp"),
                    Object(NonMatching, "EngineX/EXGeoGrabpoint.cpp"),
                    Object(NonMatching, "EngineX/EXGeoInstance.cpp"),
                    Object(NonMatching, "EngineX/EXGeoMap.cpp"),
                    Object(NonMatching, "EngineX/EXGeoParticle.cpp"),
                    Object(NonMatching, "EngineX/EXGeoScript.cpp"),
                    Object(Matching, "EngineX/EXGeoSpreadSheet.cpp"),
                    Object(NonMatching, "EngineX/EXGeoTexture.cpp"),
                    Object(NonMatching, "EngineX/EXGeoViewer.cpp"),
                    Object(Matching, "EngineX/EXHashcode.cpp"),
                    Object(NonMatching, "EngineX/EXIntersection.cpp"),
                    Object(NonMatching, "EngineX/EXItem.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Anim.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_AnimModifier.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Camera.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Collision.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_DynLight.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Entity.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Map.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Particle.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Script.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_ScriptControllers.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Sound.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator.cpp"),
                    Object(NonMatching, "EngineX/EXItemCtrl_Anim.cpp"),
                    Object(NonMatching, "EngineX/EXItemCtrl_AnimModifier.cpp"),
                    Object(NonMatching, "EngineX/EXItemCtrl.cpp"),
                    Object(NonMatching, "EngineX/EXItemEnv.cpp"),
                    Object(NonMatching, "EngineX/EXItemHandler.cpp"),
                    Object(NonMatching, "EngineX/EXItemPhysics.cpp"),
                    Object(NonMatching, "EngineX/EXItemRender_Anim.cpp"),
                    Object(NonMatching, "EngineX/EXItemRender_Entity.cpp"),
                    Object(NonMatching, "EngineX/EXItemRender.cpp"),
                    Object(NonMatching, "EngineX/EXLightManager.cpp"),
                    Object(NonMatching, "EngineX/EXLine.cpp"),
                    Object(Matching, "EngineX/EXList.cpp"),
                    Object(NonMatching, "EngineX/EXMalloc.cpp"),
                    Object(NonMatching, "EngineX/EXMaths.cpp"),
                    Object(NonMatching, "EngineX/EXMatrix.cpp"),
                    Object(NonMatching, "EngineX/EXMemCard.cpp"),
                    Object(NonMatching, "EngineX/EXMemoryManager.cpp"),
                    Object(NonMatching, "EngineX/EXMenu.cpp"),
                    Object(NonMatching, "EngineX/EXParticle.cpp"),
                    Object(NonMatching, "EngineX/EXParticleEmitter.cpp"),
                    Object(NonMatching, "EngineX/EXRand.cpp"),
                    Object(NonMatching, "EngineX/EXRect.cpp"),
                    Object(NonMatching, "EngineX/EXRenderEnv.cpp"),
                    Object(NonMatching, "EngineX/EXResourceWnd.cpp"),
                    Object(NonMatching, "EngineX/EXScratchPad.cpp"),
                    Object(NonMatching, "EngineX/EXSoundManager.cpp"),
                    Object(NonMatching, "EngineX/EXStateSaver.cpp"),
                    Object(NonMatching, "EngineX/EXStats.cpp"),
                    Object(NonMatching, "EngineX/EXStdFuncs.cpp"),
                    Object(NonMatching, "EngineX/EXString.cpp"),
                    Object(NonMatching, "EngineX/EXSwoosh.cpp"),
                    Object(NonMatching, "EngineX/EXTemplates.cpp"),
                    Object(NonMatching, "EngineX/EXTexture.cpp"),
                    Object(NonMatching, "EngineX/EXVector.cpp"),
                    Object(NonMatching, "EngineX/EXWatcher.cpp"),
                    Object(NonMatching, "EngineX/EXWnd.cpp"),
                    Object(NonMatching, "EngineX/EXWString.cpp"),
                    ############################################
                    #      Gamecube Specific EngineX files     #
                    ############################################
                    Object(NonMatching, "EngineX/GC/GCApp.cpp"),
                    Object(NonMatching, "EngineX/GC/GCAudio.cpp"),
                    Object(NonMatching, "EngineX/GC/GCBloom.cpp"),
                    Object(NonMatching, "EngineX/GC/GCBounds.cpp"),
                    Object(NonMatching, "EngineX/GC/GCCamera.cpp"),
                    Object(NonMatching, "EngineX/GC/GCCluster.cpp"),
                    Object(NonMatching, "EngineX/GC/GCCollision.cpp"),
                    Object(NonMatching, "EngineX/GC/GCDisplay.cpp"),
                    Object(NonMatching, "EngineX/GC/GCFastMath.cpp"),
                    Object(NonMatching, "EngineX/GC/GCFile.cpp"),
                    Object(NonMatching, "EngineX/GC/GCGamepad.cpp"),
                    Object(NonMatching, "EngineX/GC/GCGeoAnim.cpp"),
                    Object(NonMatching, "EngineX/GC/GCGeoDrawInfo.cpp"),
                    Object(NonMatching, "EngineX/GC/GCGeoEntity.cpp"),
                    Object(NonMatching, "EngineX/GC/GCItemRender.cpp"),
                    Object(NonMatching, "EngineX/GC/GCMalloc.cpp"),
                    Object(NonMatching, "EngineX/GC/GCMatrix.cpp"),
                    Object(NonMatching, "EngineX/GC/GCMemCard.cpp"),
                    Object(NonMatching, "EngineX/GC/GCParticle.cpp"),
                    Object(NonMatching, "EngineX/GC/GCPhysics.cpp"),
                    Object(NonMatching, "EngineX/GC/GCQuaternion.cpp"),
                    Object(NonMatching, "EngineX/GC/GCRenderEnv.cpp"),
                    Object(NonMatching, "EngineX/GC/GCResourceWnd.cpp"),
                    Object(NonMatching, "EngineX/GC/GCSoundManager.cpp"),
                    Object(NonMatching, "EngineX/GC/GCStats.cpp"),
                    Object(NonMatching, "EngineX/GC/GCSwoosh.cpp"),
                    Object(NonMatching, "EngineX/GC/GCTexture.cpp"),
                    Object(NonMatching, "EngineX/GC/GCVector.cpp"),
                    Object(NonMatching, "EngineX/GC/GCWnd.cpp"),
                    Object(NonMatching, "EngineX/GC/GCWndPrim.cpp"),
                    Object(NonMatching, "EngineX/GC/GCWndSprite.cpp"),
                    Object(NonMatching, "unknownFile/unknown.cpp"),
                ],
            },
            {
                "lib": "stdlib",
                "src_dir": "src/Gamecube",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "libc",  # str | List[str]
                "objects": [
                    Object(NonMatching, "stdlib/atexit.c"),
                    Object(NonMatching, "stdlib/malloc.c"),
                    Object(NonMatching, "stdlib/itoa.c"),
                    Object(NonMatching, "stdlib/vfprintf.c"),
                    Object(NonMatching, "stdlib/locale.c"),
                    Object(NonMatching, "stdlib/mbtowc.c"),
                    Object(NonMatching, "stdlib/printf.c"),
                    Object(NonMatching, "stdlib/qsort.c"),
                ],
            },
            DolphinLib(
                "os",
                [
                    Object(NonMatching, "dolphin/os/OS.c"),
                    Object(NonMatching, "dolphin/os/OSAlarm.c"),
                    Object(NonMatching, "dolphin/os/OSArena.c"),
                    Object(NonMatching, "dolphin/os/OSAudioSystem.c"),
                    Object(NonMatching, "dolphin/os/OSCache.c"),
                    Object(NonMatching, "dolphin/os/OSContext.c"),
                    Object(NonMatching, "dolphin/os/OSError.c"),
                    Object(NonMatching, "dolphin/os/OSExec.c"),
                    Object(NonMatching, "dolphin/os/OSInterrupt.c"),
                    Object(NonMatching, "dolphin/os/OSLink.c"),
                    Object(NonMatching, "dolphin/os/OSMemory.c"),
                    Object(NonMatching, "dolphin/os/OSReboot.c"),
                    Object(NonMatching, "dolphin/os/OSReset.c"),
                    Object(NonMatching, "dolphin/os/OSResetSW.c"),
                    Object(NonMatching, "dolphin/os/OSRtc.c"),
                    Object(NonMatching, "dolphin/os/OSSync.c"),
                    Object(NonMatching, "dolphin/os/OSThread.c"),
                    Object(NonMatching, "dolphin/os/OSTime.c"),
                    Object(NonMatching, "dolphin/os/__ppc_eabi_init.c"),
                    Object(NonMatching, "dolphin/os/OSMutex.c"),
                    Object(NonMatching, "dolphin/os/OSAlloc.c"),
                    Object(NonMatching, "dolphin/os/OSFont.c"),
                ],
            ),
            DolphinLib(
                "exi",
                [
                    Object(NonMatching, "dolphin/exi/EXIBios.c"),
                    Object(NonMatching, "dolphin/exi/EXIUart.c"),
                ],
            ),
            DolphinLib(
                "si",
                [
                    Object(NonMatching, "dolphin/si/SIBios.c"),
                    Object(NonMatching, "dolphin/si/SISamplingRate.c"),
                ],
            ),
            DolphinLib(
                "db",
                [
                    Object(NonMatching, "dolphin/db/DB.c"),
                ],
            ),
            DolphinLib(
                "mtx",
                [
                    Object(NonMatching, "dolphin/mtx/mtx44.c"),
                    Object(NonMatching, "dolphin/mtx/vec.c"),
                    Object(NonMatching, "dolphin/mtx/mtx.c"),
                    Object(NonMatching, "dolphin/mtx/mtxvec.c"),
                ],
            ),
            DolphinLib(
                "dvd",
                [
                    Object(NonMatching, "dolphin/dvd/dvdFs.c"),
                    Object(NonMatching, "dolphin/dvd/dvd.c"),
                    Object(NonMatching, "dolphin/dvd/dvdqueue.c"),
                    Object(NonMatching, "dolphin/dvd/dvderror.c"),
                    Object(NonMatching, "dolphin/dvd/dvdidutils.c"),
                    Object(NonMatching, "dolphin/dvd/dvdFatal.c"),
                    Object(NonMatching, "dolphin/dvd/fstload.c"),
                    Object(NonMatching, "dolphin/dvd/dvdlow.c"),
                ],
            ),
            DolphinLib(
                "vi",
                [
                    Object(NonMatching, "dolphin/vi/vi.c"),
                ],
            ),
            DolphinLib(

                "pad",
                [
                    Object(NonMatching, "dolphin/pad/pad.c"),
                ],
            ),
            DolphinLib(
                "ai",
                [
                    Object(NonMatching, "dolphin/ai/ai.c"),
                ],
            ),
            DolphinLib(
                "amc",
                [
                    Object(Matching, "dolphin/amcstubs/AmcExi2Stubs.c"),
                ],
            ),
            DolphinLib(
                "ode",
                [
                    Object(NonMatching, "dolphin/odemustubs/odemustubs.c"),
                ],
            ),
            DolphinLib(
                "ar",
                [
                    Object(NonMatching, "dolphin/ar/ar.c"),
                    Object(NonMatching, "dolphin/ar/arq.c"),
                ],
            ),
            DolphinLib(
                "ax",
                [
                    Object(NonMatching, "dolphin/ax/ax.c"),
                    Object(NonMatching, "dolphin/ax/AxAlloc.c"),
                    Object(NonMatching, "dolphin/ax/AxAux.c"),
                    Object(NonMatching, "dolphin/ax/AXCL.c"),
                    Object(NonMatching, "dolphin/ax/AXOut.c"),
                    Object(NonMatching, "dolphin/ax/AXSPB.c"),
                    Object(NonMatching, "dolphin/ax/AXVPB.c"),
                    Object(NonMatching, "dolphin/ax/AXProf.c"),
                ],
            ),
            DolphinLib(
                "axfx",
                [
                    Object(NonMatching, "dolphin/axfx/reverb_std.c"),
                ],
            ),
            DolphinLib(
                "mix",
                [
                    Object(NonMatching, "dolphin/mix/mix.c"),
                ],
            ),
            DolphinLib(
                "dsp",
                [
                    Object(NonMatching, "dolphin/dsp/dsp.c"),
                    Object(NonMatching, "dolphin/dsp/dsp_debug.c"),
                    Object(NonMatching, "dolphin/dsp/dsp_task.c"),
                ], 
            ),
            DolphinLib(
                "card",
                [
                    Object(NonMatching, "dolphin/card/CARDBios.c"),
                    Object(NonMatching, "dolphin/card/CARDBlock.c"),
                    Object(NonMatching, "dolphin/card/CARDDir.c"),
                    Object(NonMatching, "dolphin/card/CARDCheck.c"),
                    Object(NonMatching, "dolphin/card/CARDMount.c"),
                    Object(NonMatching, "dolphin/card/CARDFormat.c"),
                    Object(NonMatching, "dolphin/card/CARDOpen.c"),
                    Object(NonMatching, "dolphin/card/CARDCreate.c"),
                    Object(NonMatching, "dolphin/card/CARDRead.c"),
                    Object(NonMatching, "dolphin/card/CARDWrite.c"),
                    Object(NonMatching, "dolphin/card/CARDDelete.c"),
                    Object(NonMatching, "dolphin/card/CARDStat.c"),
                    Object(NonMatching, "dolphin/card/CARDUnlock.c"),
                    Object(NonMatching, "dolphin/card/CARDRdwr.c"),
                ],
            ),
            DolphinLib(
                "gx",
                [
                    Object(NonMatching, "dolphin/gx/GXInit.c"),
                    Object(NonMatching, "dolphin/gx/GXFifo.c"),
                    Object(NonMatching, "dolphin/gx/GXAttr.c"),
                    Object(NonMatching, "dolphin/gx/GXMisc.c"),
                    Object(NonMatching, "dolphin/gx/GXGeometry.c"),
                    Object(NonMatching, "dolphin/gx/GXFrameBuf.c"),
                    Object(NonMatching, "dolphin/gx/GXLight.c"),
                    Object(NonMatching, "dolphin/gx/GXTexture.c"),
                    Object(NonMatching, "dolphin/gx/GXBump.c"),
                    Object(NonMatching, "dolphin/gx/GXTev.c"),
                    Object(NonMatching, "dolphin/gx/GXPixel.c"),
                    Object(NonMatching, "dolphin/gx/GXDisplayList.c"),
                    Object(NonMatching, "dolphin/gx/GXTransform.c"),
                    Object(NonMatching, "dolphin/gx/GXPerf.c"),
                ],
            ),
            DolphinLib(
                "gd",
                [
                    Object(NonMatching, "dolphin/gd/GDBase.c"),
                    Object(NonMatching, "dolphin/gd/GDGeometry.c"),
                ],
            ),
        ]
    )

elif config.platform == Platform.PS2:
    config.libs.extend(
        [
            {
                "lib": "startup",
                "toolchain_version": config.linker_version,
                "cflags": cflags_libc,
                "host": False,
                "progress_category": "libs",
                "objects": [
                    Object(NonMatching, "EngineX/PS2/crt0.s"),
                ],
            },
            {
                "lib": "Spyro",
                "src_dir": "src/PS2",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "game",
                "objects": [
                    Object(NonMatching, "Spyro/Code/SE/PreSE.cpp"),
                    Object(NonMatching, "Spyro/Code/Levels/PreLevels.cpp"),
                    Object(NonMatching, "Spyro/Code/Levels/MiniGames/PreMiniGames.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItem/XSEItem_Default.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/PrePlayer.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Spyro/PreSpyro.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Hunter/PreHunter.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Blinky/PreBlinky.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/SgtBird/PreSgtBird.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Sparx/Player_Sparx.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/BallGadget/Player_BallGadget.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Ember/Player_Ember.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Player/Flame/Player_Flame.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/PreSXEItemHandler.cpp"),
                    Object(NonMatching, "Spyro/Code/XSEItemHandler/Bosses/PreBosses.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/SETrigger_Default.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/StartPoint.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/Trigger_Special.cpp"),
                    Object(NonMatching, "Spyro/Code/SETrigger/TriggerList.cpp"),
                    Object(NonMatching, "Spyro/Code/Camera/PreCamera.cpp"),
                    Object(NonMatching, "Spyro/Code/Support/PreSupport.cpp"),
                    Object(NonMatching, "Spyro/Code/Generic/PreGeneric.cpp"),
                    Object(NonMatching, "Spyro/Code/Panel/PrePanel.cpp"),
                    Object(NonMatching, "Spyro/Code/GUI/PreGUI.cpp"),
                    Object(NonMatching, "Spyro/Code/BASIC_System/BASIC_Interpret.cpp"),
                    Object(NonMatching, "Spyro/Code/BASIC_System/BASIC_InterpretInterfaceLayer.cpp"),
                    Object(NonMatching, "Spyro/Code/BASIC_System/BASIC_InterpretPrivate.cpp"),
                    Object(NonMatching, "Spyro/Code/PreCode.cpp"),
                ],
            },
            {
                "lib": "EngineX",
                "src_dir": "src/PS2",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "engX",
                "objects": [
                    Object(NonMatching, "EngineX/EXApp.cpp"),
                    Object(NonMatching, "EngineX/EXBounds.cpp"),
                    Object(NonMatching, "EngineX/EXCamera.cpp"),
                    Object(NonMatching, "EngineX/EXCollision.cpp"),
                    Object(NonMatching, "EngineX/EXCollisionTypes.cpp"),
                    Object(NonMatching, "EngineX/EXDatum.cpp"),
                    Object(NonMatching, "EngineX/EXDebugTree.cpp"),
                    Object(NonMatching, "EngineX/EXDebugTreeWnd.cpp"),
                    Object(NonMatching, "EngineX/EXDebugWnd.cpp"),
                    Object(NonMatching, "EngineX/EXDisplay.cpp"),
                    Object(NonMatching, "EngineX/EXDistance.cpp"),
                    Object(NonMatching, "EngineX/EXFile.cpp"),
                    Object(NonMatching, "EngineX/EXFileSys.cpp"),
                    Object(NonMatching, "EngineX/EXGamepad.cpp"),
                    Object(NonMatching, "EngineX/EXGeoAnim.cpp"),
                    Object(NonMatching, "EngineX/EXGeoCommon.cpp"),
                    Object(NonMatching, "EngineX/EXGeoEntity.cpp"),
                    Object(NonMatching, "EngineX/EXGeoEntity_NavMesh.cpp"),
                    Object(NonMatching, "EngineX/EXGeoFace.cpp"),
                    Object(NonMatching, "EngineX/EXGeoFile.cpp"),
                    Object(NonMatching, "EngineX/EXGeoMap.cpp"),
                    Object(NonMatching, "EngineX/EXGeoParticle.cpp"),
                    Object(NonMatching, "EngineX/EXGeoScript.cpp"),
                    Object(NonMatching, "EngineX/EXGeoSpreadSheet.cpp"),
                    Object(NonMatching, "EngineX/EXGeoViewer.cpp"),
                    Object(NonMatching, "EngineX/EXHashcode.cpp"),
                    Object(NonMatching, "EngineX/EXIntersection.cpp"),
                    Object(NonMatching, "EngineX/EXItem.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Anim.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_AnimModifier.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Camera.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Collision.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_DynLight.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Entity.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Map.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Particle.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Script.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_ScriptControllers.cpp"),
                    Object(NonMatching, "EngineX/EXItemAnimator_Sound.cpp"),
                    Object(NonMatching, "EngineX/EXItemCtrl.cpp"),
                    Object(NonMatching, "EngineX/EXItemCtrl_Anim.cpp"),
                    Object(NonMatching, "EngineX/EXItemCtrl_AnimModifier.cpp"),
                    Object(NonMatching, "EngineX/EXItemEnv.cpp"),
                    Object(NonMatching, "EngineX/EXItemHandler.cpp"),
                    Object(NonMatching, "EngineX/EXItemPhysics.cpp"),
                    Object(NonMatching, "EngineX/EXItemRender.cpp"),
                    Object(NonMatching, "EngineX/EXItemRender_Anim.cpp"),
                    Object(NonMatching, "EngineX/EXItemRender_Entity.cpp"),
                    Object(NonMatching, "EngineX/EXLightManager.cpp"),
                    Object(NonMatching, "EngineX/EXLine.cpp"),
                    Object(NonMatching, "EngineX/EXList.cpp"),
                    Object(NonMatching, "EngineX/EXMalloc.cpp"),
                    Object(NonMatching, "EngineX/EXMaths.cpp"),
                    Object(NonMatching, "EngineX/EXMatrix.cpp"),
                    Object(NonMatching, "EngineX/EXMemCard.cpp"),
                    Object(NonMatching, "EngineX/EXMemoryManager.cpp"),
                    Object(NonMatching, "EngineX/EXMenu.cpp"),
                    Object(NonMatching, "EngineX/EXParticle.cpp"),
                    Object(NonMatching, "EngineX/EXParticleEmitter.cpp"),
                    Object(NonMatching, "EngineX/EXRand.cpp"),
                    Object(NonMatching, "EngineX/EXRect.cpp"),
                    Object(NonMatching, "EngineX/EXRenderEnv.cpp"),
                    Object(NonMatching, "EngineX/EXResourceWnd.cpp"),
                    Object(NonMatching, "EngineX/EXScratchPad.cpp"),
                    Object(NonMatching, "EngineX/EXSoundManager.cpp"),
                    Object(NonMatching, "EngineX/EXStateSaver.cpp"),
                    Object(NonMatching, "EngineX/EXStats.cpp"),
                    Object(NonMatching, "EngineX/EXStdFuncs.cpp"),
                    Object(NonMatching, "EngineX/EXString.cpp"),
                    Object(NonMatching, "EngineX/EXSwoosh.cpp"),
                    Object(NonMatching, "EngineX/EXTemplates.cpp"),
                    Object(NonMatching, "EngineX/EXTexture.cpp"),
                    Object(NonMatching, "EngineX/EXVector.cpp"),
                    Object(NonMatching, "EngineX/EXWatcher.cpp"),
                    Object(NonMatching, "EngineX/EXWnd.cpp"),
                    Object(NonMatching, "EngineX/EXWString.cpp"),
                    ############################################
                    #        PS2-Specific EngineX files        #
                    ############################################
                    Object(NonMatching, "EngineX/PS2/PS2App.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Bounds.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Camera.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Cluster.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Collision.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Display.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Displayenv.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2DMAUtils.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Drawenv.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2FastMath.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2File.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Gamepad.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2GsMem.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2GeoAnim.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2GeoDrawInfo.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2GeoEntity.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2ItemRender.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Matrix.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Malloc.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2MemCard.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Movie.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2MovieAudio.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Packet.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Particle.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Quaternion.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2RenderEnv.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2ResourceWnd.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2SoundManager.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Stats.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Texture.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Vector.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2VuHandler.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Wnd.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2WndDebug.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2WndDraw.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2WndPrim.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2WndSprite.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Swoosh.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2Physics.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2GeoEntity_Instance.cpp"),
                    Object(NonMatching, "EngineX/PS2/PS2GeoTexture.cpp"),
                ],
            },
            {
                "lib": "ps2sdk",
                "toolchain_version": config.linker_version,
                "cflags": cflags_libc,
                "host": False,
                "progress_category": "libs",
                "objects": [
                    Object(NonMatching, "ps2/libmc.c"),
                    Object(NonMatching, "ps2/libscf.c"),
                    Object(NonMatching, "ps2/vu/vu.c"),
                    Object(NonMatching, "ps2/graphdev.c"),
                    Object(NonMatching, "ps2/libdma.c"),
                    Object(NonMatching, "ps2/devvu0.c"),
                    Object(NonMatching, "ps2/devvif0.c"),
                    Object(NonMatching, "ps2/libpad.c"),
                    Object(NonMatching, "ps2/eecdvd.c"),
                ],
            },
            {
                "lib": "libgcc",
                "toolchain_version": config.linker_version,
                "cflags": cflags_libc,
                "host": False,
                "progress_category": "libc",
                "objects": [
                    Object(NonMatching, "gcc/libgcc2.c"),
                    Object(NonMatching, "gcc/fp-bit.c"),
                    Object(NonMatching, "gcc/dp-bit.c"),
                    Object(NonMatching, "gcc/frame.c"),
                ],
            },
            {
                "lib": "math",
                "toolchain_version": config.linker_version,
                "cflags": cflags_libc,
                "host": False,
                "progress_category": "libc",
                "objects": [
                    Object(NonMatching, "math/sf_atan.c"),
                    Object(NonMatching, "math/sf_ceil.c"),
                    Object(NonMatching, "math/sf_cos.c"),
                    Object(NonMatching, "math/sf_fabs.c"),
                    Object(NonMatching, "math/sf_floor.c"),
                    Object(NonMatching, "math/sf_sin.c"),
                    Object(NonMatching, "math/sf_tan.c"),
                    Object(NonMatching, "math/wf_asin.c"),
                    Object(NonMatching, "math/wf_atan2.c"),
                    Object(NonMatching, "math/wf_fmod.c"),
                    Object(NonMatching, "math/wf_log.c"),
                    Object(NonMatching, "math/wf_pow.c"),
                    Object(NonMatching, "math/ef_asin.c"),
                    Object(NonMatching, "math/ef_atan2.c"),
                    Object(NonMatching, "math/ef_fmod.c"),
                    Object(NonMatching, "math/ef_log.c"),
                    Object(NonMatching, "math/ef_pow.c"),
                    Object(NonMatching, "math/ef_rem_pio2.c"),
                    Object(NonMatching, "math/ef_sqrt.c"),
                    Object(NonMatching, "math/kf_cos.c"),
                    Object(NonMatching, "math/kf_rem_pio2.c"),
                    Object(NonMatching, "math/kf_sin.c"),
                    Object(NonMatching, "math/kf_tan.c"),
                ],
            },
        ]
    )

# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("engX", "EngineX code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("dsdk", "Dolphin SDK Code"),
    ProgressCategory("libc", "STD Code"),
    ProgressCategory("libs", "Library Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
    # Append rules to sync progress.json and rebuild the website
    report_src = config.out_path() / "report.json"
    website_report = Path("website/json/progress.json")
    with open("build.ninja", "a") as f:
        f.write("\n")
        report_src_fwd = str(report_src).replace("\\", "/")
        website_report_fwd = str(website_report).replace("\\", "/")
        f.write("rule copy_report\n")
        f.write(f"  command = $python -c \"import shutil; shutil.copy2('{report_src_fwd}', '{website_report_fwd}')\"\n")
        f.write("  description = SYNC $out\n")
        f.write(f"build {website_report}: copy_report {report_src}\n")
        f.write("\n")
        # Add progress.json copy to the default build alongside 'progress'
        f.write(f"default {website_report}\n")
        f.write("rule npm_build\n")
        f.write("  command = $python -c \"import subprocess,sys; r=subprocess.run(['npm','install'],cwd='website',shell=True); r=subprocess.run(['npm','run','build'],cwd='website',shell=True); sys.exit(r.returncode)\"\n")
        f.write("  description = WEBSITE BUILD\n")
        f.write(f"build website/dist/index.html: npm_build {website_report}\n")
        f.write("\n")
        # 'ninja website' builds the website; not part of default to avoid slow npm on every build
        f.write("build website: phony website/dist/index.html\n")
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
