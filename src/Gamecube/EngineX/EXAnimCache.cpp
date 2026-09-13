#include "EngineX/EXAnimCache.h"

#include "EngineX/EXMalloc.h"
#include "EngineX/EXMemoryManager.h"

extern u8 g_Stats[];

EXAnimCache g_AnimCache;
u32 lbl_804CBA20[2] = { 0, 0 };

// Forward decs to make this fucking compiler happy
void GC_ARAM_Read_From(void*, void*, unsigned long);
void GC_ARAM_Write_To(unsigned long, void*, unsigned long);
void GC_Die(char*);
int sprintf(char*, const char*, ...);
void* memcpy(void*, const void*, size_t);

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
    u16 refCount;
    EXAnimCache* cache = &g_AnimCache;

    if (cache->m_bDiscardSeqFlag == 0)
    {
        refCount = --m_MainRefCount;
        if (refCount == 0)
        {
            WaitCopyToMainCache();
            s32 numEntries = --cache->m_NumMainEntries;
            m_SeqHash = 0;

            if (numEntries == 0)
            {
                cache->m_MainNext = numEntries;
            }
        }
    }
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

u8* EXAnimCacheEntry::GetValidPtrToData(EXAnimStreamInfo& streamInfo)
{
    u16* streamTable = (u16*)streamInfo.m_pStreamTable;
    s32 numFrames = streamInfo.m_NumFrames;
    s32 startFrame = 0;
    s32 endFrame = numFrames - 1;
    s32 blockOffset = -1;
    s32 blockSize = 0;

    if (streamTable != NULL)
    {
        blockSize = (streamTable[0] + (streamTable[1] << 16) + 31) & ~31;
        s32 frame = streamInfo.m_StartFrame;
        s32 block = 0;
        endFrame = streamTable[2];
        u16* blockEndFrames = streamTable + 2;

        while (frame < startFrame || frame > endFrame)
        {
            block++;
            startFrame = endFrame + 1;
            endFrame = blockEndFrames[block];
        }

        if (endFrame < numFrames - 1)
        {
            endFrame++;
        }
        blockOffset = block * blockSize;
    }

    streamInfo.m_StrmStartFrame = startFrame;
    streamInfo.m_StrmNumFrames = endFrame - startFrame + 1;
    streamInfo.m_StrmRelFrame = streamInfo.m_StartFrame - startFrame;

    if (!isInSubCache() || m_StreamBlockOffset != blockOffset)
    {
        g_AnimCache.AddSeqToSubCache(this, blockOffset, blockSize);
    }

    WaitCopyToSubCache();
    m_TimeStamp = *(u32*)g_Stats;
    return m_pDataSubCache;
}

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
    u32 allocated = 1;
    if (m_pMainEntries == NULL)
    {
        allocated = 0;
    }

    if (allocated != 0)
    {
        do
        {
        } while (true);
    }

    if ((unk0 & (unk0 - 1)) != 0)
    {
        do
        {
        } while (true);
    }

    if (unk0 > 2048)
    {
        do
        {
        } while (true);
    }

    m_MaxEntriesMask = unk0 - 1;
    m_pMainEntries = (EXAnimCacheEntry*)_EXAlloc(unk0 * sizeof(EXAnimCacheEntry), 1);
    if (m_pMainEntries == NULL)
    {
        do
        {
        } while (true);
    }

    m_NumMainEntries = 0;
    m_MaxMainEntries = unk0;
    for (s32 i = 0; i < m_MaxMainEntries; i++)
    {
        m_pMainEntries[i].m_SeqHash = 0;
    }

    u32 mainCacheAddress = 0x1000000 - unk1;
    lbl_804CBA20[0] = mainCacheAddress;
    m_pMainCache = (u8*)mainCacheAddress;
    if (m_pMainCache == NULL)
    {
        FreeMainCache();
        do
        {
        } while (true);
    }

    m_MainSize = unk1;
    m_MainNext = 0;
    return true;
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

