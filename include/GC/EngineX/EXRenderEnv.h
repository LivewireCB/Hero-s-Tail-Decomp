#ifndef EXRENDERENV_H
#define EXRENDERENV_H

#include "types.h"

#include "EXDataArray.h"
#include "EXFlagTemplate.h"
#include "EXGeoFile.h"
#include "EXHashcode.h"
#include "EXRGB.h"
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
    EXRenderInfo()
    {
    }
    void SetDefault();
    static EXRenderInfo& Merge(EXRenderInfo& Out, EXRenderInfo& Child, EXRenderInfo& Parent);
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

struct EXLightManager;
struct EXDynLightData;

struct EXRenderFogInfo
{ // 0x18
    /* 0x00 */ RGBA m_FogColor;
    /* 0x04 */ float m_FogNear;
    /* 0x08 */ float m_FogFar;
    /* 0x0c */ float m_FogMin;
    /* 0x10 */ float m_FogMax;
    /* 0x14 */ Bool m_EnableFog;

    // EXRenderFogInfo& operator=();
    EXRenderFogInfo();
    // EXRenderFogInfo();
    void SetFogDistance();
    void SetFogMinMax();
    void SetFogColor();
    void SetFogEnabled();
    float FogNear();
    float FogFar();
    float FogMin();
    float FogMax();
    RGBA FogColor();
    Bool FogEnabled();
};

struct EXBaseRenderEnv
{ // 0x4
protected:
    static EXRenderInfo ms_RenderInfo;
    static EXRenderInfo ms_GRenderInfo;
    static EXRenderFogInfo ms_RenderFogInfo;
    static Bool ms_WideScreen;
    static u32 ms_ContrastModifier;
    static Bool ms_DistanceFade;
    static float ms_DistanceFadeStart;
    static float ms_DistanceFadeEnd;
    static Bool ms_ShadowRender;
    static Bool ms_ReflectionRender;
    static float ms_ReflectionHeight;
    static u16 ms_RefractTexWidth;
    static u16 ms_RefractTexHeight;
    static u32 ms_RenderState;
    static EXLightManager* ms_pLightManager;
    static EXDynLightData* ms_DynLights[4];
    static u32 ms_DynLightCount;
    static Bool ms_RenderPortals;
    static Bool ms_RenderLights;
    static Bool ms_RenderSounds;
    static Bool ms_RenderBspGrid;
    static Bool ms_RenderGrabPoints;
    static Bool ms_RenderMapZones;
    static Bool ms_RenderEntityBounds;
    static Bool ms_RenderScoopCollision;
    static Bool ms_RenderPaths;
    static Bool ms_RenderAnimBones;
    static Bool ms_RenderDynLights;
    static Bool ms_RenderCameras;
    static Bool ms_RenderClipBounds;
    static u32 ms_RenderFlashingBackground;
    static Bool ms_RenderNavMesh;
    static Bool ms_RenderNavConnections;
    static Bool ms_RenderNavPaths;
    static u32 ms_RenderItemDir;
    static u32 ms_RenderDrawType;
    static EXRenderFogInfo ms_OverrideFogInfo;

public:
    /* 0x0 */ // __vtbl_ptr_type* $vf8154;

    // EXBaseRenderEnv& operator=();
    EXBaseRenderEnv();
    // EXBaseRenderEnv();
    /* vtable[1] */ virtual ~EXBaseRenderEnv();
    /* vtable[2] */ virtual void CalcFogCoefficients();
    /* vtable[3] */ virtual void RegisterWatcherVars();
    static Bool ShadowRender()
    {
        return ms_ShadowRender;
    }
    static u32 RenderState()
    {
        return ms_RenderState;
    }
};

#endif // EXRENDERENV_H
