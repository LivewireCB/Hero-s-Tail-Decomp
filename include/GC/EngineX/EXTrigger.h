#ifndef EXTRIGGER_H
#define EXTRIGGER_H

#include "EXRuntimeClass.h"
#include "EXList.h"
#include "EXHashcode.h"

// afaict there is no corresponding cpp file for this header.
// I HAVE however kinda figured it out. The PreSE TU holds functions for EXTrigger.
// My guess is that EXTrigger got Precompiled into the PreSE TU. Which means its kind of a pain in the ass to 100% EngineX

typedef union // dumping this here
{ // 0x4
    /* 0x0 */ float f;
    /* 0x0 */ s32 i;
    /* 0x0 */ EXHashCode h;
} EXVar32;

struct EXBaseTrigger : /* 0x0 */ EXDListItem
{ // 0xc
    // /* 0x8 */ __vtbl_ptr_type* $vf9588;
};

struct EXTrigger
{ // 0x68
    static EXRuntimeClass classEXTrigger;
    /* 0x00 */ u32 m_TrigFlags;
    /* 0x04 */ u32 m_GameFlags;
    /* 0x08 */ EXHashCode m_GeoFileHashRef;
    /* 0x0c */ EXHashCode m_GfxHashRef;
    /* 0x10 */ s32 m_TrigScriptIndex;
    /* 0x14 */ EXVar32 m_Data[16];
    /* 0x54 */ short int m_Links[8];
    // /* 0x64 */ __vtbl_ptr_type* $vf12089;

    // EXTrigger& operator=();
    EXTrigger();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXTrigger* CreateObject(/* parameters unknown */);
    // EXTrigger();
    /* vtable[2] */ virtual ~EXTrigger();
    u32* Init();
    u32 GameFlags();
    Bool GameFlag();
    Bool TrigFlag();
};

#endif // EXTRIGGER_H
