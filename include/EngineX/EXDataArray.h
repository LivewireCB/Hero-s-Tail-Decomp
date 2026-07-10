#ifndef EXDATAARRAY_H
#define EXDATAARRAY_H

#include "types.h"

// This should probably be empty. Look at ExRelPtr.h
template <typename T, typename N> struct EXDataArray
{
    T* pData;
    N count;
};

#endif // EXDATAARRAY_H
