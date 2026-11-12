#ifndef EXITEMANIMATOR_COLLISION_H
#define EXITEMANIMATOR_COLLISION_H

#include "types.h"

#include "EXGeoScript.h"
#include "EXItemAnimator.h"

struct EXItemAnimator_Collision : /* 0x000 */ EXItemAnimator
{ // 0x148
    static EXRuntimeClass classEXItemAnimator_Collision;

protected:
    /* 0x110 */ EXDatumTemp m_Collision;
    /* 0x140 */ EXHashCode m_CollisionRef;

public:
    EXItemAnimator_Collision();
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    static EXItemAnimator_Collision* CreateObject();
    /* vtable[3] */ virtual char* TypeName() const;
    /* vtable[4] */ virtual int Size() const;
    void SetFromScriptCmd(GEOSCRIPT_COLLISION* pCmd);
    /* vtable[9] */ virtual void SetObjectTime(float rObjectTime);
    /* vtable[12] */ virtual void* GetDatum(EXHashCode DatumHashRef, EXDatumTemp& Datum, u64 Flags, void*& pPrevPtr);
    /* vtable[13] */ virtual void GetDatum(EXHashCode DatumHashRef, EXDatumTempArray& DatumArray, u64 Flags);
};

#endif // EXITEMANIMATOR_COLLISION_H
