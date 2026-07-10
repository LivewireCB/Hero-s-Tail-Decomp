#ifndef EXSCRATCHPAD_H
#define EXSCRATCHPAD_H

#include "types.h"

struct EXScratchPad
{
    static u8* m_pStart;
    static u32 m_AllocSeq;
    /* 0x0 */ void* m_pAlloc;
    /* 0x4 */ u32 m_AllocSize;
    /* 0x8 */ u32 m_Seq;

    // EXScratchPad& operator=();
    // EXScratchPad();
    // EXScratchPad();
    // EXScratchPad(EXScratchPad*, int, void);
    u32 FreeBytes();
    void* Claim(unsigned long);
    void* Cache();
    void Release();
    static void MemCpy(/* parameters unknown */);
};

#endif // EXSCRATCHPAD_H
