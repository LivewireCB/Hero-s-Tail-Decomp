#ifndef EXRAND_H
#define EXRAND_H

#include "types.h"

struct EXRandClass
{
    u32 m_RandShift;

    EXRandClass()
    {
        m_RandShift = 0x955;
    }

    // EXRandClass& operator=();
    // EXRandClass();
    // ~EXRandClass();
    void SetSeed(u64 Seed);
    void SetState(EXRandClass& State);
    void GetState(EXRandClass& State) const;
    u32 Rand32();
    s32 Rand31();
    s32 Rand(s32 MaxVal);
    s32 Rand(s32 MinVal, s32 MaxVal);
    float Randf();
    float Randf(float MaxVal);
    float Randf(float MinVal, float MaxVal);
};

struct EXRandFastClass
{
    u32 m_Seed;

    EXRandFastClass()
    {
        m_Seed = 1;
    }

    // EXRandFastClass& operator=();
    // EXRandFastClass();
    // ~EXRandFastClass();
    void SetSeed();
    void SetState();
    void GetState();
    u32 Rand32();
    s32 Rand31();
    s32 Rand();
    // s32 Rand();
    float Randf();
    float Randf(float MaxVal);
    // float Randf();
};

#endif // EXRAND_H
