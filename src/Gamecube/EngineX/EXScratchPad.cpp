#include "EngineX/EXScratchPad.h"

// forcing data section here
u8* EXScratchPad::m_pStart __attribute__((section(".sbss")));

extern u8 EXScratchPadMem[]; // idk tbh

// i LOVE register problemss
void* EXScratchPad::Claim(u64 SizeBytes)
{
    u32 QuadWords;
    void* pAlloc;

    QuadWords = (u32)EXScratchPadMem;
    QuadWords = QuadWords + 0xf;
    QuadWords = QuadWords & ~0xf;
    QuadWords = (u32)m_pStart - QuadWords;
    QuadWords = (u32)((s32)QuadWords >> 4);
    QuadWords = 0x400 - QuadWords;
    pAlloc = 0;

    if ((s32)QuadWords > (s32)((SizeBytes + 0xf) >> 4))
    {
        QuadWords = (SizeBytes + 0xf) >> 4;
        QuadWords <<= 4;
        pAlloc = m_pStart;
        m_pAlloc = pAlloc;
        m_AllocSize = QuadWords;

        m_pStart = (u8*)pAlloc + QuadWords;
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
