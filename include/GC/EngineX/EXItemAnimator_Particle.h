#ifndef EXITEMANIMATOR_PARTICLE_H
#define EXITEMANIMATOR_PARTICLE_H

#include "types.h"

#include "EXEffectsSys.h"
#include "EXItemAnimator.h"
#include "EXParticleSys.h"

struct EXItemAnimator_Particle : /* 0x000 */ EXItemAnimator
{ // 0x120
    static EXRuntimeClass classEXItemAnimator_Particle;

protected:
    /* 0x110 */ EXEffectsSysTag m_EffectsTag;
    /* 0x118 */ Bool m_HasRendered;

public:
    EXItemAnimator_Particle();
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    static EXItemAnimator_Particle* CreateObject();
    /* vtable[3] */ virtual char* TypeName() const;
    /* vtable[4] */ virtual int Size() const;
    static EXItemAnimator_Particle* NewItem();
    /* vtable[1] */ virtual ~EXItemAnimator_Particle();
    /* vtable[7] */ virtual Bool Initialise(EXGeoFile* pGeoFile, EXHashCode HashRef);
    Bool InitialiseCustom(EXGeoFile* pGeoFile, EXHashCode HashRef, EXRuntimeClass* pClass);
    void DeleteParticleSys() const;
    EXParticleSys* ParticleSys() const;
    /* vtable[11] */ virtual void EnableParticleSystems(Bool Enable) const;
    /* vtable[6] */ virtual u32 DoRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo, u64 CtrlFlags);
};

#endif // EXITEMANIMATOR_PARTICLE_H