Bool EXAnimCache::AddSeqToMainCache(unsigned char*, unsigned long size, unsigned long seqHash,
                                    unsigned long geoHash, EXAnimCacheEntry*& entry)
{
    if (m_bDiscardSeqFlag != 0)
    {
        return true;
    }

    u32 isAllocated = 1;
    if (m_pMainEntries == NULL)
    {
        isAllocated = 0;
    }
    if (isAllocated == 0)
    {
        do
        {
        } while (true);
    }

    s32 foundIndex = FindEntry(seqHash, geoHash);

    if (foundIndex >= 0)
    {
        EXAnimCacheEntry* foundEntry = &m_pMainEntries[foundIndex];
        foundEntry->m_MainRefCount++;
        entry = foundEntry;
        return true;
    }

    entry = NULL;
    size += 31;
    s32 freeIndex = FindFreeEntry(seqHash, geoHash);

    if (freeIndex < 0)
    {
        do
        {
        } while (true);
    }

    u32 alignedSize = size & ~31;
    EXAnimCacheEntry* newEntry = &m_pMainEntries[freeIndex];
    if (m_MainNext + alignedSize > m_MainSize)
    {
        DefragMainCache();
        if (m_MainNext + alignedSize > m_MainSize)
        {
            do
            {
            } while (true);
        }
    }

    entry = newEntry;
    newEntry->m_SeqHash = seqHash;
    newEntry->m_GeoHash = geoHash;
    newEntry->m_Size = alignedSize;
    newEntry->m_SubSize = 0;
    newEntry->m_MainCacheInd = m_MainNext;
    newEntry->m_StreamBlockOffset = -1;
    newEntry->m_pDataSubCache = NULL;
    newEntry->m_Flags = 0;
    entry->m_MainRefCount = 1;
    m_MainNext += alignedSize;
    m_NumMainEntries++;
    return true;
}

void EXAnimCache::StartCopyToMainCache(void* destination, void* source, unsigned long size,
                                       unsigned short* flags, unsigned short copyFlag) const
{
    *flags |= copyFlag;
    GC_ARAM_Write_To((unsigned long)destination, source, size);
    *flags &= ~copyFlag;
}

void EXAnimCache::DefragMainCache()
{
    EXAnimCacheEntry* entries[2048];
    s32 numEntries = 0;

    for (s32 i = 0; i < m_MaxMainEntries; i++)
    {
        EXAnimCacheEntry* entry = &m_pMainEntries[i];
        if (entry->isInMainCache())
        {
            entries[numEntries++] = entry;
            entry->WaitCopyToMainCache();
            entry->WaitCopyToSubCache();
        }
    }

    for (s32 i = 0; i < numEntries - 1; i++)
    {
        for (s32 j = i + 1; j < numEntries; j++)
        {
            if (entries[i]->m_MainCacheInd > entries[j]->m_MainCacheInd)
            {
                EXAnimCacheEntry* swap = entries[i];
                entries[i] = entries[j];
                entries[j] = swap;
            }
        }
    }

    u32 next = 0;
    for (s32 i = 0; i < numEntries; i++)
    {
        EXAnimCacheEntry* entry = entries[i];
        if (entry->m_MainCacheInd != next)
        {
            u8* source = m_pMainCache + entry->m_MainCacheInd;
            u8* destination = m_pMainCache + next;
            u32 remaining = entry->m_Size;
            u32 overlap = 0;

            if (destination >= source)
            {
                overlap = destination < source + remaining;
            }
            if (overlap != 0)
            {
                source += remaining;
                destination += remaining;
            }

            while (remaining != 0)
            {
                u32 maxChunkSize = 0x10000;
                u32 chunkSize = remaining > maxChunkSize ? maxChunkSize : remaining;
                if (overlap != 0)
                {
                    source -= chunkSize;
                    destination -= chunkSize;
                }

                StartCopyToSubCache(m_pSubCache, source, chunkSize, &entry->m_Flags, 2);
                entry->WaitCopyToSubCache();
                StartCopyToMainCache(destination, m_pSubCache, chunkSize, &entry->m_Flags, 1);
                entry->WaitCopyToMainCache();

                if (overlap == 0)
                {
                    source += chunkSize;
                    destination += chunkSize;
                }
                remaining -= chunkSize;
            }
            entry->m_MainCacheInd = next;
        }
        next += entry->m_Size;
    }

    m_MainNext = next;
    InvalidateSubCache();
}

void EXAnimCache::WaitCopyToMainCacheAll()
{
    for (s32 i = 0; i < m_MaxMainEntries; i++)
    {
        EXAnimCacheEntry* entry =
            (EXAnimCacheEntry*)((u8*)m_pMainEntries + i * sizeof(EXAnimCacheEntry));
        if (entry->isInMainCache())
        {
            entry->WaitCopyToMainCache();
        }
    }
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

    m_pSubCache = (u8*)_EXAlloc(unk0, 1);

    if (m_pSubCache == NULL)
    {
        do
        {
        } while (true);
    }

    m_SubSize = unk0;
    m_SubNext = 0;
    m_SubAutoDeleteAge = unk1;
    return true;
}

void EXAnimCache::FreeSubCache()
{
    u32 isAllocated = 1;
    if (m_pMainEntries == NULL)
    {
        isAllocated = 0;
    }

    if (isAllocated != 0)
    {
        WaitCopyToSubCacheAll();
        for (s32 i = 0; i < m_MaxMainEntries; i++)
        {
            EXAnimCacheEntry* entry =
                (EXAnimCacheEntry*)((u8*)m_pMainEntries + i * sizeof(EXAnimCacheEntry));
            if (entry->isInMainCache())
            {
                entry->DeleteFromSub();
            }
        }

        if (m_pSubCache != NULL)
        {
            EXFree(m_pSubCache);
            m_pSubCache = NULL;
        }
    }
}

