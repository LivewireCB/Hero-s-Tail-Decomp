#ifndef GCFILE_H
#define GCFILE_H

#include <types.h>

#include "EngineX/EXFileManager.h"

struct GCFileManager : EXFileManager
{ // 0x4a4
    /* 0x4a0 */ s32 m_CurrentGCFile;

    GCFileManager();
    virtual ~GCFileManager();

protected:
    virtual void Init2();
    virtual s32 FileOpen(AsyncFileData* pFile);
    virtual void FileRead(AsyncFileData* pFile, u8* pDest, unsigned long Size);
    virtual void FileClose(AsyncFileData* pFile);
    virtual u32 FileLength(AsyncFileData* pFile);
    virtual HFL_STATUS HasFileLoaded();
    virtual u32 GetFileSortKey(AsyncFileData* pFile);
    virtual u32 DEBUG_GetMillisecondTimer();

public:
    virtual void DEBUG_Print(char* pFormat, ...);
    virtual void StopReadAccess();
};

extern GCFileManager gFileManager;

#endif // GCFILE_H
