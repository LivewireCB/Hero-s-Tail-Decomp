#ifndef EXPTRARRAY_H
#define EXPTRARRAY_H

#include "types.h"

template <typename T> struct EXPtrArray
{
    int m_iAlloc;
    int m_iGrowBy;
    int m_iSize;
    T** m_pData;
};

#endif
