#include "EngineX/EXAnimCache.h"

#include "EngineX/EXMemoryManager.h"

void EXAnimCache::ReloadSeqToMainCache(EXAnimCacheEntry* cache, u8* data)
{
    if (m_bDiscardSeqFlag == 0)
    {
        u64 seq = 1;
        if (m_pMainEntries == 0)
        {
            seq = 0;
        }

        if (seq == 0)
        {
            do
            {
            } while (!0);
        }

        cache->WaitCopyToMainCache();
        this->StartCopyToMainCache(cache->m_MainCacheInd + m_pMainCache, data, cache->m_Size,
                                   &cache->m_Flags, 1);
    }
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
    u32 shouldFree = 1;

    if (m_pMainEntries == NULL)
    {
        shouldFree = 0;
    }

    if (shouldFree != 0)
    {
        WaitCopyToMainCacheAll();
        FreeSubCache();

        if (m_pMainEntries != NULL)
        {
            EXFree(m_pMainEntries);
            m_pMainEntries = 0;
        }
    }
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

Bool EXAnimCache::AllocateSubCache(unsigned long unk0, unsigned long unk1)
{
    if (m_pSubCache != NULL)
    {
        do
        {
        } while (true);
    }

    if (unk0 < (0 | 65536))
    {
        do
        {
        } while (true);
    }

    _EXAlloc(unk0, 1);

    if (m_pSubCache == NULL)
    {
        do
        {
        } while (true);
    }

    return true;
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
