#ifndef EXANIMCACHE_H
#define EXANIMCACHE_H

#include "types.h"
#include "EXMemoryManager.h"

struct EXAnimCacheEntry
{
    /* 0x00 */ u32 m_SeqHash;
    /* 0x04 */ u32 m_GeoHash;
    /* 0x08 */ u32 m_Size;
    /* 0x0c */ u32 m_SubSize;
    /* 0x10 */ u32 m_TimeStamp;
    /* 0x14 */ s32 m_StreamBlockOffset;
    /* 0x18 */ u8* m_pDataSubCache;
    /* 0x1c */ u32 m_MainCacheInd;
    /* 0x20 */ u16 m_Flags;
    /* 0x22 */ u16 m_MainRefCount;

    // EXAnimCacheEntry& operator=();
    EXAnimCacheEntry();
    // EXAnimCacheEntry();
    void RemoveSeqFromMainCache();
    void WaitCopyToMainCache() const;
    // u8* GetValidPtrToData(EXAnimStreamInfo&);
    void WaitCopyToSubCache() const;
    void DeleteFromMain();
    Bool isInMainCache();
    void DeleteFromSub();
    Bool isInSubCache();
    Bool isStreamBlockInSubCache();
};

struct EXAnimCache
{
    /* 0x00 */ EXAnimCacheEntry* m_pMainEntries;
    /* 0x04 */ s32 m_NumMainEntries;
    /* 0x08 */ s32 m_MaxMainEntries;
    /* 0x0c */ u32 m_MaxEntriesMask;
    /* 0x10 */ u8* m_pMainCache;
    /* 0x14 */ u32 m_MainSize;
    /* 0x18 */ u32 m_MainNext;
    /* 0x1c */ u8* m_pSubCache;
    /* 0x20 */ u32 m_SubSize;
    /* 0x24 */ u32 m_SubNext;
    /* 0x28 */ u32 m_SubAutoDeleteAge;
    /* 0x2c */ Bool m_bDiscardSeqFlag;

    // EXAnimCache& operator=();
    EXAnimCache();
    // EXAnimCache();
    // EXAnimCache(EXAnimCache*, int, void);
    void Shutdown();
    Bool AllocateMainCache(u64, u64);
    void FreeMainCache();
    Bool AddSeqToMainCache(unsigned char*, unsigned long, unsigned long, unsigned long,
                           EXAnimCacheEntry*&);
    Bool AllocateSubCache(unsigned long, unsigned long);
    void FreeSubCache();
    Bool AddSeqToSubCache(EXAnimCacheEntry*, long, long);
    void GetCacheStats();
    void ReloadSeqToMainCache(EXAnimCacheEntry* cache, u8* data);
    Bool isEnabled();
    s32 DecNumMainCacheEntries();
    void ResetMainCacheIndex();
    void SetDiscardSeqs();
    Bool DiscardSeqs();
    void InvalidateSubCache();
    u8* MainBuffer();

    void EmptyMainCache();
    void DefragMainCache();
    void StartCopyToMainCache(void*, void*, unsigned long, unsigned short*, unsigned short) const;
    void WaitCopyToMainCacheAll();
    void DefragSubCache();
    void StartCopyToSubCache(void*, void*, unsigned long, unsigned short*, unsigned short) const;
    void WaitCopyToSubCacheAll();
    s32 FindEntry();
    s32 FindFreeEntry();
};

#endif // EXANIMCACHE_H
