#include "EngineX/GC/GCFile.h"

#include "include/GC/libc/string.h"

#include "EngineX/EXFile.h"

struct DVDFileInfo
{
    /* 0x00 */ u8 cb[0x30];
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void* callback;
};

extern "C" int DVDOpen(char* pFilename, DVDFileInfo* pFileInfo);
extern "C" int DVDClose(DVDFileInfo* pFileInfo);
extern "C" int DVDReadAsyncPrio(DVDFileInfo* pFileInfo, void* pDest, s32 Length, s32 Offset, void* pCallback,
                                s32 Prio);
extern "C" s32 DVDGetCommandBlockStatus(void* pBlock);
extern "C" s32 DVDGetDriveStatus(void);
extern "C" u32 OSGetTick(void);
void GC2_ARAM_DMA_To_ARAM(u8* pSrc, unsigned long AramDest, unsigned long Size);
Bool GC2_ARAM_DMA_Has_Completed();

#define OS_BUS_CLOCK (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))

#define DVD_STATE_END 0
#define DVD_STATE_WAITING 2
#define DVD_STATE_NO_DISK 4
#define DVD_STATE_COVER_OPEN 5
#define DVD_STATE_WRONG_DISK 6
#define DVD_STATE_RETRY 11
#define DVD_STATE_PAUSING 8

struct GCDVDFile
{ // 0x40
    /* 0x00 */ u8 m_InUse;
    /* 0x04 */ DVDFileInfo m_Info;
};

static DVDFileInfo gc_fileInfo;
static GCDVDFile gc_files[64];
static s32 gc_DVDOffset = 0;
static s32 gc_DVDFileLen = 0;

GCFileManager gFileManager;

int _PCopen(char* pFilename, int flags, int mode)
{
    int ret;

    ret = DVDOpen(pFilename, &gc_fileInfo);
    if (ret != 0)
    {
        gc_DVDOffset = 0;
        gc_DVDFileLen = gc_fileInfo.length;
    }
    return ret != 0 ? ret : -1;
}

u32 MXFile::GetLength() const
{
    if (_PCopen(m_SysFile[0].pSysFilename, 0, 0) < 0)
    {
        return 0;
    }
    return gc_DVDFileLen;
}

GCFileManager::GCFileManager()
{
    memset(gc_files, 0, sizeof(gc_files));
    m_CurrentGCFile = 0;
}

void GCFileManager::Init2()
{
}

u32 GCFileManager::GetFileSortKey(AsyncFileData* pFile)
{
    return 0;
}

s32 GCFileManager::FileOpen(AsyncFileData* pFile)
{
    int i;

    pFile->AsyncFileOpen = 0;
    pFile->AsyncFileHandle = 0;

    for (i = 1; i <= 63 && gc_files[i].m_InUse; i++)
    {
    }

    if (i <= 63)
    {
        if (DVDOpen(pFile->XFile.FileName[0], &gc_files[i].m_Info))
        {
            pFile->AsyncFileHandle = i;
            pFile->AsyncFileOpen = 1;
            gc_files[i].m_InUse = 1;
            return 1;
        }
    }
    return 0;
}

void GCFileManager::FileClose(AsyncFileData* pFile)
{
    if (pFile->AsyncFileOpen != 0 && pFile->AsyncFileHandle != 0)
    {
        DVDClose(&gc_files[pFile->AsyncFileHandle].m_Info);
        gc_files[pFile->AsyncFileHandle].m_InUse = 0;
    }
    pFile->AsyncFileOpen = 0;
}

void GCFileManager::FileRead(AsyncFileData* pFile, u8* pDest, unsigned long Size)
{
    m_CurrentGCFile = pFile->AsyncFileHandle;

    if (pDest != NULL && (s32)Size > 0)
    {
        if (((u32)pDest & 0x1f) != 0 || (pFile->AsyncFileByteOffset & 0x3) != 0 || pFile->AsyncFileByteOffset < 0 ||
            (Size & 0x1f) != 0)
        {
            memset(pDest, 0, Size);
        }
        else
        {
            DVDReadAsyncPrio(&gc_files[m_CurrentGCFile].m_Info, pDest, Size, pFile->AsyncFileByteOffset, NULL, 2);
        }
    }
}

HFL_STATUS GCFileManager::HasFileLoaded()
{
    if (m_CurrentGCFile == 0)
    {
        return HFL_LOADED;
    }

    if (DVDGetCommandBlockStatus(&gc_files[m_CurrentGCFile].m_Info.cb) == DVD_STATE_WAITING)
    {
        return HFL_NOT_LOADED;
    }

    switch (DVDGetDriveStatus())
    {
    case DVD_STATE_NO_DISK:
    case DVD_STATE_COVER_OPEN:
    case DVD_STATE_WRONG_DISK:
    case DVD_STATE_RETRY:
        return HFL_ERROR;
    case DVD_STATE_END:
        return HFL_LOADED;
    case DVD_STATE_PAUSING:
    default:
        return HFL_NOT_LOADED;
    }
}

void GCFileManager::StopReadAccess()
{
}

u32 GCFileManager::FileLength(AsyncFileData* pFile)
{
    if (pFile->AsyncFileHandle == 0)
    {
        return 0;
    }
    DVDFileInfo* pInfo = &gc_files[m_CurrentGCFile].m_Info;
    return pInfo->length;
}

u32 GCFileManager::DEBUG_GetMillisecondTimer()
{
    return OSTicksToMilliseconds(OSGetTick());
}

void GCFileManager::DEBUG_Print(char* pFormat, ...)
{
}

s32 EXAudioFile::OnLoad(AsyncFileData* pFile, int iDma)
{
    return 1;
}

s32 EXAudioFile::CheckDMA(int iDma)
{
    return 1;
}

s32 EXGameFile::OnLoad(AsyncFileData* pFile, int iDma)
{
    return 1;
}

s32 EXGameFile::CheckDMA(int iDma)
{
    return 1;
}

s32 EXSoundBankFile::OnLoad(AsyncFileData* pFile, int iDma)
{
    GC2_ARAM_DMA_To_ARAM(m_pFileManager->m_DMABuffer[iDma], (u32)pFile->AsyncFileRealDestBuffer,
                         m_pFileManager->m_DMASize);
    while (!GC2_ARAM_DMA_Has_Completed())
    {
    }
    return 1;
}

s32 EXSoundBankFile::CheckDMA(int iDma)
{
    return 1;
}

s32 EXGameFile::FileType()
{
    return 2;
}

s32 EXAudioFile::FileType()
{
    return 1;
}

s32 EXSoundBankFile::FileType()
{
    return 0;
}