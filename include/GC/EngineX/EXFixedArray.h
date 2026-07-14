#ifndef EXFIXEDARRAY_H
#define EXFIXEDARRAY_H

#include "types.h"

template <typename T, int N> struct EXFixedArray
{
    T data[N];
};

#endif // EXFIXEDARRAY_H
