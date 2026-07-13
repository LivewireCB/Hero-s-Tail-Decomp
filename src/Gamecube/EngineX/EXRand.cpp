#include <EngineX/EXRand.h>

EXRandFastClass g_EXRandFastClass;
EXRandClass g_EXRandClass;

static const double lbl_803D5948 = 4503601774854144.0;
static const float lbl_803D5950 = 4.656613e-10f;

void EXRandClass::SetSeed(u64 Seed)
{
    m_RandShift = Seed;
}

void EXRandClass::SetState(EXRandClass& State)
{
    m_RandShift = State.m_RandShift;
}

void EXRandClass::GetState(EXRandClass& State) const
{
    State.m_RandShift = m_RandShift;
}

// I believe that this is a Linear Congruential Generator algorithm
#define MULTIPLIER 0x343fd // 214013
#define INCREMENT 0x269ec3 // 2531011

u32 EXRandClass::Rand32(void)
{
    u32 rand1;
    u32 rand2;

    rand1 = m_RandShift * MULTIPLIER + INCREMENT;
    rand2 = rand1 * MULTIPLIER + INCREMENT;

    m_RandShift = rand2;
    return rand1 & 0xffff0000 | rand2 >> 16;
}

// ToDo: Not exactly correct, may correct itself when rodata sectioning is fixed.
// Function shows as 100% but the float values in objdiff are not correct.
f32 EXRandClass::Randf(void)
{
    return (s32)(Rand32() >> 1) * (4.656613e-10f);
}
