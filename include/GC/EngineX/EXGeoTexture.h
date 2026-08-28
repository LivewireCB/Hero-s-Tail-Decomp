#ifndef EXGEOTEXTURE_H
#define EXGEOTEXTURE_H

#include "types.h"

#include "EngineX/EXRGB.h"
#include "EXRelPtr.h"
#include "EXHashcode.h"
#include "EXVector.h"
#include "EXHashcode.h"
#include "EXGeoCommon.h"

struct EXBaseGeoTexture
{ // 0x1c
protected:
    /* 0x00 */ u16 m_Width;
    /* 0x02 */ u16 m_Height;
    /* 0x04 */ u16 m_Depth;
    /* 0x06 */ u16 m_GameFlags;
    /* 0x08 */ s16 m_ScrollU;
    /* 0x0a */ s16 m_ScrollV;
    /* 0x0c */ u8 m_FrameCount;
    /* 0x0d */ u8 m_ImageCount;
    /* 0x0e */ u8 m_FrameRate;
    /* 0x0f */ u8 m_pad1;
    /* 0x10 */ u8 m_ValuesUsed;
    /* 0x11 */ u8 m_RegionsCount;
    /* 0x12 */ u8 m_MipCount;
    /* 0x13 */ u8 m_Format;
    /* 0x14 */ float m_MipBias;
    /* 0x18 */ RGBA m_Colour;

public:
    // EXBaseGeoTexture& operator=();
    EXBaseGeoTexture();
    // EXBaseGeoTexture();

protected:
    void SetRuntimeValues(u16 Width, u16 Height, u8 Format, u16 GameFlags, s16 ScrollU,
                          s16 ScrollV);

public:
    u16 Width();
    u16 Height();
    u16 Depth();
    s16 ScrollU();
    s16 ScrollV();
    u32 MipCount();
    float MipBias();
    u32 Format();
    u32 FrameCount();
    u32 ImageCount();
    u32 FrameRate();
    u32 RegionsCount();
    RGBA Colour();
    u16 GameFlags();
};

struct EXGeoTexture_FurData
{ // 0x10
    /* 0x0 */ u32 NumShells;
    /* 0x4 */ float ShellSpacing;
    /* 0x8 */ float ShellAlpha;
    /* 0xc */ float FinLength;
};

struct EXGeoTexture_Region
{ // 0x18
    /* 0x00 */ EXHashCode HashCode;
    /* 0x04 */ u8 ValuesUsed;
    /* 0x05 */ u8 pad0;
    /* 0x06 */ EXRelPtr16<int> rpValuesOffset;
    /* 0x08 */ EXVector2 Min;
    /* 0x10 */ EXVector2 Max;

    // EXGeoTexture_Region& operator=();
    EXGeoTexture_Region();
    // EXGeoTexture_Region();
    s32 Value();
};

struct EXGeoTexture : /* 0x00 */ EXBaseGeoTexture
{ // 0x30
protected:
    /* 0x1c */ EXRelPtr16<unsigned char> m_rpAnimSeqOffset;
    /* 0x1e */ EXRelPtr16<int> m_rpValuesOffset;
    /* 0x20 */ EXRelPtr16<EXGeoTexture_FurData> m_rpFurOffset;
    /* 0x22 */ EXRelPtr16<EXGeoTexture_Region> m_rpRegionsOffset;
    /* 0x24 */ EXRelPtr16<long long unsigned int> m_rpUploadOffset;
    /* 0x26 */ u8 m_SwizzleFlags;
    /* 0x27 */ u8 m_Pad1;
    /* 0x28 */ EXRelPtr<long long unsigned int> m_Clut;
    /* 0x2c */ EXRelPtr<long long unsigned int> m_Frames[1];

public:
    // EXGeoTexture& operator=();
    EXGeoTexture();
    // EXGeoTexture();
    u128* Frame();
    u128* Clut();
    u8* AnimSeqData();
    s32 Value();
    u8 SwizzleFlags();
    // EXGeoTexture_FurData* FurData();
    // EXGeoTexture_Region* RegionsData();
    // EXGeoTexture_Region* Region();
    u128* UploadMem();

protected:
    void SetFrameAddr();
};

// EXAMPLE:  IMPORTANT:
// THERE ARE MULTIPLE VERSIONS OF THIS STRUCT. THIS STRUCT NEEDS TO ONLY EXIST IN ITS RESPECTIVE FILES.
struct EXGeoCommonAddr
{ // 0x8
    /* 0x0 */ EXABSOFFSET32 DataOffset;
    /* 0x4 */ EXGeoTexture* pPtr;
};

struct EXGeoCommonArrayElement<EXGeoTexture>
{ // 0x10
    // protected:
    /* 0x0 */ EXHashCode m_HashCode;
    /* 0x4 */ u16 m_Section;
    /* 0x6 */ EXGeoDebug<short unsigned int> m_Debug;
    /* 0x8 */ EXGeoCommonAddr m_Address[1];

public:
    // EXGeoCommonArrayElement<EXGeoTexture>& operator=();
    EXGeoCommonArrayElement();
    // EXGeoCommonArrayElement();
    EXHashCode HashCode();
    u32 Section();
    u16 Debug();
    // EXGeoBaseDebug* DebugHeader();
    EXGeoTexture* Object();

protected:
    // EXGeoCommonAddr& Address();
    Bool ObjectCreated();
    void SetObjectCreated();
    void ClrObjectCreated();
};

struct EXGeoTextureHeader : /* 0x00 */ EXGeoCommonArrayElement<EXGeoTexture>
{ // 0x1c
protected:
    /* 0x10 */ u16 m_Width;
    /* 0x12 */ u16 m_Height;
    /* 0x14 */ u32 m_GameFlags;
    /* 0x18 */ u32 m_Flags;

public:
    // EXGeoTextureHeader& operator=();
    // EXGeoTextureHeader();
    // EXGeoTextureHeader();

protected:
    void SetRuntimeValues();

public:
    u16 Width();
    u16 Height();
    u32 Flags();
    u32 GameFlags();
};

#endif // EXGEOTEXTURE_H
