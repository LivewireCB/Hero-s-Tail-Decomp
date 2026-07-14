#ifndef EXRELPTR_H
#define EXRELPTR_H

#include "types.h"

struct EXRELOFFSET32
{
    s32 RelOffset;
};

struct EXRELOFFSET24x8
{ // 0x4
    /* 0x0:0 */ u32 Data : 8;
    /* 0x1:0 */ s32 RelOffset : 24;
};

template <typename T> struct EXRelPtr
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
