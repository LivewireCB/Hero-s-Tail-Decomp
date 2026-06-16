#include "include/EngineX/EXAnimCache.h"

void EXAnimCache::ReloadSeqToMainCache(EXAnimCacheEntry* cache, u8* data)
{
}

void EXAnimCacheEntry::RemoveSeqFromMainCache()
{
}

void EXAnimCacheEntry::WaitCopyToMainCache() const
{
    bool flagCheck;

    flagCheck = (m_Flags & 1);

    if (flagCheck == 0)
    {
        return;
    }

    do
    {
    } while (flagCheck);
}

// u8* EXAnimCacheEntry::GetValidPtrToData(EXAnimStreamInfo&)
// {
// }

void EXAnimCacheEntry::WaitCopyToSubCache() const
{
    bool flagCheck;

    flagCheck = (m_Flags & 2);

    if (flagCheck == 0)
    {
        return;
    }

    do
    {
    } while (flagCheck);
}

EXAnimCache::EXAnimCache()
{
    m_pMainEntries = NULL;
    m_pMainCache = NULL;
    m_pSubCache = NULL;
    m_bDiscardSeqFlag = NULL;
}

Bool EXAnimCache::AllocateMainCache(u64 unk0, u64 unk1)
{
}

void EXAnimCache::FreeMainCache()
{
}

Bool EXAnimCache::AddSeqToMainCache(unsigned char*, unsigned long, unsigned long, unsigned long,
                                    EXAnimCacheEntry*&)
{
}

void EXAnimCache::StartCopyToMainCache(void*, void*, unsigned long, unsigned short*,
                                       unsigned short) const
{
}

void EXAnimCache::DefragMainCache()
{
}

void EXAnimCache::WaitCopyToMainCacheAll()
{
}

Bool EXAnimCache::AllocateSubCache(unsigned long, unsigned long)
{
}

void EXAnimCache::FreeSubCache()
{
}

Bool EXAnimCache::AddSeqToSubCache(EXAnimCacheEntry*, long, long)
{
}

void EXAnimCache::StartCopyToSubCache(void*, void*, unsigned long, unsigned short*,
                                      unsigned short) const
{
}

void EXAnimCache::DefragSubCache()
{
}

void EXAnimCache::InvalidateSubCache()
{
}

void EXAnimCache::WaitCopyToSubCacheAll()
{
}
