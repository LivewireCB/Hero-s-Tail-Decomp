#ifndef EXGEOCOMMON_H
#define EXGEOCOMMON_H

#include "types.h"

#include "EXRuntimeClass.h"
#include "EXBounds.h"
#include "EXHashcode.h"
#include "EXRelPtr.h"

template <typename T> struct EXGeoCommonArrayElement
{
};

template <typename T> struct EXGeoDebug
{
};

struct EXGeoCommonObject
{ // 0x4
    static EXRuntimeClass classEXGeoCommonObject;
    // /* 0x0 */ __vtbl_ptr_type* $vf4327;

    // EXGeoCommonObject& operator=();
    EXGeoCommonObject();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    void Create();
    static void _GCO_N_EXGeoCommonObject(/* parameters unknown */);
    // EXGeoCommonObject();
    /* vtable[2] */ virtual void OnCreate();
    /* vtable[3] */ virtual void OnDelete();
    /* vtable[4] */ virtual void Draw();
    /* vtable[5] */ virtual EXBoundsBox& GetBoundsBox();
};

struct EXGeoBaseDebug
{ // 0x4
protected:
    /* 0x0 */ EXRelPtr<const char> m_rpName;

public:
    // EXGeoBaseDebug& operator=();
    EXGeoBaseDebug();
    // EXGeoBaseDebug();
    char* Name();
};

struct EXGeoDebug<short unsigned int>
{ // 0x2
protected:
    /* 0x0 */ u16 m_DebugIndex;

public:
    // EXGeoDebug<short unsigned int>& operator=();
    EXGeoDebug();
    // EXGeoDebug();
    EXGeoBaseDebug* Get();
    // u32 operator unsigned int();
    // void operator=();
};

#endif // EXGEOCOMMON_H
