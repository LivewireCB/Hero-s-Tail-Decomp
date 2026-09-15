#ifndef GCGEODRAWINFO_H
#define GCGEODRAWINFO_H

#include "types.h"

#include "EngineX/EXFixedArray.h"
#include "EngineX/EXGeoFile.h"
#include "EngineX/EXTexture.h"

struct EXGDiTextureRemap
{ // 0xc
    /* 0x0 */ u32 ChangeNum;
    /* 0x4 */ u128* pTexturePkt;
    /* 0x8 */ EXTexture* pTexture[1];
};

struct EXGDiBuf
{ // 0x44
    /* 0x00 */ union
    { // 0x4
        /* 0x00 */ struct
        { // 0x4
            /* 0x00:0 */ u32 ModifiedVerts : 1;
            /* 0x00:1 */ u32 RgbaModified : 1;
            /* 0x00:2 */ u32 ApplyAlphaMult : 1;
            /* 0x00:3 */ u32 VertBufChangedR : 1;
            /* 0x00:4 */ u32 VertBufChangedS : 1;
            /* 0x00:5 */ u32 VertBufTimer : 5;
            /* 0x01:2 */ u32 HWSkin : 1;
            /* 0x01:3 */ u32 ShadowRendered : 1;
            /* 0x01:4 */ u32 Spare : 20;
        };
        /* 0x00 */ u32 _Flags;
    };
    /* 0x04 */ void* pData;
    /* 0x08 */ void* pMisc;
    /* 0x0c */ void* pDynLights;
    /* 0x10 */ void* pVert;
    /* 0x14 */ void* pShadowData;
    /* 0x18 */ void* pShadowMtx;
    /* 0x1c */ void* pShadowMisc;
    /* 0x20 */ void* pShadowVert;
    /* 0x24 */ void* pVertMem;
    /* 0x28 */ void* pLightSetMem;
    /* 0x2c */ EXGDiTextureRemap* pTextureRemap;
    /* 0x30 */ u32 LastDataSize;
    /* 0x34 */ u32 LastRS;
    /* 0x38 */ u32 LastLightSet;
    /* 0x3c */ u32 LastVertexSet;
    /* 0x40 */ u32 TriCount;
};

struct EXFixedArray<EXGDiBuf, 2>
{ // 0x88
    /* 0x00 */ EXGDiBuf m_Data[2];

    // EXFixedArray<EXGDiBuf, 2>& operator=();
    EXFixedArray();
    // EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    EXGDiBuf& ElementAt();
    EXGDiBuf GetAt();
    void SetAt();
    EXGDiBuf* GetData();
    // EXGDiBuf* GetData();
    // EXGDiBuf* operator EXGDiBuf*();
    // EXGDiBuf* operator EXGDiBuf*();
};

struct EXGDiData
{ // 0x88
    /* 0x00 */ EXFixedArray<EXGDiBuf, 2> m_GDiBuf;

    // EXGDiData& operator=();
    EXGDiData();
    // EXGDiData();
    ~EXGDiData();
    void Init();
    void Release();
    EXGDiBuf* DrawBuf();
    EXGDiBuf* DMABuf();
    Bool HasModifiedVerts();
};

struct EXGDiDataArray
{ // 0x8
private:
    /* 0x0 */ EXGDiData* m_pData;
    /* 0x4 */ int m_iSize;

public:
    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXGDiDataArray& operator=();
    EXGDiDataArray();
    // EXGDiDataArray();
    ~EXGDiDataArray();
    EXGDiData* Data();
    int Size();
    void Init(int);
    void RemoveAll();
};

struct EXGDiInstanceBuff
{ // 0x14
    /* 0x00 */ void* pPkt;
    /* 0x04 */ void* pMtx;
    /* 0x08 */ void* pInstData;
    /* 0x0c */ void* pTexData;
    /* 0x10 */ u32 LastSize;
};

struct EXFixedArray<EXGDiInstanceBuff, 2>
{ // 0x28
    /* 0x00 */ EXGDiInstanceBuff m_Data[2];

    // EXFixedArray<EXGDiInstanceBuff, 2>& operator=();
    EXFixedArray();
    // EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    EXGDiInstanceBuff& ElementAt();
    EXGDiInstanceBuff GetAt();
    void SetAt();
    EXGDiInstanceBuff* GetData();
    // EXGDiInstanceBuff* GetData();
    // EXGDiInstanceBuff* operator EXGDiInstanceBuff*();
    // EXGDiInstanceBuff* operator EXGDiInstanceBuff*();
};

struct EXGDiInstanceData
{ // 0x30
    /* 0x00 */ EXFixedArray<EXGDiInstanceBuff, 2> m_GdiBuff;
    /* 0x28 */ EXHashCode m_HashCode;
    /* 0x2c */ EXGeoFile* m_pFile;

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXGDiInstanceData& operator=();
    EXGDiInstanceData();
    // EXGDiInstanceData();
    ~EXGDiInstanceData();
    void Init();
    void Release();
    EXGDiInstanceBuff* DrawBuf();
};

#endif // GCGEODRAWINFO_H
