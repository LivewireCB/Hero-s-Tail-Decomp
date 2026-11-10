#ifndef EXDATAARRAY_H
#define EXDATAARRAY_H

#include <types.h>

// This should probably be empty. Look at ExRelPtr.h
template <typename T, typename N> struct EXDataArray
{
    T* pData;
    N count;
};

struct EXDataArray<void*, void*>
{
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ void** m_pData;

    void Init(int iSize, int iGrowBy);
    void SetSize(int iSize, int iGrowBy);
    void Empty(Bool bFreeExtra);
    int Add(void* pData, int iGrowBy);
};

#endif // EXDATAARRAY_H
