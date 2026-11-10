#include "EngineX/EXGeoFace.h"

#include "EngineX/EXDisplay.h"

void EXGeoFace::Draw(EXGDiData* pGDiData, unsigned long Flags)
{
    EXWnd* pWnd = EXBaseDisplay::ActiveWnd();
    if (pWnd != 0)
    {
        EXTexture* pTexture = EXBaseDisplay::GeoHeader()->Texture(m_TextureRef);
        pWnd->SetTriFanBlendMode(0);
        pWnd->SelectTriFanTexture(pTexture);
        pWnd->DrawTriFan(m_VertexCount, (EXPrimVert*)m_vtx);
    }
}

EXRuntimeClass* EXGeoFace::GetRuntimeClass() const
{
    return &classEXGeoFace;
}