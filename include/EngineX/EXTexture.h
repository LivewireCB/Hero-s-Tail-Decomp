#ifndef EXTEXTURE_H
#define EXTEXTURE_H

#include "types.h"
#include "EXHashcode.h"

// TODO: FIX STRUCT
struct EXBaseTexture
{ // 0x24
protected:
    // /* 0x00 */ EXGeoTextureHeader* m_pTextureHeader;
    // /* 0x04 */ EXGeoTexture* m_pTextureData;
    /* 0x08 */ EXHashCode m_HashCode;
    /* 0x0c */ u8 m_Frame;
    /* 0x0d */ u8 m_FrameTick;
    /* 0x0e */ union
    { // 0x1
        /* 0x0e */ u8 m_AnimFlags;
        /* 0x0e */ struct
        { // 0x1
            /* 0x0e:0 */ u8 m_SetScrollRate : 1;
            /* 0x0e:1 */ u8 m_Paused : 1;
            /* 0x0e:2 */ u8 m_NoAutoPause : 1;
            /* 0x0e:3 */ u8 m_OnFirstFrame : 1;
            /* 0x0e:4 */ u8 m_OnLastFrame : 1;
            /* 0x0e:5 */ u8 m_AnimFlagsPad : 3;
        };
    };
    /* 0x0f */ Bool m_RuntimeTexture;
    /* 0x10 */ float m_UStep;
    /* 0x14 */ float m_VStep;
    /* 0x18 */ float m_UOffset;
    /* 0x1c */ float m_VOffset;

public:
    // /* 0x20 */ __vtbl_ptr_type* $vf10545;

    // EXBaseTexture& operator=();
    EXBaseTexture();
    // EXBaseTexture();
    // /* vtable[1] */ virtual EXBaseTexture(EXBaseTexture*, int, void);
    void SetHashCode();
    EXHashCode HashCode();
    // EXGeoTextureHeader* GeoTextureHeader();
    // EXGeoTexture* GeoTexture();
    u16 Width();
    u16 Height();
    u32 Flags();
    u32 GameFlags();
    /* vtable[2] */ virtual void Load();
    /* vtable[3] */ virtual void Unload();
    /* vtable[4] */ virtual void Select();
    /* vtable[5] */ virtual void Animate();
    /* vtable[6] */ virtual Bool InitRuntimeTexture();
    /* vtable[7] */ virtual void DestroyRuntimeTexture();
    void SetScrollRate();
    void SetScrollRateAngular();
    float ScrollRateU();
    float ScrollRateV();
    void StopScroll();
    void ResetScrollRate();
    void ReverseScroll();
    Bool IsScrolling();
    float ScrollStepU();
    float ScrollStepV();
    u8 FrameCount();
    void RestartAnimation();
    void PauseAnimation();
    void ResumeAnimation();
    Bool IsPaused();
    Bool IsOnFirstFrame();
    Bool IsOnLastFrame();
    float UOffset();
    float VOffset();
    Bool HasSetScrollRate();
    void UpdatePtrs();
    // void UpdatePtrs();

private:
    /* vtable[8] */ virtual void Update();
};

// TODO: FIX STRUCT
struct EXTexture : /* 0x00 */ EXBaseTexture
{ // 0xf0
protected:
    /* 0x30 */ u128 m_VifTag;
    /* 0x40 */ u128 m_TexDataVector;
    /* 0x50 */ u128 m_VifUnpack;
    // /* 0x60 */ sceGifTag m_GifTag;
    // /* 0x70 */ sceGsTex0 m_Tex01;
    /* 0x78 */ u64 m_Tex01Addr;
    // /* 0x80 */ sceGsMiptbp1 m_MipTbp1;
    /* 0x88 */ u64 m_MipTbp1Addr;
    // /* 0x90 */ sceGsTex1 m_Tex11;
    /* 0x98 */ u64 m_Tex11Addr;
    // /* 0xa0 */ sceGsClamp m_Clamp1;
    /* 0xa8 */ u64 m_Clamp1Addr;
    // /* 0xb0 */ sceGsFrame m_Frame1;
    /* 0xb8 */ u64 m_Frame1Addr;
    /* 0xc0 */ u16 m_TexPage;
    /* 0xc2 */ u8 m_BasePageSize;
    /* 0xc3 */ u8 m_PageSize;
    // /* 0xc4 */ EXFixedArray<short unsigned int, 4> m_MipOffset;
    // /* 0xcc */ EXFixedArray<short unsigned int, 4> m_w64;
    /* 0xd4 */ Bool m_PalTex;
    /* 0xd5 */ Bool m_Updated;
    /* 0xd6 */ Bool m_RuntimeInVRAMTex;
    /* 0xd7 */ Bool m_SpareBool;
    /* 0xd8 */ Bool m_VRAMPack;
    /* 0xdc */ s32 m_MipMapK;
    /* 0xe0 */ float m_UVShift;
    /* 0xe4 */ u32 m_UploadSeq;
    static EXTexture* m_pSelTexture;

public:
    // EXTexture& operator=();
    EXTexture();
    // EXTexture();
    // /* vtable[1] */ virtual EXTexture(EXTexture*, int, void);
    static void DeselectTexture(/* parameters unknown */);
    /* vtable[2] */ virtual void Load();
    /* vtable[3] */ virtual void Unload();
    /* vtable[4] */ virtual void Select();
    void SetLoadData();
    void SetAddrData();
    /* vtable[5] */ virtual void Animate();
    /* vtable[6] */ virtual Bool InitRuntimeTexture();
    /* vtable[7] */ virtual void DestroyRuntimeTexture();
    u64 TextureFrameReg();
    void SetTextureData();
    void SetTextureDataDepth();
    void SetTiling();
    void SetFiltered();
    u32 UploadSeq();
    void SetUploadSeq();
    u16 BasePageSize();
    u16 PageSize();
    u16 PalTex();
    u16 MipOffset();
    void* VifSelectAddr();
    void* GifSelectAddr();
    static u32 VifSelectQuads(/* parameters unknown */);
    static u32 GifSelectQuads(/* parameters unknown */);
    void* Tex0Addr();
    void SetTextureEffect();
    u16 GetTexPage();
    Bool IsVRAMPackable();

private:
    /* vtable[8] */ virtual void Update();
    void SetupTexDataPriv();

protected:
    void* FrameAddr();
    u16 TexPSM();
    void SetTexPage();
    u16 TexPage();
    Bool RuntimeInVRAMTex();
};

struct EXTextureArray
{ // 0x14
protected:
    /* 0x00 */ u32 m_BlockCount;
    /* 0x04 */ u32 m_TextureCount;
    /* 0x08 */ EXTexture** m_pTextureData;
    /* 0x0c */ EXBit128* m_pBlockUse;
    /* 0x10 */ u32 m_LastBlockSize;

public:
    // EXTextureArray& operator=();
    EXTextureArray();
    // EXTextureArray();
    // EXTextureArray(EXTextureArray*, int, void);
    Bool Init();
    void Release();
    u32 TextureCount();
    s32 NewTexture();
    Bool DeleteTexture();
    s32 FindTextureIndex();
    // EXTexture* SafeTexture();
    // EXTexture& operator[]();

protected:
    Bool InitBlockUse();
};

#endif // EXTEXTURE_H
