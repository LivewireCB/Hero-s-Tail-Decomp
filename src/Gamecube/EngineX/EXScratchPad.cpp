#include "EngineX/EXScratchPad.h"

extern u8 EXScratchPadMem[]; // idk tbh

static inline u32 ScratchPadStart()
{
    u32 Start;

    Start = (u32)EXScratchPadMem;
    Start += 0xf;
    Start &= ~0xf;
    return Start;
}

u8* EXScratchPad::m_pStart = (u8*)ScratchPadStart();

void* EXScratchPad::Claim(unsigned long SizeBytes)
{
    u32 QuadWords;
    void* pAlloc;
    s32 FreeQuadWords;

    QuadWords = (SizeBytes + 0xf) >> 4;
    pAlloc = 0;

    FreeQuadWords = 0x400 - (((s32)m_pStart - (s32)ScratchPadStart()) >> 4);

    if (FreeQuadWords > (s32)QuadWords)
    {
        pAlloc = m_pStart;
        m_pAlloc = pAlloc;
        m_AllocSize = QuadWords << 4;

        m_pStart = (u8*)pAlloc + (QuadWords << 4);
    }

    return pAlloc;
}

void EXScratchPad::Release()
{
    if (m_pAlloc == 0)
    {
        return;
    }

    m_pStart = m_pStart - m_AllocSize;
    m_pAlloc = 0;
}
