#ifndef EXFILEMANAGER_H
#define EXFILEMANAGER_H

#include "types.h"

enum ASYNCFILESTATUS
{
    ASF_AWAIT_REQUEST = 0,
    ASF_START_READ = 1,
    ASF_READING = 2,
    ASF_FREE = 3,
    ASF_HASREAD = 128
};

enum DMABUFSTATUS
{
    DBS_FREE = 0,
    DBS_LOADING = 1,
    DBS_DMAING = 2
};

enum FM_DMASTATES
{
    FM_FLAT = 0,
    FM_DMA = 1
};

enum HFL_STATUS
{
    HFL_NOT_LOADED = 0,
    HFL_LOADED = 1,
    HFL_ERROR = 2
};

struct XFileHandle
{ // 0x1a0
    /* 0x000 */ u32 DiskStartSector[4];
    /* 0x010 */ u32 FileStart[4];
    /* 0x020 */ u32 FileLength;
    /* 0x024 */ char FileName[4][94];
    /* 0x19c */ u16 IsBigFileFile;
};

struct AsyncFileData_tag
{ // 0x1d8
    /* 0x000 */ ASYNCFILESTATUS AsyncFileStatus;
    /* 0x004 */ s32 AsyncFileOpen;
    /* 0x008 */ XFileHandle XFile;
    /* 0x1a8 */ int AsyncFileHandle;
    /* 0x1ac */ s32 AsyncFileByteOffset;
    /* 0x1b0 */ u32 AsyncFileByteSize;
    /* 0x1b4 */ u32 AsyncFileByteSizeAligned;
    /* 0x1b8 */ u8* AsyncFileDestBuffer;
    /* 0x1bc */ u8* AsyncFileRealDestBuffer;
    /* 0x1c0 */ u32 AsyncFilePriority;
    /* 0x1c4 */ s32 CloseMe;
    /* 0x1c8 */ int HasRead;
    /* 0x1cc */ int StopFile;
    /* 0x1d0 */ u32 UniqueID;
    /* 0x1d4 */ int BigFileIndex;
};

typedef AsyncFileData_tag AsyncFileData;

struct EXFileManager;

struct AsyncFile
{ // 0x14
protected:
    /* 0x00 */ AsyncFileData* Files;
    /* 0x04 */ u32 m_ScanPos;
    /* 0x08 */ u32 m_MaxFiles;
    /* 0x0c */ EXFileManager* m_pFileManager;

public:
    /* 0x10 */ // __vtbl_ptr_type* $vf3317;

    AsyncFile();
    virtual s32 OnLoad(AsyncFileData* pFile, int iDma);
    virtual s32 CheckDMA(int iDma);
    virtual s32 FileType();
    virtual ~AsyncFile();
};

struct EXGameFile : AsyncFile
{ // 0x14
    EXGameFile();
    virtual ~EXGameFile();

protected:
    virtual s32 FileType();
    virtual s32 OnLoad(AsyncFileData* pFile, int iDma);
    virtual s32 CheckDMA(int iDma);
};

struct EXAudioFile : AsyncFile
{ // 0x14
    EXAudioFile();
    virtual ~EXAudioFile();

protected:
    virtual s32 FileType();
    virtual s32 OnLoad(AsyncFileData* pFile, int iDma);
    virtual s32 CheckDMA(int iDma);
};

struct EXSoundBankFile : AsyncFile
{ // 0x14
    EXSoundBankFile();
    virtual ~EXSoundBankFile();

protected:
    virtual s32 FileType();
    virtual s32 OnLoad(AsyncFileData* pFile, int iDma);
    virtual s32 CheckDMA(int iDma);
};

struct EXFileManager
{ // 0x4a0
    /* 0x000 */ s32 m_ProcessingDMAJobs;
    /* 0x004 */ u8* m_DMABuffer[2];
    /* 0x00c */ DMABUFSTATUS m_DMABufferStatus[2];
    /* 0x014 */ AsyncFileData* m_DMABufferFile[2];
    /* 0x01c */ s32 m_DmaBuffer;
    /* 0x020 */ u32 m_FileChunkSize;
    /* 0x024 */ u32 m_CDSectorSize;
    /* 0x028 */ Bool m_IsCallbackMode;
    /* 0x02c */ EXSoundBankFile* SoundBankFiles;
    /* 0x030 */ EXAudioFile* AudioFiles;
    /* 0x034 */ EXGameFile* GameFiles;
    /* 0x038 */ u32 m_GameFileCount;
    /* 0x03c */ s32 m_FilePriorityLockFlag;
    /* 0x040 */ u32 m_FilePriorityLock;
    /* 0x044 */ s32 m_FileSystemPaused;
    /* 0x048 */ s32 m_ReadingFileChunk;
    /* 0x04c */ s32 m_ReadingFlag;
    /* 0x050 */ u32 m_ChunkSize;
    /* 0x054 */ u32 m_DMASize;
    /* 0x058 */ AsyncFileData* m_CurrentFile[2];
    /* 0x060 */ AsyncFile* m_CurrentFileClass[2];
    /* 0x068 */ u32 m_newtime;
    /* 0x06c */ u32 m_oldtime;
    /* 0x070 */ u32 m_ReadTimer;
    /* 0x074 */ unsigned int m_TotalReadTime[3];
    /* 0x080 */ unsigned int loadpercent[3];
    /* 0x08c */ u32 MaxSeekDelta;
    /* 0x090 */ u32 m_CurMaxSeekDelta;
    /* 0x094 */ u32 m_CurSeekPos;
    /* 0x098 */ unsigned int m_FileListOrder[256];
    /* 0x498 */ u32 m_SmartSeekFlag;
    /* 0x49c */ // __vtbl_ptr_type* $vf3320;

    EXFileManager();
    virtual ~EXFileManager();
    void Init(FM_DMASTATES SoundBankDMA, FM_DMASTATES AudioDMA, u32 FileChunkSize, u32 CDSectorSize,
              Bool IsCallbackMode);
    s32 Update_();
    virtual s32 Update();
    virtual void StopReadAccess();

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
};

#endif // EXFILEMANAGER_H
