#include "EngineX/EXGeoTexture.h"

void EXBaseGeoTexture::SetRuntimeValues(u16 Width, u16 Height, u8 Format, u16 GameFlags,
                                        s16 ScrollU, s16 ScrollV)
{
    m_Width = Width;

    m_Height = Height;
    m_Format = Format;
    m_GameFlags = GameFlags;
    m_ScrollU = ScrollU;
    m_ScrollV = ScrollV;
    m_RegionsCount = 0;
    m_MipCount = 1;

    m_Depth = 1;
    m_FrameCount = 1;
    m_ImageCount = 1;
    m_FrameRate = 1;
    m_pad1 = 0;
    m_ValuesUsed = 0;

    m_Colour.r = 0;
}
