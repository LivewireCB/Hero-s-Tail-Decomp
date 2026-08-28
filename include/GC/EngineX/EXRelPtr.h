#ifndef EXRELPTR_H
#define EXRELPTR_H

#include "types.h"

struct EXRELOFFSET16
{ // 0x2
    /* 0x0 */ s16 RelOffset;
};

struct EXRELOFFSET16x16
{ // 0x4
    /* 0x0:0 */ u32 Data : 16;
    /* 0x2:0 */ s32 RelOffset : 16;
};

struct EXRELOFFSET32
{
    s32 RelOffset;
};

struct EXRELOFFSET24x8
{ // 0x4
    /* 0x0:0 */ u32 Data : 8;
    /* 0x1:0 */ s32 RelOffset : 24;
};

struct EXABSOFFSET32
{ // 0x4
    /* 0x0 */ u32 AbsOffset;
};

template <typename T> struct EXRelPtr
{
};

template <typename T> struct EXRelPtr16
{
};

template <typename T> struct EXRelPtr24
{
};

struct EXRelPtr<unsigned int>
{
protected:
    EXRELOFFSET32 m_rPtr;

public:
    // EXRelPtr<unsigned int>& operator=();
    EXRelPtr();
    // EXRelPtr();
    EXRELOFFSET32& RelPtr();
    // u32* operator unsigned int*();
};

struct EXRelPtr<const char>
{ // 0x4
protected:
    /* 0x0 */ EXRELOFFSET32 m_rPtr;

public:
    // EXRelPtr<const char>& operator=();
    EXRelPtr();
    // EXRelPtr();
    EXRELOFFSET32& RelPtr();
    // char* operator char*();
};

struct EXRelPtr<long long unsigned int>
{ // 0x4
protected:
    /* 0x0 */ EXRELOFFSET32 m_rPtr;

public:
    // EXRelPtr<long long unsigned int>& operator=();
    // EXRelPtr();
    // EXRelPtr();
    EXRELOFFSET32& RelPtr();
    // u128* operator unsigned long long*();
};

struct EXRelPtr16<unsigned char>
{ // 0x2
protected:
    /* 0x0 */ EXRELOFFSET16 m_rPtr;

public:
    // EXRelPtr16<unsigned char>& operator=();
    // EXRelPtr16();
    // EXRelPtr16();
    EXRELOFFSET16& RelPtr();
    // u8* operator unsigned char*();
};

struct EXRelPtr24<int>
{ // 0x4
protected:
    EXRELOFFSET24x8 m_rPtr;

public:
    // EXRelPtr24<int>& operator=();
    // EXRelPtr24();
    // EXRelPtr24();
    EXRELOFFSET24x8& RelPtr();
    // s32* operator int*();
};

#endif
