#ifndef EXGEOINSTANCE_H
#define EXGEOINSTANCE_H

#include "types.h"

#include "EXDataArray.h"
#include "EXGeoFile.h"
#include "EXHashcode.h"
#include "EXMalloc.h"
#include "EXMatrix.h"
#include "ExPtrArray.h"
#include "GC/GCGeoDrawInfo.h"

struct EXInstanceInfo;

struct EXInstanceEnv
{ // 0x60
    /* 0x00 */ u32 m_Type;
    /* 0x04 */ EXHashCode m_HashCode;
    /* 0x08 */ u32 m_NumInstances;
    /* 0x0c */ u32 m_Age;
    /* 0x10 */ EXMatrix m_matParent;
    /* 0x50 */ Bool m_bUseParent;
    /* 0x54 */ EXGeoHeader* m_pGeoHeader;
    /* 0x58 */ EXInstanceInfo* m_pDrawInfo;
    /* 0x5c */ EXGDiInstanceData* m_pData;
};

struct EXDataArray<EXInstanceEnv, EXInstanceEnv&>
{
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ EXInstanceEnv* m_pData;

    EXDataArray()
    {
        Init(0, -1);
    }
    ~EXDataArray()
    {
        EXFree(m_pData);
    }
    void Init(int iSize, int iGrowBy);
    void SetSize(int iSize, int nGrowBy);
    void Empty(Bool bFreeExtra);
    EXInstanceEnv& ElementAt(int iPos)
    {
        return m_pData[iPos];
    }

    void GrowArray(int iReqNewSize);
};

struct EXPtrArray<EXInstanceEnv> : EXDataArray<void*, void*>
{ // 0x10
    EXPtrArray()
    {
        Init(0, -1);
    }
    ~EXPtrArray()
    {
        EXFree(m_pData);
    }
    EXInstanceEnv*& ElementAt(int iPos)
    {
        return (EXInstanceEnv*&)m_pData[iPos];
    }
};

struct EXInstanceManager
{ // 0x34
private:
    /* 0x00 */ EXDataArray<EXInstanceEnv, EXInstanceEnv&> m_Pool;
    /* 0x10 */ EXPtrArray<EXInstanceEnv> m_CustomPool;
    /* 0x20 */ u32 m_UsedInstanceLists;
    /* 0x24 */ u32 m_UsedCustomLists;
    /* 0x28 */ u32 m_TotalInstanceLists;
    /* 0x2c */ u32 m_TotalCustomLists;
    /* 0x30 */ EXInstanceEnv* m_pLastUsedPool;

public:
    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXInstanceManager& operator=();
    EXInstanceManager();
    ~EXInstanceManager();
    EXInstanceInfo* Instance();
    EXInstanceInfo* AllocInstanceBuffer();
    Bool AddInstanceBuffer();
    void RenderInstances();
    void DeleteManager();
    void ResetInstanceManager();
    void ReduceInstanceBuffer();
    void SetParent();
    Bool AllocateManager();
};

#endif // EXGEOINSTANCE_H
