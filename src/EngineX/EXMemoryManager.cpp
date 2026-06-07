#include <EngineX/EXMemoryManager.h>

void* _EXAlloc(size_t size, EXMemFlags memflags)
{
}

void* _EXAllocPure(size_t size, EXMemFlags memflags)
{
}

void* _EXRealloc(void* pData, size_t size)
{
}

void EXFree(void* pData)
{
}

void EXAllocSetTime(void* pData, s16 nTime)
{
}

void EXAllocSetOwner(void* pData, void* pOwner)
{
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
