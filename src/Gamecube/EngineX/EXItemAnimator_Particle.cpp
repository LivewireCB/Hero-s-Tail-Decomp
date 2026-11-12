#include "EngineX/EXItemAnimator_Particle.h"

EXItemAnimator_Particle* EXItemAnimator_Particle::CreateObject()
{
    return new EXItemAnimator_Particle();
}

EXItemAnimator_Particle::EXItemAnimator_Particle()
{
    m_HasRendered = false;
    m_GeoRefObject.Set(0, 0);
}

EXItemAnimator_Particle::~EXItemAnimator_Particle()
{
}

Bool EXItemAnimator_Particle::Initialise(EXGeoFile* pGeoFile, EXHashCode HashRef)
{
    return InitialiseCustom(pGeoFile, HashRef, 0);
}

Bool EXItemAnimator_Particle::InitialiseCustom(EXGeoFile* pGeoFile, EXHashCode HashRef, EXRuntimeClass* pClass)
{
    if (m_GeoRefObject.GeoFile())
    {
        if (m_GeoRefObject.GeoFile() == pGeoFile && m_GeoRefObject.HashRef() == HashRef)
        {
            return true;
        }

        m_EffectsTag.DetatchSystems();
    }

    m_GeoRefObject.Set(pGeoFile, HashRef);
    m_HasRendered = false;

    EXParticleSys* pParticleSys = (EXParticleSys*)m_EffectsTag.AttachParticleSys(this, pGeoFile, HashRef, pClass);

    if (pParticleSys == 0)
    {
        return false;
    }

    pParticleSys->m_bAggressiveCull = false;
    return true;
}

void EXItemAnimator_Particle::DeleteParticleSys() const
{
    m_EffectsTag.DeleteSystems(&EXParticleSys::classEXParticleSys);
}

EXParticleSys* EXItemAnimator_Particle::ParticleSys() const
{
    EXParticleSys* pSys;

    if (m_EffectsTag.Head())
    {
        pSys = (EXParticleSys*)m_EffectsTag.FindSystem(&EXParticleSys::classEXParticleSys);
    }
    else
    {
        pSys = 0;
    }

    return pSys;
}

void EXItemAnimator_Particle::EnableParticleSystems(Bool Enable) const
{
    EXParticleSys* pSys = ParticleSys();

    if (pSys)
    {
        pSys->m_Enabled = Enable;
    }
}

u32 EXItemAnimator_Particle::DoRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo, u64 CtrlFlags)
{
    if (EXBaseRenderEnv::RenderState() & 1)
    {
        CalcMatrix_InPlace(mtxIn, CtrlFlags);
    }

    u32 ReturnFlags = 0;

    if (EXBaseRenderEnv::RenderState() & 2)
    {
        if (EXBaseRenderEnv::ShadowRender())
        {
            return 0;
        }

        EXParticleSys* pParticleSys = ParticleSys();

        if (pParticleSys)
        {
            EXRenderInfo RenderInfo;

            EXRenderInfo::Merge(RenderInfo, m_RenderInfo, InRenderInfo);
            ReturnFlags = 1;
            pParticleSys->UpdateRenderInfo(RenderInfo);
            m_HasRendered = true;
        }
    }

    return ReturnFlags | RenderNodes(m_mtx, InRenderInfo, CtrlFlags);
}

EXRuntimeClass* EXItemAnimator_Particle::GetRuntimeClass() const
{
    return &EXItemAnimator_Particle::classEXItemAnimator_Particle;
}

char* EXItemAnimator_Particle::TypeName() const
{
    return "EXItemAnimator_Particle";
}

int EXItemAnimator_Particle::Size() const
{
    return sizeof(EXItemAnimator_Particle);
}

EXItemAnimator_Particle* EXItemAnimator_Particle::NewItem()
{
    return new EXItemAnimator_Particle();
}
