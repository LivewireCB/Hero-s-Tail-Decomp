#include <EngineX/EXMemoryManager.h>

#include <EngineX/EXMalloc.h>
#include "include/EngineX/GC/GCMalloc.h"

extern EXMemHeap* _SystemHeap;
extern EXMemHeap* _SystemHeapList[4];

// TODO: this function needs -fforce-addr off
void* _EXAlloc(size_t size, EXMemFlags memflags)
{
    if (_SystemHeap == 0)
    {
        _initalize_heap_memory();
    }

    _SystemHeap->_sysAlloc(size, memflags);
}

void* _EXAllocPure(size_t size, EXMemFlags memflags)
{
    if (_SystemHeap == 0)
    {
        _initalize_heap_memory();
    }

    _SystemHeap->_sysAlloc(size, memflags);
}

void* _EXRealloc(void* pData, size_t size)
{
    if (_SystemHeap == 0)
    {
        _initalize_heap_memory();
    }

    if (pData != 0)
    {
    }

    return _SystemHeap->_sysRealloc(pData, size);

    // best attempt
    // if (pData != 0)
    // {
    //     EXMemHeap* pHeap = 0;
    //     for (int i = 0; i < 4; i++)
    //     {
    //         pHeap = _SystemHeapList[i];
    //         if (pHeap != 0)
    //         {
    //             if (pData >= pHeap->m_pStart && pData <= pHeap->m_pEnd)
    //             {
    //                 return pHeap->_sysRealloc(pData, size);
    //             }
    //         }
    //     }
    //     return pHeap->_sysRealloc(pData, size);
    // }
}

void EXFree(void* pData)
{
}

void EXAllocSetTime(void* pData, s16 nTime)
{
}

void EXAllocSetOwner(void* pData, void* pOwner)
{
    *((void**)((char*)pData - 0x10)) = pOwner;

    if (pOwner != 0)
    {
        *(void**)pOwner = pData;
    }
}

void EXAllocSetReloc(void* pData, Bool fReloc)
{
}

void EXAllocSetFunc(void* pData, EXMEMCALLBACK* pFunc)
{
}

void EXAllocSetCacheDel(void* pData, s16 time, void** pOwner)
{
}
