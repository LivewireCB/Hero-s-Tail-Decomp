#include <EngineX/EXMemoryManager.h>

#include <EngineX/EXMalloc.h>
#include "EngineX/GC/GCMalloc.h"

extern EXMemHeap* _SystemHeap;
extern EXMemHeap* _SystemHeapList[4];

// TODO: this function needs -fforce-addr off
void* _EXAlloc(size_t size, EXMemFlags memflags)
{
    if (_SystemHeap == 0)
    {
        _initalize_heap_memory();
    }

    return _SystemHeap->_sysAlloc(size, memflags);
}

void* _EXAllocPure(size_t size, EXMemFlags memflags)
{
    if (_SystemHeap == 0)
    {
        _initalize_heap_memory();
    }

    return _SystemHeap->_sysAlloc(size, memflags);
}

void* _EXRealloc(void* pData, size_t size)
{
    if (_SystemHeap == 0)
    {
        _initalize_heap_memory();
    }

    EXMemHeap* pHeap;
    if (pData != 0)
    {
        EXMemHeap** ppHeap = _SystemHeapList;
        int heapsRemaining = 4;
        do
        {
            pHeap = *ppHeap++;
            if (pHeap != 0 && pData >= pHeap->m_pStart && pData <= pHeap->m_pEnd)
            {
                break;
            }
        } while (--heapsRemaining != 0 || (pHeap = 0, false));
    }
    else
    {
        pHeap = _SystemHeap;
    }

    return pHeap->_sysRealloc(pData, size);
}

void EXFree(void* pData)
{
    if (pData == 0)
    {
        return;
    }

    EXMemBlock* pMem = (EXMemBlock*)pData - 1;
    EXMemHeap** ppHeap = _SystemHeapList;
    EXMemHeap* pHeap;
    int heapsRemaining = 4;
    do
    {
        pHeap = *ppHeap++;
        if (pHeap != 0 && pData >= pHeap->m_pStart && pData <= pHeap->m_pEnd)
        {
            break;
        }
    } while (--heapsRemaining != 0 || (pHeap = 0, false));

    if (pHeap == 0)
    {
        while (true)
        {
        }
    }

    pHeap->_sysFree(pMem);
}

void EXAllocSetTime(void* pData, s16 nTime)
{
    EXMemBlock* pMem = (EXMemBlock*)pData - 1;
    nTime = nTime < 0 ? -nTime : nTime;

    if (pMem->m_Size_Flags & 4)
    {
        pMem->m_pCache->m_Time = nTime;
    }
}

void EXAllocSetOwner(void* pData, void* pOwner)
{
    EXMemBlock* pMem = (EXMemBlock*)pData - 1;
    pMem->m_pOwner = pOwner;

    if (pOwner != 0)
    {
        *(void**)pOwner = pData;
    }
}

void EXAllocSetReloc(void* pData, Bool fReloc)
{
    EXMemBlock* pMem = (EXMemBlock*)pData - 1;
    if (fReloc)
    {
        pMem->m_Size_Flags |= 2;
    }
    else
    {
        pMem->m_Size_Flags &= ~2;
    }
}

void EXAllocSetFunc(void* pData, EXMEMCALLBACK* pFunc)
{
    EXMemBlock* pMem = (EXMemBlock*)pData - 1;
    if (pMem->m_Size_Flags & 4)
    {
        pMem->m_pCache->m_pFunc = pFunc;
    }
    else
    {
        pMem->m_pFunc = pFunc;
    }
}

void EXAllocSetCacheDel(void* pData, s16 time, void** pOwner)
{
    EXMemHeap** ppHeap = _SystemHeapList;
    EXMemHeap* pHeap;
    int heapsRemaining = 4;
    do
    {
        pHeap = *ppHeap++;
        if (pHeap != 0 && pData >= pHeap->m_pStart && pData <= pHeap->m_pEnd)
        {
            break;
        }
    } while (--heapsRemaining != 0 || (pHeap = 0, false));

    pHeap->_sysSetAsCache(pData, time, pOwner, true);
}
