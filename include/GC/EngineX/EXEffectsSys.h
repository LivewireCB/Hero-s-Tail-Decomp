#ifndef EXEFFECTSSYS_H
#define EXEFFECTSSYS_H

#include "types.h"

#include "EXGeoFile.h"
#include "EXList.h"
#include "EXRenderEnv.h"
#include "EXRuntimeClass.h"

struct EXEffectsSysMgr;
struct EXItemAnimator;

struct EXEffectsSys : /* 0x00 */ EXLDListItem
{ // 0x60
    static EXRuntimeClass classEXEffectsSys;

protected:
    /* 0x0c */ EXGeoComplexRefObject m_GeoRefObject;
    /* 0x20 */ EXRenderInfo m_RenderInfo;
    /* 0x50 */ EXEffectsSysMgr* m_pSystemMgr;

public:
    EXEffectsSys();
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    /* vtable[2] */ virtual ~EXEffectsSys();
    /* vtable[3] */ virtual void UpdateRenderInfo(EXRenderInfo& Parent);
};

struct EXEffectsSysTag : /* 0x0 */ EXLDList
{ // 0x8
    ~EXEffectsSysTag();
    void Add();
    void Remove();
    void UpdateRenderInfo(EXRenderInfo& Parent) const;
    EXEffectsSys* FindSystem(EXRuntimeClass* pClass) const;
    void DetatchSystems() const;
    void DeleteSystems(EXRuntimeClass* pClass) const;
    EXEffectsSys* AttachParticleSys(EXItemAnimator* pAnimator, EXGeoFile* pGeoFile, EXHashCode HashRef, EXRuntimeClass* pClass);
};

#endif // EXEFFECTSSYS_H
