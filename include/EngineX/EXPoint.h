#ifndef EXPOINT_H
#define EXPOINT_H

#include <types.h>

struct EXPOINT
{
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
};

struct EXPoint : EXPOINT
{
    EXPoint();
    // EXPoint();
    // EXPoint();
    // EXPoint();
    void Set();
    // EXPoint& operator=();
    // EXPoint& operator=();
    // EXPoint& operator+=();
    // EXPoint& operator-=();
    // EXPOINT* operator EXPOINT*();
};

struct EXPOINTF
{
    /* 0x0 */ float x;
    /* 0x4 */ float y;
};

struct EXPointf : EXPOINTF
{
    EXPointf();
    // EXPointf();
    // EXPointf();
    // EXPointf();
    void Set();
    // EXPointf& operator=();
    // EXPointf& operator=();
    // EXPointf& operator+=();
    // EXPointf& operator-=();
    // EXPOINTF* operator EXPOINTF*();
};

#endif
