#ifndef EXRENDERENV_H
#define EXRENDERENV_H

#include "types.h"

#include "EXDataArray.h"
#include "EXFlagTemplate.h"
#include "EXGeoFile.h"
#include "EXHashcode.h"
#include "EXTexture.h"
#include "EXVector.h"

struct EXTexSwapEntry
{ // 0x10
    /* 0x0 */ EXHashCode OldHash;
    /* 0x4 */ EXHashCode NewFileHash;
    /* 0x8 */ union
    { // 0x8
        /* 0x8 */ struct
        { // 0x8
            /* 0x8 */ EXGeoFile* pNewGeoFile;
            /* 0xc */ EXHashCode NewTexHash;
        };
        /* 0x8 */ struct
        { // 0x8
            /* 0x8 */ EXTexture* pNewTexture;
            /* 0xc */ u32 Pad;
        };
    };
};

struct EXTexSwapInfo
{ // 0x14
protected:
    /* 0x00 */ u32 m_ChangeNum;
    /* 0x04 */ EXDataArray<EXTexSwapEntry, const EXTexSwapEntry&> m_Swaps;

public:
    // EXTexSwapInfo& operator=();
    EXTexSwapInfo();
    // EXTexSwapInfo();
    ~EXTexSwapInfo();
    void SetSwap();
    // void SetSwap();
    // void SetSwap();
    Bool StopSwap();
    void SetCatchAllSwap();
    // void SetCatchAllSwap();
    // void SetCatchAllSwap();
    Bool StopCatchAllSwap();
    void StopAllSwaps();
    u32 ChangeNum();
    u32 SwapCount();
    // EXTexture* SwappedTexture();

protected:
    void ResolveHashCodes();
};

struct EXExtRenderInfo
{ // 0x80
    /* 0x00 */ EXVector m_LightVect[3];
    /* 0x30 */ EXVector m_LightCol[3];
    /* 0x60 */ EXVector m_Ambient;
    /* 0x70 */ float m_FastAmbientCol;
    /* 0x74 */ float m_RefractionStrength;
    /* 0x78 */ union
    { // 0x4
        /* 0x78 */ u32 m_ExtRenderFlags;
        /* 0x78 */ struct
        { // 0x4
            /* 0x78:0 */ u32 m_RefractDirect : 1;
            /* 0x78:1 */ u32 m_FastAmbient : 1;
            /* 0x78:2 */ u32 m_PadBits : 30;
        };
    };
    /* 0x7c */ float m_SquashShadowHeight;

    // EXExtRenderInfo& operator=();
    EXExtRenderInfo();
    // EXExtRenderInfo();
    void SetDefault();
    EXVector& LightVector();
    EXVector& LightColor();
    EXVector& Ambient();
    void SetLightData();
    void SetFastAmbientData();
    void SetRefractionStrength();
    void EnableRefractDirect();
    void SetSquashShadowHeight();
};

struct EXRenderInfo
{ // 0x30
protected:
    /* 0x00 */ MXVector m_RGBAMult;
    /* 0x10 */ EXExtRenderInfo* m_pExtRenderInfo;
    /* 0x14 */ EXTexSwapInfo* m_pTexSwapInfo;
    /* 0x18 */ EXFlag<short unsigned int> m_RenderFlags;
    /* 0x1a */ u8 m_RenderMode;
    /* 0x1b */ u8 m_ShadowType;
    /* 0x1c */ s16 m_ShadowDensity;
    /* 0x1e */ s16 m_Pad1;
    /* 0x20 */ s16 m_LightSet1;
    /* 0x22 */ s16 m_LightSet2;
    /* 0x24 */ s16 m_VertexSet1;
    /* 0x26 */ s16 m_VertexSet2;
    /* 0x28 */ u8 m_LightSetBlend;
    /* 0x29 */ u8 m_VertexSetBlend;
    /* 0x2a */ s16 m_Pad2;
    /* 0x2c */ s32 m_Pad3;

public:
    // EXRenderInfo& operator=();
    EXRenderInfo();
    // EXRenderInfo();
    // EXRenderInfo();
    void SetDefault();
    static EXRenderInfo& Merge(/* parameters unknown */);
    void SetRenderMode();
    void EnableWireFrame();
    void EnableRGBMult();
    void EnableAlphaMult();
    void SetRGBAMult();
    // void SetRGBAMult();
    void EnableLightSet();
    void SetLightSet();
    // void SetLightSet();
    void EnableVertexSet();
    void SetVertexSet();
    // void SetVertexSet();
    void SetShadowDensity();
    void DisableZWrite();
    void DisableZRead();
    void DisableLods();
    void DisableDrawShadow();
    void SetExtRenderInfo();
    void ClearExtRenderInfo();
    void SetTexSwapInfo();
    void ClearTexSwapInfo();
    void EnableRefractionRender();
    void EnableHeatRender();
    void EnableParentRGBAMultOverride();
    u32 RenderMode();
    u16 RenderFlags();
    Bool WireFrameEnabled();
    Bool RGBMultEnabled();
    Bool AlphaMultEnabled();
    EXVector& RGBAMult();
    u16 LightSet1();
    u16 LightSet2();
    float LightSetBlend();
    u8 LightSetBlendRaw();
    u16 VertexSet1();
    u16 VertexSet2();
    float VertexSetBlend();
    u8 VertexSetBlendRaw();
    float ShadowDensity();
    Bool ZWriteDisabled();
    Bool ZReadDisabled();
    Bool LodDisabled();
    Bool ShadowDrawDisabled();
    Bool ParentRGBAMultOverrideEnabled();
    EXExtRenderInfo* ExtRenderInfo();
    EXVector& LightVector();
    EXVector& LightColor();
    EXVector& AmbientColor();
    float RefractionStrength();
    Bool RefractDirect();
    float SquashShadowHeight();
    Bool HasExtRenderInfo();
    EXTexSwapInfo* TexSwapInfo();
    Bool HasTexSwapInfo();
    Bool RefractionRender();
    Bool HeatRender();
    Bool FastAmbientLighting();
    float FastAmbientCol();
    void SetShadowType();
    u8 ShadowType();
};

#endif // EXRENDERENV_H
