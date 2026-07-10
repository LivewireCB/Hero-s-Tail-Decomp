#ifndef EXGEOCOMMON_H
#define EXGEOCOMMON_H

#include "types.h"

#include "EXRuntimeClass.h"
#include "EXBounds.h"

struct EXGeoCommonObject
{ // 0x4
    static EXRuntimeClass classEXGeoCommonObject;
    // /* 0x0 */ __vtbl_ptr_type* vf4327;

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

#endif // EXGEOCOMMON_H
