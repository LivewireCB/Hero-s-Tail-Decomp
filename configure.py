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
    "G5SE7D",  # 0
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
    config.platform = Platform.X360
    config.dtk_tag = "v0.1.2"
    config.binutils_tag = "2.42-1"
elif version_num in [2]:
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
        "-I include",
        f"-I build/{config.version}/include",
        f"--defsym BUILD_VERSION={version_num}",
    ]

    ldscript_path = Path("config") / config.version / "ldscript.ld"
    config.ldflags = ["-T", str(ldscript_path)]

    # Optional numeric ID for decomp.me preset
    # Can be overridden in libraries or objects
    config.scratch_preset_id = 0
elif config.platform == Platform.PS2:
    config.asflags = [
        "-no-pad-sections",
        "-EL",
        "-march=5900",
        "-mabi=eabi",
        "-I include",
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
        "-i include",
        f"-i build/{config.version}/include",
        "-multibyte",
        f"-DVERSION={version_num}",
    ]

    # TODO move some of these to the game flags
    cflags_base_prodg = [
        "-O1",
        "-gdwarf",
        # "-Wa,-L",
        # "-Wall",
        # "-Wreturn-type", # enable at some point
        "-Wno-ctor-dtor-privacy",  # because of AttribSys for example
        "-Woverloaded-virtual",
        "-I include",
        "-I src/Packages",
        "-I ./",
        "-I src",
        "-DEA_PLATFORM_GAMECUBE",
        "-DEA_REGION_AMERICA",
        "-DGEKKO",
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
        "-mps-nodf",
        # "-mfast-cast",
        "-G0",
        "-ffast-math",
        # "-fno-strength-reduce",
        "-fforce-addr",
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
        # # "-fcaller-saves",
        # # "-ffloat-store",
        # # "-funroll-all-loops",
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
            "src_dir": "src",
            "toolchain_version": "GC/1.2.5n",
            "cflags": cflags_dolphin,
            "progress_category": "sdk",
            "objects": objects,
        }

elif config.platform == Platform.PS2:
    config.linker_version = "PS2/ee-gcc2.9-991111"

    cflags_base_prodg = [
        "-O2",
        "-g2",
        # "-Wall",
        "-I src/Speed/Indep/Libs/Support/stlps2",
        "-I src/Speed/PSX2/Libs/stl/gpp",
        "-I src/Speed/PSX2/bWare/src/ee/include",
        "-I src/Speed/PSX2/bWare/src/ee/gcc/ee/include",
        "-I src/Speed/PSX2/bWare/src/ee/gcc/lib/gcc-lib/ee/2.9-ee-991111/include",
        "-I src/Speed/PSX2/bWare/src/ee/gcc/ee",
        "-I src/Speed/PSX2/bWare/src/ee/gcc/lib/gcc-lib/ee/2.9-ee-991111",
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

config.libs = []

if config.platform == Platform.GC_WII:
    config.libs.extend(
        [
            {
                "lib": "libsn",
                "toolchain_version": config.linker_version,
                "cflags": cflags_base_prodg,
                "host": False,
                "progress_category": "libs",  # str | List[str]
                "objects": [
                    Object(NonMatching, "prodg_fixes.cpp"),
                ],
            },
            {
                "lib": "Spyro",
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
                "src_dir": "src",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "engX",  # str | List[str]
                "objects": [
                    Object(NonMatching, "EngineX/EXAnimCache.cpp"),
                ],
            },
            {
                "lib": "stdlib",
                "src_dir": "src",
                "toolchain_version": config.linker_version,
                "cflags": cflags_game,
                "host": False,
                "progress_category": "libc",  # str | List[str]
                "objects": [
                    Object(NonMatching, "stdlib/itoa.c"),
                ],
            },
            DolphinLib(
                "ar",
                [
                    Object(NonMatching, "dolphin/ar/ar.c"),
                ],
            ),
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
    ProgressCategory("libc", "STD Code"),
    ProgressCategory("libs", "Library Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
