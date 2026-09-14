#ifndef GCCLUSTER_H
#define GCCLUSTER_H

#include "types.h"

#include "EngineX/EXFixedArray.h"
#include "EngineX/EXMalloc.h"

// TODO: Make sure no other functions require the commented out members
// had to comment these out to get code gen correct in the real EXCluster file.

struct EXClusterBuff
{ // 0x4
    /* 0x0 */ void* pPkt;
    // /* 0x4 */ void* pMtx;
    // /* 0x8 */ void* pClustData;
    // /* 0xc */ u32 LastSize;
};

struct EXFixedArray<EXClusterBuff, 1>
{ // 0x4
    /* 0x0 */ EXClusterBuff m_Data[1];

    // EXFixedArray<EXClusterBuff, 1>& operator=();
    size_t Size();
    size_t GetUpperBound();
    EXClusterBuff& ElementAt();
    EXClusterBuff GetAt();
    void SetAt();
    EXClusterBuff* GetData();
    // EXClusterBuff* GetData();
    // EXClusterBuff* operator EXClusterBuff*();
    // EXClusterBuff* operator EXClusterBuff*();
};

struct EXCluster
{ // 0x4
protected:
    /* 0x00 */ EXFixedArray<EXClusterBuff, 1> m_ClusterBuff;
    // /* 0x10 */ EXClusterBuff* m_pClusterBuff;
    // /* 0x14 */ short unsigned int m_TexData[2];

public:
    void* operator new[](size_t size)
    {
        return _EXAlloc(size, 0);
    }

    void operator delete[](void* ptr)
    {
        return EXFree(ptr);
    }

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXCluster& operator=();
    EXCluster();
    // EXCluster();
    ~EXCluster();
    void Draw();
    void Create();
    void WritePktMtx();
    void WritePktCluster();
    void Update();
    void DrawVU1();
};

struct EXClusterArray
{ // 0x8
private:
    /* 0x0 */ EXCluster* m_pClusters;
    /* 0x4 */ u32 m_Size;

public:
    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXClusterArray& operator=();
    EXClusterArray();
    // EXClusterArray();
    ~EXClusterArray();
    EXCluster* Clusters();
    u32 Size();
    void Init(unsigned long size);
    void RemoveAll();
};

#endif // GCCLUSTER_H
