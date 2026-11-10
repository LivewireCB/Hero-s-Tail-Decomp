#include "EngineX/EXGeoTexture.h"

void EXBaseGeoTexture::SetRuntimeValues(u16 Width, u16 Height, u8 Format, u16 GameFlags,
                                        s16 ScrollU, s16 ScrollV)
{
    m_Width = Width;
    m_Height = Height;
    m_Depth = 1;
    m_GameFlags = GameFlags;
    m_ScrollU = ScrollU;
    m_ScrollV = ScrollV;
    m_FrameCount = 1;
    m_ImageCount = 1;
    m_FrameRate = 1;
    m_pad1 = 0;
    m_ValuesUsed = 0;
    m_RegionsCount = 0;
    m_MipCount = 1;
    m_Format = Format;
    m_Colour.rgba = 0;
}

void EXGeoTextureHeader::SetRuntimeValues(EXGeoTexture* pTexture, u16 Width, u16 Height,
                                          unsigned long GameFlags, unsigned long Flags)
{
    m_HashCode = 0;
    m_Section = 0;
    m_Debug = 0;
    m_Address[0].pPtr = pTexture;
    m_Width = Width;
    m_Height = Height;
    m_GameFlags = GameFlags;
    m_Flags = Flags;
}
