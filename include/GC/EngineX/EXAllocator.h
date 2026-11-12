#ifndef EXALLOCATOR_H
#define EXALLOCATOR_H

#include "types.h"
#include "EXDataArray.h"

struct EXAllocatorBlock
{ // 0x8
    /* 0x0 */ u32 UsedCount;
    /* 0x4 */ void* pBlock;
};

struct EXAllocatorBlockArray : /* 0x0 */ EXDataArray<EXAllocatorBlock, const EXAllocatorBlock&>
{ // 0x10
};

template <typename T> struct EXAllocator
{ // 0x14
protected:
    /* 0x00 */ EXAllocatorBlockArray m_Blocks;
    /* 0x10 */ u32 m_BlockSize;

public:
    EXAllocator(unsigned long nBlockSize);
    T* Get();
    void Remove(T* pItem);
};

#endif // EXALLOCATOR_H
