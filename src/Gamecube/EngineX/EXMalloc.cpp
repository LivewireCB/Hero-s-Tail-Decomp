#include "libc/stddef.h"
#include <EngineX/EXMalloc.h>
#include <EngineX/EXMemoryManager.h>

#include "EngineX/EXFixedArray.h"

EXMemHeap _SDataHeap;
EXMemHeap _LDataHeap;
EXMemHeap* _SystemHeapList[4];

EXFixedArray<unsigned int, 7> EXMemHeap::m_gAlignTbl = { 0, 32, 64, 128, 1024, 2048, 8192 };
EXFixedArray<const char*, 7> EXMemHeap::m_gAlignTxt = { "<default>", "Align32",   "Align64",
                                                        "Align128",  "Align1024", "Align2048",
                                                        "Align8192" };

void EXMemBlock::Init(size_t size)
{
    m_pNext = 0;
    m_Size_Flags = size | 1;
    m_PrevSize_Align &= ~0xFU;
    m_pOwner = 0;
}

// Bit of a guess on the final if statement. I have no clue sometimes
void EXMemBlock::Copy(EXMemBlock* pMem)
{
    m_PrevSize_Align = (m_PrevSize_Align & ~0xF) | (pMem->m_PrevSize_Align & 0xF);
    m_Size_Flags = (m_Size_Flags & ~0xF) | (pMem->m_Size_Flags & 0xF);

    EXMEMCALLBACK* p = pMem->m_pFunc;

    if (m_Size_Flags & 4)
    {
        m_pCache->m_pFunc = p;
    }
    else
    {
        m_pFunc = p;
    }

    m_pOwner = pMem->m_pOwner;

    if (m_pOwner != 0)
    {
        *(void**)m_pOwner = (void*)(this + 1);
    }
}

// TODO: FIX THIS FUNCTION. IT LOOKS FUCKING HORRIBLE
EXMemBlock* EXMemBlock::Split(size_t size, Bool fHi)
{
    size_t memsize;
    size_t nSplitSize;
    size_t size2;
    size_t s;

    memsize = m_Size_Flags & ~0xFU;
    size2 = size;
    nSplitSize = memsize - size;

    if (nSplitSize <= 0x1Fu)
        return this;

    s = nSplitSize - 0x10;
    if (fHi)
    {
        size = s;
        s = size2;
    }

    EXMemBlock* pNew = (EXMemBlock*)((char*)this + (size + 0x10u));
    m_Size_Flags = (m_Size_Flags & 0xFU) | size;
    pNew->m_Size_Flags = s | 1;
    pNew->m_PrevSize_Align = (pNew->m_PrevSize_Align & 0xFU) | size;
    EXMemBlock* pNext = (EXMemBlock*)((char*)this + (memsize + 0x10u));
    pNext->m_PrevSize_Align = (pNext->m_PrevSize_Align & 0xFU) | s;
    return pNew;
}

void EXMemHeap::Init(void* pMem, size_t size, long HeapId, char* HeapName)
{
    EXMemBlock* pStart;
    u32 n;
    EXMemBlock* pNext;
    u32 fl;
    EXDListItem* m;
    int d;
}

EXMemBlock* EXMemHeap::SplitAlignMemory(EXMemBlock* pMem, size_t alignment) const
{
    u32 aptr;
    EXMemBlock* pPrev;
    EXMemBlock* pNext;
}

EXMemBlock* EXMemHeap::SplitAlignMemory2(EXMemBlock* pMem, size_t alignment, size_t size) const
{
    u32 aptr;
    EXMemBlock* pPrev;
    EXMemBlock* pNext;
}

void* EXMemHeap::_EXAlloc(size_t size, unsigned long unk0)
{
    EXMemHeap::_sysAlloc(size, unk0);
}

void* EXMemHeap::_EXAllocPure(size_t size, unsigned long unk0)
{
    EXMemHeap::_sysAlloc(size, unk0);
}
