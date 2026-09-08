#ifndef EXALLOCATOR_H
#define EXALLOCATOR_H

#include "types.h"
#include "EXDataArray.h"

template <typename T> struct EXAllocator
{
};

struct EXAllocatorBlock
{ // 0x8
    /* 0x0 */ u32 UsedCount;
    /* 0x4 */ void* pBlock;
};

struct EXDataArray<EXAllocatorBlock, const EXAllocatorBlock&>
{ // 0x10
protected:
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ EXAllocatorBlock* m_pData;

public:
    EXDataArray();
    // EXDataArray();
    ~EXDataArray();
    void Init();
    int Size();
    int AllocSize();
    int GetUpperBound();
    void SetSize();
    void SetGrowBy(EXDataArray<EXAllocatorBlock, const EXAllocatorBlock&>*, int, void);
    void AllocMem(EXDataArray<EXAllocatorBlock, const EXAllocatorBlock&>*, int, void);
    void FreeExtra();
    void Empty();
    void RemoveAll();
    void SetAt();
    EXAllocatorBlock GetAt();
    EXAllocatorBlock& ElementAt();
    EXAllocatorBlock* GetData();
    // EXAllocatorBlock* GetData();
    void SetAtGrow();
    int Add();
    int Append();
    void Copy();
    EXAllocatorBlock& AddSpace();
    s32 AddUnique();
    s32 Find();
    // EXAllocatorBlock& operator[]();
    // EXAllocatorBlock& operator[]();
    void InsertAt();
    void RemoveAt();
    // void InsertAt();
    // EXDataArray<EXAllocatorBlock, const EXAllocatorBlock&>& operator=();

protected:
    void GrowArray();
};

struct EXAllocatorBlockArray : /* 0x0 */ EXDataArray<EXAllocatorBlock, const EXAllocatorBlock&>
{ // 0x10
};

#endif // EXALLOCATOR_H
