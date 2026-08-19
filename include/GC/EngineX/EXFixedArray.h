#ifndef EXFIXEDARRAY_H
#define EXFIXEDARRAY_H

#include "types.h"

template <typename T, int N> struct EXFixedArray
{
    T data[N];
};

struct EXFixedArray<unsigned int, 8>
{ // 0x20
    /* 0x00 */ unsigned int m_Data[8];

    // EXFixedArray<unsigned int, 8>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    // size_t Size();
    // size_t GetUpperBound();
    // u32& ElementAt();
    // u32 GetAt();
    // void SetAt();
    // u32* GetData();
    // u32* GetData();
    // u32* operator unsigned int*();
    // u32* operator unsigned int*();
};

struct EXFixedArray<const char*, 4>
{ // 0x10
    /* 0x0 */ char* m_Data[4];

    // EXFixedArray<const char*, 4>& operator=();
    // EXFixedArray();
    // ~EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    char*& ElementAt();
    char* GetAt();
    void SetAt();
    char** GetData();
    // char** GetData();
    // char** operator char**();
    // char** operator char**();
};

struct EXFixedArray<char, 32>
{ // 0x20
    /* 0x00 */ char m_Data[32];

    // EXFixedArray<char, 32>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    char& ElementAt();
    char GetAt();
    void SetAt();
    char* GetData();
    // char* GetData();
    // char* operator char*();
    // char* operator char*();
};

struct EXFixedArray<char, 34>
{ // 0x22
    /* 0x00 */ char m_Data[34];

    // EXFixedArray<char, 34>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    char& ElementAt();
    char GetAt();
    void SetAt();
    char* GetData();
    // char* GetData();
    // char* operator char*();
    // char* operator char*();
};

struct EXFixedArray<int[4], 4>
{ // 0x40
    /* 0x00 */ int m_Data[4][4];

    // EXFixedArray<int[4], 4>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    // size_t Size();
    // size_t GetUpperBound();
    // _iconVu0IVECTOR& ElementAt();
    // _iconVu0IVECTOR GetAt();
    // void SetAt();
    // int* [4] GetData();
    // _iconVu0IVECTOR* GetData();
    // int* [4] operator int (*)[3]();
    // _iconVu0IVECTOR* operator int (*)[3]();
};

struct EXFixedArray<float[4], 3>
{ // 0x30
    /* 0x00 */ float m_Data[3][4];

    // EXFixedArray<float[4], 3>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    // size_t Size();
    // size_t GetUpperBound();
    // _iconVu0FVECTOR& ElementAt();
    // _iconVu0FVECTOR GetAt();
    // void SetAt();
    // float* [4] GetData();
    // _iconVu0FVECTOR* GetData();
    // float* [4] operator float (*)[3]();
    // _iconVu0FVECTOR* operator float (*)[3]();
};

#endif // EXFIXEDARRAY_H
