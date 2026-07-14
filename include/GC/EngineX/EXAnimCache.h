#ifndef EXANIMCACHE_H
#define EXANIMCACHE_H

#include "types.h"

struct EXAnimCacheEntry
{
    u32 m_SeqHash;
    u32 m_GeoHash;
    u32 m_Size;
    u32 m_SubSize;
    u32 m_TimeStamp;
    s32 m_StreamBlockOffset;
    u8* m_pDataSubCache;
    u32 m_MainCacheInd;
    u16 m_Flags;
    u16 m_MainRefCount;

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
    EXAnimCacheEntry* m_pMainEntries;
    s32 m_NumMainEntries;
    s32 m_MaxMainEntries;
    u32 m_MaxEntriesMask;
    u8* m_pMainCache;
    u32 m_MainSize;
    u32 m_MainNext;
    u8* m_pSubCache;
    u32 m_SubSize;
    u32 m_SubNext;
    u32 m_SubAutoDeleteAge;
    Bool m_bDiscardSeqFlag;

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
