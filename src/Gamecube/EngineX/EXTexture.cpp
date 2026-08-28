#include "EngineX/EXTexture.h"

EXBaseTexture::EXBaseTexture()
{
    m_pTextureHeader = 0;
    m_pTextureData = 0;

    m_Frame = 0;
    m_FrameTick = 0;

    m_HashCode = 0;

    m_SetScrollRate = 0;
    m_Paused = 0;
    m_NoAutoPause = 0;
    m_OnFirstFrame = 1;
    m_OnLastFrame = 0;

    m_RuntimeTexture = 0;

    m_UOffset = 0.0f;
    m_VOffset = 0.0f;
    m_UStep = 0.0f;
    m_VStep = 0.0f;
}

EXBaseTexture::~EXBaseTexture()
{
}

void EXBaseTexture::ResumeAnimation()
{
    m_Paused = 0;
    m_NoAutoPause = 1;
}

void EXBaseTexture::UpdatePtrs(EXGeoTextureHeader* pTextureHeader)
{
}
