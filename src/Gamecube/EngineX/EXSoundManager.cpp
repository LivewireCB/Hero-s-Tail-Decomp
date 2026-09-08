#include "EngineX/EXSoundManager.h"

EXBaseSoundManager* EXBaseSoundManager::m_pSoundManager;

// this compiler fucking sucks lol
void EXSoundHandle::Initialise()
{
    m_pPrev = NULL;
    m_pNext = NULL;
    m_pList = NULL;
    m_ManagerList.m_pPrev = NULL;
    // m_ManagerList.m_pObject = &m_ManagerList;
    m_fTrackingSound = false;
    m_Handle = NULL;
    m_HashCode = NULL;

    m_TempTimer = NULL; // 0x2e

    m_UpdateState = NULL; // 0x2d
    m_fSoundActive = NULL; // 0x2b

    // m_SoundTimeout = NULL; // 0x28
}

void EXSoundTag::SetVolume(EXHashCode SoundHash, u64 Volume) const
{
    // /* s0 16 */ EXSoundHandle* pSound;
    // /* s0 16 */ EXSoundHandle* this;
    // /* s0 16 */ EXDListItem* this;
}

void EXSoundTag::SetVolume(u64 Volume) const
{
    // /* s0 16 */ EXSoundHandle* pSound;
    // /* s0 16 */ EXDListItem* this;
}

void EXSoundTag::SetPitch(u64 Pitch) const
{
    // /* s0 16 */ EXSoundHandle* pSound;
    // /* s0 16 */ EXDListItem* this;
}
