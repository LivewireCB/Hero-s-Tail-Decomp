#include "EngineX/EXItemAnimator_Sound.h"

EXItemAnimator_Sound* EXItemAnimator_Sound::CreateObject()
{
    return new EXItemAnimator_Sound();
}

EXItemAnimator_Sound::EXItemAnimator_Sound()
{
    m_InnerRadius = 0.0f;
    m_OuterRadius = 0.0f;
    m_SoundFlags = 0;
    m_Volume = -1;
    m_SoundCreated = false;
    m_Handle = 0;
}

Bool EXItemAnimator_Sound::Initialise(EXGeoFile* pGeoFile, EXHashCode EntityHash)
{
    m_GeoRefObject.Set(pGeoFile, EntityHash);
    m_InnerRadius = 0.0f;
    m_OuterRadius = 0.0f;
    m_SoundFlags = 0;
    m_SoundCreated = false;
    m_Volume = -1;
    return true;
}

void EXItemAnimator_Sound::SetSoundDetails(float InnerRadius, float OuterRadius, s64 Volume, u64 SoundFlags, u64 Handle)
{
    m_InnerRadius = InnerRadius;
    m_OuterRadius = OuterRadius;
    m_SoundFlags = SoundFlags;
    m_Volume = Volume;
    m_Handle = Handle;
}

void EXItemAnimator_Sound::UpdateSound(Bool fRender)
{
    EXBaseSoundManager* pSoundManager = EXBaseSoundManager::m_pSoundManager;

    if (pSoundManager == 0)
    {
        return;
    }

    EXVector vPos = m_mtx.GetTranslation();
    EXVector vVel(0.0f, 0.0f, 0.0f, 0.0f);

    switch ((m_GeoRefObject.HashRef() >> 24) & 0x7f)
    {
    case 0x1a:
    {
        EXSoundHandle* pSound;

        if (m_SoundFlags & 0x20)
        {
            if (m_SoundCreated == false)
            {
                pSound = m_SoundTag.AddTrackingSound(m_GeoRefObject.HashRef(), vPos, vVel, m_InnerRadius, m_OuterRadius);

                if (pSound)
                {
                    pSound->SetHandle(m_Handle);
                    m_SoundCreated = true;
                    return;
                }
            }
        }
        else
        {
            if (m_SoundCreated == false)
            {
                EXSoundDetails& Details = pSoundManager->SoundDetails(m_GeoRefObject.HashRef());
                float OuterRadius = m_OuterRadius;

                if (OuterRadius == 0.0f)
                {
                    OuterRadius = Details.OuterRadius;
                }

                Bool InRange = Details.Type3D ? pSoundManager->SfxIsValidRange(vPos, OuterRadius) : true;

                if (InRange)
                {
                    pSound = m_SoundTag.StartSound(m_GeoRefObject.HashRef(), vPos, vVel, m_InnerRadius, m_OuterRadius, m_Volume, 0);

                    if (pSound)
                    {
                        pSound->SetHandle(m_Handle);
                        m_SoundCreated = true;
                        return;
                    }
                }

                m_ItemFlags.BitSet(0x10);
                return;
            }

            pSound = (EXSoundHandle*)m_SoundTag.Head();

            if (pSound == 0)
            {
                m_ItemFlags.BitSet(0x10);
                return;
            }
        }

        if (m_SoundCreated)
        {
            m_SoundTag.UpdatePositionAndVelocity(vPos, vVel);
        }
        break;
    }
    case 0x1c:
        if (fRender && pSoundManager->SfxIsValidRange(vPos, m_OuterRadius))
        {
            pSoundManager->SfxSetReverbDepth(m_Volume);
        }
        break;
    }
}

void EXItemAnimator_Sound::DoUpdate()
{
    CalcMatrix_InPlaceParent();
    UpdateSound(false);
    UpdateNodes();
}

void EXItemAnimator_Sound::SetObjectTime(float rObjectTime)
{
    CalcMatrix_InPlaceParent();
    UpdateSound(false);
}

u32 EXItemAnimator_Sound::DoRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo, u64 CtrlFlags)
{
    u32 ReturnFlags = 0;

    if (EXBaseRenderEnv::RenderState() & 1)
    {
        CalcMatrix_InPlace(mtxIn, CtrlFlags);
    }

    if (!EXBaseRenderEnv::ShadowRender())
    {
        UpdateSound(true);

        if (EXBaseRenderEnv::RenderState() & 2)
        {
            ReturnFlags = 1;
        }
    }

    return ReturnFlags | RenderNodes(m_mtx, InRenderInfo, CtrlFlags);
}

EXRuntimeClass* EXItemAnimator_Sound::GetRuntimeClass() const
{
    return &EXItemAnimator_Sound::classEXItemAnimator_Sound;
}

char* EXItemAnimator_Sound::TypeName() const
{
    return "EXItemAnimator_Sound";
}

int EXItemAnimator_Sound::Size() const
{
    return sizeof(EXItemAnimator_Sound);
}

EXItemAnimator_Sound* EXItemAnimator_Sound::NewItem()
{
    return new EXItemAnimator_Sound();
}