Bool EXAnimCache::AddSeqToSubCache(EXAnimCacheEntry* entry, long blockOffset, long blockSize)
{
    u32 isAllocated = 1;
    if (m_pMainEntries == NULL)
    {
        isAllocated = 0;
    }
    if (isAllocated == 0)
    {
        return false;
    }
    if (m_pSubCache == NULL)
    {
        do
        {
        } while (true);
    }
    if (entry == NULL)
    {
        do
        {
        } while (true);
    }

    if (!entry->isInSubCache() || entry->m_StreamBlockOffset != blockOffset)
    {
        entry->m_StreamBlockOffset = blockOffset;
        s32 copySize;
        if (blockOffset < 0)
        {
            copySize = entry->m_Size;
            blockOffset = 0;
        }
        else
        {
            copySize = blockSize;
        }

        if (m_SubNext + copySize > m_SubSize)
        {
            DefragSubCache();
            if (m_SubNext + copySize > m_SubSize)
            {
                InvalidateSubCache();
                if (m_SubNext + copySize > m_SubSize)
                {
                    char message[256];
                    sprintf(message, "Anim subcache full, has %d, needs %d\n", m_SubSize, copySize);
                    GC_Die(message);
                    do
                    {
                    } while (true);
                }
            }
        }

        entry->WaitCopyToMainCache();
        StartCopyToSubCache(entry->m_pDataSubCache = m_pSubCache + m_SubNext,
                            m_pMainCache + entry->m_MainCacheInd + blockOffset,
                            entry->m_SubSize = copySize, &entry->m_Flags, 2);
        m_SubNext += entry->m_SubSize;
    }
    entry->m_TimeStamp = *(u32*)g_Stats;
    return true;
}

void EXAnimCache::StartCopyToSubCache(void* destination, void* source, unsigned long size,
                                      unsigned short* flags, unsigned short copyFlag) const
{
    *flags |= copyFlag;
    GC_ARAM_Read_From(destination, source, size);
    *flags &= ~copyFlag;
}

void EXAnimCache::DefragSubCache()
{
    EXAnimCacheEntry* entries[2048];
    u32 frameCount = *(u32*)g_Stats;
    s32 numEntries = 0;
    EXAnimCacheEntry** nextEntry = entries - 1;

    for (s32 i = 0; i < m_MaxMainEntries; i++)
    {
        EXAnimCacheEntry* entry = &m_pMainEntries[i];
        if (entry->isInMainCache())
        {
            if (entry->isInSubCache())
            {
                entry->WaitCopyToSubCache();
                if (frameCount - entry->m_TimeStamp > m_SubAutoDeleteAge)
                {
                    entry->DeleteFromSub();
                }
                else
                {
                    *++nextEntry = entry;
                    numEntries++;
                }
            }
        }
    }

    for (s32 i = 0; i < numEntries - 1; i++)
    {
        for (s32 j = i + 1; j < numEntries; j++)
        {
            if (entries[i]->m_pDataSubCache > entries[j]->m_pDataSubCache)
            {
                EXAnimCacheEntry* swap = entries[i];
                entries[i] = entries[j];
                entries[j] = swap;
            }
        }
    }

    u32 next = 0;
    for (s32 i = 0; i < numEntries; i++)
    {
        EXAnimCacheEntry* entry = entries[i];
        if ((u32)(entry->m_pDataSubCache - m_pSubCache) != next)
        {
            memcpy(m_pSubCache + next, entry->m_pDataSubCache, entry->m_SubSize);
            entry->m_pDataSubCache = m_pSubCache + next;
        }
        next += entry->m_SubSize;
    }
    m_SubNext = next;
}

void EXAnimCache::InvalidateSubCache()
{
    WaitCopyToSubCacheAll();
    for (s32 i = 0; i < m_MaxMainEntries; i++)
    {
        EXAnimCacheEntry* entry =
            (EXAnimCacheEntry*)((u8*)m_pMainEntries + i * sizeof(EXAnimCacheEntry));
        if (entry->isInMainCache())
        {
            if (entry->isInSubCache())
            {
                entry->DeleteFromSub();
            }
        }
    }
    m_SubNext = 0;
}

void EXAnimCache::WaitCopyToSubCacheAll()
{
    for (s32 i = 0; i < m_MaxMainEntries; i++)
    {
        EXAnimCacheEntry* entry =
            (EXAnimCacheEntry*)((u8*)m_pMainEntries + i * sizeof(EXAnimCacheEntry));
        if (entry->isInMainCache())
        {
            entry->WaitCopyToSubCache();
        }
    }
}
