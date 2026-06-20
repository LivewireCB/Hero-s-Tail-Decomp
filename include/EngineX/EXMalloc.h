#ifndef EXMALLOC_H
#define EXMALLOC_H

#include "types.h"
#include <EngineX/EXMemoryManager.h>
#include <EngineX/EXList.h>

struct EXMemBlock;

struct EXMemCacheEntry
{
    s16 m_Time;
    u8 m_Flags;
    s8 m_ct;
    EXMemBlock* m_pMem;
    EXMEMCALLBACK* m_pFunc;
    u32 m_pad0;
};

struct EXMemCacheBlock
{
    int UsedCount;
    EXMemCacheEntry* pBlock;
};

template <typename T, typename TRef> struct EXDataArray
{
    int m_iAlloc;
    int m_iGrowBy;
    int m_iSize;
    EXMemCacheBlock* m_pData;

    EXDataArray();
    // EXDataArray();
    EXDataArray(EXDataArray<T, TRef>*, int, void);
    void Init();
    int Size();
    int AllocSize();
    int GetUpperBound();
    void SetSize();
    void SetGrowBy(EXDataArray<T, TRef>*, int, void);
    void AllocMem(EXDataArray<T, TRef>*, int, void);
    void FreeExtra();
    void Empty();
    void RemoveAll();
    void SetAt();
    EXMemCacheBlock GetAt();
    EXMemCacheBlock& ElementAt();
    EXMemCacheBlock* GetData();
    // EXMemCacheBlock* GetData();
    void SetAtGrow();
    int Add();
    int Append();
    void Copy();
    EXMemCacheBlock& AddSpace();
    s32 AddUnique();
    s32 Find();
    // EXMemCacheBlock& operator[]();
    // EXMemCacheBlock& operator[]();
    void InsertAt();
    void RemoveAt();
    // void InsertAt();
    // EXDataArray<EXMemCacheBlock,const EXMemCacheBlock &>& operator=();
    void GrowArray();
};

struct EXMemCacheArray
{
    EXDataArray<EXMemCacheBlock, const EXMemCacheBlock&> m_Blocks;

    // EXMemCacheArray& operator=();
    EXMemCacheArray();
    // EXMemCacheArray();
    EXMemCacheArray(EXMemCacheArray*, int, void);
    // EXMemCacheEntry* Get();
    void RemoveEntry();
    void RemoveAll();
};

struct EXMemBlock
{
    union
    {
        EXMemBlock* m_pPrev;
        void* m_pOwner;
    };
    union
    {
        EXMemBlock* m_pNext;
        EXMEMCALLBACK* m_pFunc;
        EXMemCacheEntry* m_pCache;
    };
    u32 m_Size_Flags;
    u32 m_PrevSize_Align;

    // EXMemBlock& operator=();
    EXMemBlock();
    // EXMemBlock();
    void SetFlag();
    void ClrFlag();
    void SetFlags();
    void SetOwner();
    void* Owner();
    void SetTime();
    void SetFunc();
    Bool LockMem();
    char* AlignText();
    void Init(u32);
    void Copy(EXMemBlock* pMem);
    void* Data();
    EXMEMCALLBACK* Func();
    Bool CallFunction();
    void SetAlignFlags();
    u32 AlignFlags();
    u32 Alignment();
    u32 IsFree();
    u32 IsMoveable();
    u32 IsCache();
    u32 Flags();
    void SetPrevSize();
    void SetSize();
    u32 Size();
    void SetDefaults();
    EXMemBlock* PrevLink();
    EXMemBlock* NextLink();
    EXMemBlock* LinkAddr();
    EXMemBlock* Split(size_t size, Bool fHi);
    void Add();
    void Remove();
    void JoinNext();
    s32 GetSize();
};

struct EXMemHeap
{
    void* m_pMemAlloc;
    EXMemBlock* m_pStart;
    EXMemBlock* m_pEnd;
    EXDListItem m_FreeList[5];
    EXMemCacheArray m_CacheLists[3];
    s32 m_HeapId;
    u32 m_HeapSize;
    char* m_HeapName;
    static Bool m_ForceCompactHeaps;
    static Bool m_EnableCompactHeaps;
    static void (*m_PreCompactCallback)(/* parameters unknown */);
    static void (*m_PostCompactCallback)(/* parameters unknown */);
    unsigned int m_DebugStats[4];

    // static EXFixedArray<unsigned int, 7> m_gAlignTbl;
    // static EXFixedArray<const char*, 7> m_gAlignTxt;

    // EXMemHeap& operator=();
    EXMemHeap();
    // EXMemHeap();
    EXMemHeap(EXMemHeap*, int, void);
    void Init(void* pMem, size_t size, long HeapId, char* HeapName);
    void* MemAlloc();
    EXMemBlock* MemStart();
    EXMemBlock* MemEnd();
    char* Name();
    u32 HeapId();
    u32 HeapSize();
    EXMemBlock* FindLargestFree();
    void* _EXAlloc(unsigned int, unsigned long);
    void* _EXAllocPure(unsigned int, unsigned long);
    void* _EXAllocRel();
    void* _EXAllocFnc();
    void* _EXCache();
    void* _EXCacheDel();
    void* _EXRealloc();
    void EXFree();
    static void CompactHeaps(/* parameters unknown */);
    static void ForceCompactHeaps(/* parameters unknown */);
    static void EnableAutoHeapCompact(/* parameters unknown */);
    static void SetCompactCallbacks(/* parameters unknown */);
    void Update();
    static void UpdateAllHeaps(/* parameters unknown */);
    static void UpdateHeapStats(/* parameters unknown */);
    static void FlushAllCacheMem(/* parameters unknown */);
    static void RegisterMallocVars(/* parameters unknown */);
    void Debug_CalculateStats();
    u32 Debug_Stats();

    void* _sysAlloc(unsigned int, unsigned long);
    void* _sysAllocRel();
    void* _sysAllocFnc();
    void* _sysCache();
    void* _sysCacheDel();
    void* _sysRealloc(void*, u32);
    EXMemBlock* _sysFree();
    void _sysSetAsCache();
    void UpdateFirstLastFree();
    EXMemBlock* _FindFirstFree();
    EXMemBlock* _FindLastFree();
    EXMemBlock* _FindFree();
    EXMemBlock* _FindLargestFree();
    EXMemBlock* _FindFreeLastChance();
    EXMemBlock* _FindFreeCacheMem();
    EXMemBlock* SplitAlignMemory(EXMemBlock* pMem, size_t alignment) const;
    EXMemBlock* SplitAlignMemory2(EXMemBlock* pMem, size_t alignment, size_t size) const;
    EXMemBlock* AllocBlock();
    EXMemBlock* AddFreeList();
    EXMemBlock* AddFreeList2();
    EXMemBlock* CompactMemLo();
    EXMemBlock* CompactMemHi();
    EXMemBlock* CompactMemHiAlignMemory();
    void AddCache();
    void RemoveCache();
    void AgeCacheMem();
    void FlushCacheMem();
    Bool Compact();
};

#endif // EXMALLOC_H
