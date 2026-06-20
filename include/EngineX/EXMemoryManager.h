#ifndef EXMEMORYMANAGER_H
#define EXMEMORYMANAGER_H

#include "types.h"

typedef u64 EXMemFlags;

enum EXMcmds
{
    MemCmd_Null = 0,
    MemCmd_PreMemUpdate = 1,
    MemCmd_PostMemUpdate = 2,
    MemCmd_DebugMemBlockDump = 3,
    MemCmd_DebugMemBlockColour = 4
};

typedef Bool EXMEMCALLBACK(void* pData, EXMcmds cmd);

void* _EXAlloc(size_t size, EXMemFlags memflags);
void* _EXAllocPure(size_t size, EXMemFlags memflags);
void* _EXAllocRel(size_t size, void** pOwner, EXMemFlags memflags);
void* _EXAllocFnc(size_t size, EXMEMCALLBACK* pFunc, EXMemFlags memflags);
void* _EXRealloc(void* pData, size_t size);
void* _EXCache(size_t size, s16 time, void** pOwner, EXMemFlags memflags);
void* _EXCacheDel(size_t size, s16 time, void** pOwner, EXMemFlags memflags);
void EXFree(void* pData);
void EXAllocSetTime(void* pData, s16 nTime);
void EXAllocSetOwner(void* pData, void* pOwner);
void EXAllocSetReloc(void* pData, Bool fReloc);
void EXAllocSetFunc(void* pData, EXMEMCALLBACK* pFunc);
void EXAllocSetCache(void* pData, s16 time, void** pOwner);
void EXAllocSetCacheDel(void* pData, s16 time, void** pOwner);

#endif // EXMEMORYMANAGER_H
