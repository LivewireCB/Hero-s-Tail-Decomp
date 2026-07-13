#ifndef EXGEOSCRIPT_H
#define EXGEOSCRIPT_H

#include "types.h"

#include "EXBounds.h"
#include "EXRelPtr.h"
#include "EXGeoCommon.h"

struct GEOSCRIPT_BASECMD
{ // 0x8
    /* 0x0 */ u8 Cmd;
    /* 0x1 */ u8 CmdSize;
    /* 0x2 */ u8 PrevCmdSize;
    /* 0x3 */ s8 GroupId;
    /* 0x4 */ s16 CmdFrame;
    /* 0x6 */ u16 CmdLength;
};

struct GEOSCRIPT_CMD : /* 0x0 */ GEOSCRIPT_BASECMD
{ // 0xc
    /* 0x8 */ u16 CtrlIndex;
    /* 0xa */ u8 Thread;
    /* 0xb */ u8 ParentThread;
};

struct EXGeoScript : /* 0x00 */ EXGeoCommonObject
{ // 0x70
    static EXRuntimeClass classEXGeoScript;

protected:
    /* 0x04 */ u32 m_NumFrames;
    /* 0x08 */ u8 m_NumThreads;
    /* 0x09 */ u8 m_NumTimeJumps;
    /* 0x0a */ u16 m_ScriptFlags;
    /* 0x0c */ float m_FrameRate;
    /* 0x10 */ EXBoundsBox m_BoundsBox;
    /* 0x30 */ EXRelPtr<unsigned int> m_rpThreadHashTable;
    // /* 0x34 */ EXRelPtr<ex::EXRELOFFSET32> m_rpThreadControllers; // TODO: Figure out the 'ex::' space
    /* 0x38 */ EXRelPtr<short unsigned int> m_rpThreadInfo;
    /* 0x3c */ u16 m_ThreadControllerCount;
    /* 0x3e */ u16 m_ThreadControllerChannelCount;
    /* 0x40 */ u32 m_UsedControllerTypes;
    /* 0x44 */ unsigned char m_Data[32];

public:
    // EXGeoScript& operator=();
    EXGeoScript();
    // ~EXGeoScript();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    void Create();
    static void _GCO_N_EXGeoScript(void* p);
    u32 NumFrames();
    u32 ScriptFlags();
    float FrameRate();
    u32 NumThreads();
    u32 NumTimeJumps();
    u32 UsedControllerTypes();
    u16 ThreadControllerChannelCount();
    u16 ThreadControllerCount();
    EXRELOFFSET32* ThreadControllerTable();
    u16* ThreadInfo();
    /* vtable[5] */ virtual EXBoundsBox& GetBoundsBox();
    GEOSCRIPT_CMD* Data();
    Bool GetFirstCmdObject();
    u32 DecodeScriptCmd();
};

#endif // EXGEOSCRIPT_H
