#ifndef EXSTATS_H
#define EXSTATS_H

#include "types.h"
#include "EXMalloc.h"

// TODO: FIXME:
// struct is NOT correct. look at the constructor for an example
// im fairly certain were just missing variables. The v table should be correct
struct EXBaseStats
{ // 0x18
protected:
    /* 0x00 */ u32 m_FrameCount;
    /* 0x08 */ u64 m_FrameMillisec;

public:
    // /* 0x10 */ __vtbl_ptr_type* vf730;

    // EXBaseStats& operator=();
    // ~EXBaseStats();
    EXBaseStats();
    /* vtable[1] */ virtual ~EXBaseStats();
    void FrameUpdate();
    u32 FrameCount();

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }
};

struct EXHistogram
{ // 0x98
protected:
    /* 0x00 */ s16 m_NumBins;
    /* 0x02 */ s16 m_DataBufIndex;
    /* 0x04 */ s32* m_BinRanges;
    /* 0x08 */ s32* m_BinCounts;
    /* 0x0c */ s32 m_NumCounts;
    /* 0x10 */ int m_DataBuf[32];
    /* 0x90 */ s32 m_DataTotal;
    /* 0x94 */ Bool m_bPaused;

public:
    // EXHistogram& operator=();
    EXHistogram();
    // EXHistogram();
    // EXHistogram();
    ~EXHistogram();
    void Reset();
    // void Add(EXHistogram*, int, void);
    s32 NumBins();
    s32 NumCounts();
    s32 DataTotal();
    void BinData();
    float Average();
    float MovingAverage();
    void Pause();
    void UnPause();
};

#endif // EXSTATS_H
