#include "EngineX/EXFileSys.h"

#include "EngineX/EXGeoFile.h"
#include "EngineX/EXSoundManager.h"
#include "EngineX/GC/GCWnd.h"
#include "libc/string.h"

// TODO: decompile lib functions and get headers for each function below
// forward decs cus the compiler is freaking the fuck out
extern "C" int strcasecmp(const char*, const char*); // what tu is this from (nvm i found it)
extern "C" void qsort(void*, size_t, size_t, int (*)(const void*, const void*));
extern "C" int sprintf(char*, const char*, ...);

EXFileSys::EXFileSys()
{
    EXDList* pQueued = &m_FileQueuedList;
    EXDList* pLoaded = &m_FileLoadedList;

    m_FileLists.Init(0, -1);
    pQueued->m_pHead = NULL;
    pQueued->m_pTail = NULL;
    pLoaded->m_pHead = NULL;
    pLoaded->m_pTail = NULL;
    m_NumActiveFiles = 0;
    m_Status = 0;
    m_ScanPos = 0;
    m_UniqueID = 0;

    for (u32 i = 0; i < 16; i++)
    {
        m_ActiveFiles[i] = NULL;
    }
}

EXFileSys::~EXFileSys()
{
    EXFile* pFile = (EXFile*)m_FileQueuedList.m_pHead;
    while (pFile != NULL)
    {
        pFile->OnKill();
        pFile = (EXFile*)pFile->m_pNext;
    }

    pFile = (EXFile*)m_FileLoadedList.m_pHead;
    while (pFile != NULL)
    {
        pFile->OnKill();
        pFile = (EXFile*)pFile->m_pNext;
    }

    for (int i = 0; i < m_FileLists.m_iSize; i++)
    {
        if (m_FileLists.m_pData[i] != NULL)
        {
            delete (EXFileList*)m_FileLists.m_pData[i];
        }
    }

    EXFree(m_FileLists.m_pData);
}

void EXFileSys::RegisterWatcherVars() const
{
}

Bool EXFileSys::Init(EXFileSys* pFileSys)
{
    m_pFileSys = pFileSys;
    return true;
}

void EXFileSys::Shutdown()
{
    if (m_pFileSys != 0)
    {
        delete m_pFileSys;
        m_pFileSys = 0;
    }
}

void EXFileSys::AddFileList(EXFILE& FileList)
{
    m_FileLists.EXDataArray<void*, void*>::Add(new EXFileList(FileList), 1);
    EXBaseSoundManager::m_pSoundManager->BuildSoundFileList();
}

void EXFileSys::UpdateFileLists() const
{
}

EXFILEINFO* EXFileSys::GetFileInfo(EXHashCode HashCode) const
{
    for (int i = 0; i < m_FileLists.m_iSize; i++)
    {
        EXFILEINFO* FInf = ((EXFileList*)m_FileLists.m_pData[i])->FindFile(HashCode);
        if ((FInf != NULL) && ((s32)FInf->Flags < 0))
        {
            return FInf;
        }
    }

    return NULL;
}

EXFILEINFO* EXFileSys::GetFileInfo(char* pFileName) const
{
    for (int i = 0; i < m_FileLists.m_iSize; i++)
    {
        EXFILEINFO* FInf = ((EXFileList*)m_FileLists.m_pData[i])->FindFile(pFileName);
        if ((FInf != NULL) && ((s32)FInf->Flags < 0))
        {
            return FInf;
        }
    }

    return NULL;
}

EXFILEINFO* EXFileSys::GetFileInfo(EXFile* pFile) const
{
    for (int i = 0; i < m_FileLists.m_iSize; i++)
    {
        EXFILEINFO* FInf = ((EXFileList*)m_FileLists.m_pData[i])->FindFile(pFile);
        if ((FInf != NULL) && ((s32)FInf->Flags < 0))
        {
            return FInf;
        }
    }

    return NULL;
}

Bool EXFileSys::GetSysFileInfo(MXFile* pMXFile, char* pFilename) const
{
    for (int i = 0; i < m_FileLists.m_iSize; i++)
    {
        EXFileList* pFileList = (EXFileList*)m_FileLists.m_pData[i];
        EXFILEINFO* FInf = pFileList->FindFile(pFilename);

        if (FInf != NULL)
        {
            EXSYSFILEINFO* pSysFile = pMXFile->m_SysFile;
            for (u32 l = 0; l < 4; l++, pSysFile++)
            {
                u32 n = FInf->FileLocInfo[l].FileListNum;
                char* pSysFilename = pFileList->m_BinaryNames.m_pData[n].m_pData;
                if (pSysFilename == NULL)
                {
                    pSysFilename = "";
                }

                pSysFile->pSysFilename = pSysFilename;
                pSysFile->SysFileLoc = FInf->FileLocInfo[l].FileLoc;
                pSysFile->IsBigFileFile = true;
            }

            return true;
        }
    }

    EXSYSFILEINFO* pSysFile = pMXFile->m_SysFile;
    for (u32 l = 0; l < 4; l++, pSysFile++)
    {
        pSysFile->pSysFilename = pFilename;
        pSysFile->SysFileLoc = 0;
        pSysFile->IsBigFileFile = false;
    }

    return true;
}

EXFile* EXFileSys::OnQueueFile(EXFile* pFile, u64 Priority, Bool fWait)
{
    if (pFile->m_Status == 0)
    {
        if (m_FileQueuedList.IsMember(pFile) == 0)
        {
            m_FileQueuedList.AddTail(pFile);
            pFile->m_Status = 1;
            pFile->m_Priority = ~Priority;

            if (fWait)
            {
                WaitSyncOnFile(pFile, true);
                WaitSync(true);
            }
        }
    }

    return pFile;
}

EXFile* EXFileSys::OnLoadFile(EXFile* pFile)
{
    if (pFile->m_Status == 2)
    {
        WaitSyncOnFile(pFile, true);
    }

    if (pFile->m_Status == 0)
    {
        if (m_FileLoadedList.IsMember(pFile))
        {
            return pFile;
        }

        if (OnQueueFile(pFile, 0x7fffffff, true) == NULL)
        {
            return NULL;
        }
    }

    return pFile;
}

void EXFileSys::RemoveFile(EXFile* pFile)
{
    if (this != NULL)
    {
        for (u32 i = 0; i < 16; i++)
        {
            if (m_ActiveFiles[i] == pFile)
            {
                u32 FileStatus = EXBaseSoundManager::m_pSoundManager->GetFileStatus(i) & 0xf;
                if ((((FileStatus - 1) <= 1)) || (pFile->m_Status == 2))
                {
                    EXBaseSoundManager::m_pSoundManager->AsyncStopFileRead(
                        pFile->m_pMXFile->m_FileHandle);
                    WaitForFileCompletion(pFile);
                    m_ActiveFiles[i]->m_Status = 0;
                }

                m_NumActiveFiles--;
                m_ActiveFiles[i] = NULL;
                break;
            }
        }

        pFile->m_Status = 0;
        pFile->OnKill();

        if (m_FileQueuedList.IsMember(pFile))
        {
            m_FileQueuedList.Remove(pFile);
        }

        if (m_FileLoadedList.IsMember(pFile))
        {
            m_FileLoadedList.Remove(pFile);
        }
    }
}

Bool EXFileSys::AsyncReadFile(MXFile* pFile, u64 Priority)
{
    XFileHandle hXFile;
    hXFile.FileLength = pFile->m_Length;

    for (u32 l = 0; l <= 3; l++)
    {
        hXFile.FileStart[l] = 0;
        hXFile.DiskStartSector[l] = pFile->m_SeekPos + pFile->m_SysFile[l].SysFileLoc;
        GetFileListFileName(hXFile.FileName[0], pFile->m_SysFile[0].pSysFilename);
    }

    hXFile.IsBigFileFile = pFile->m_SysFile[0].IsBigFileFile;
    EXBaseSoundManager::m_pSoundManager->AsyncReadFile(&hXFile, (char*)pFile->m_pLoadAddr, Priority,
                                                       pFile->m_FileHandle);

    return true;
}

void EXFileSys::GetFileListFileName(char* destFileName, char* FileListName)
{
    sprintf(destFileName, "/%s", FileListName);
}

void EXFileSys::Poll()
{
}

// TODO: fix out of order control flow
void EXFileSys::WaitForFileCompletion(EXFile* pFile) const
{
    while (true)
    {
        u32 FileStatus = pFile->m_Status;
        if (FileStatus == 2)
        {
            MXFile* pMXFile = pFile->m_pMXFile;
            u32 Status = EXBaseSoundManager::m_pSoundManager->GetFileStatus(
                             ((u8*)&pMXFile->m_FileHandle)[3]) &
                         0xf;
            if (Status == 3)
            {
                return;
            }
        }
        else if ((FileStatus < 2) || (FileStatus <= 5))
        {
            return;
        }

        EXBaseSoundManager::m_pSoundManager->CommandUpdate(1);
    }
}

// bro
void EXFileSys::WaitSyncOnFile(EXFile* pFile, Bool fAllowMemoryCompact)
{
    EXFileSys* pFileSys = m_pFileSys;

    while ((pFile->m_Status != 3) && (pFile->m_Status != 5))
    {
        pFileSys->Poll();
        EXBaseSoundManager::m_pSoundManager->CommandUpdate(1);

        if (pFileSys->m_Status == 2)
        {
            if (fAllowMemoryCompact)
            {
                EXMemHeap::UpdateAllHeaps(1, 0);
            }
        }
    }
}

void EXFileSys::WaitSync(Bool fAllowMemoryCompact)
{
    EXFileSys* pFileSys = m_pFileSys;

    do
    {
        pFileSys->Poll();
        EXBaseSoundManager::m_pSoundManager->CommandUpdate(1);

        if ((pFileSys->m_Status == 2) && fAllowMemoryCompact)
        {
            EXMemHeap::UpdateAllHeaps(1, 0);
        }
    } while (pFileSys->GetLoadingStatus());
}

void EXFileSys::UpdateLoadedFiles(Bool fCompactMode) const
{
    EXGeoFile::UpdateFiles(fCompactMode);
}

void EXFileSys::Update()
{
    Poll();
    UpdateLoadedFiles(0);
}

// what kind of fucking code gen is this
Bool EXFileSys::GetLoadingStatus() const
{
    s32 Count = m_NumActiveFiles + m_FileQueuedList.Count();

    if (m_Status != 0)
    {
        if (Count == -1)
        {
            return false;
        }
    }
    else if (Count == 0)
    {
        return false;
    }

    return false;
}

EXFileList::EXFileList(EXFILE& FileList) : m_FileList(FileList), m_BinaryNames(0, -1)
{
}

EXFileList::~EXFileList()
{
    if (m_FileNameBuf != NULL)
    {
        EXFree(m_FileNameBuf);
    }

    EXFree(m_FileInfo.m_pData);
}

EXFILEINFO* EXFileList::FindFile(EXHashCode HashCode) const
{
}

EXFILEINFO* EXFileList::FindFile(char* pInFileName) const
{
}

EXFILEINFO* EXFileList::FindFile(EXFile* pFile) const
{
    EXDataArray<EXFILEINFO, const EXFILEINFO&>* pFileInfo =
        (EXDataArray<EXFILEINFO, const EXFILEINFO&>*)&m_FileInfo;
    EXFILEINFO* pFInf = pFileInfo->m_pData;

    for (int i = 0; i < pFileInfo->m_iSize; i++, pFInf++)
    {
        if (pFInf->pFile == pFile)
        {
            return pFInf;
        }
    }

    return NULL;
}

int EXFileInfoArray::QSortFn_SortByName(void* arg1, void* arg2)
{
    return strcmp(((EXFILEINFO*)arg1)->pFileName, ((EXFILEINFO*)arg2)->pFileName);
}

void EXFileInfoArray::SortByName()
{
    qsort(m_pData, m_iSize, sizeof(EXFILEINFO),
          (int (*)(const void*, const void*))QSortFn_SortByName);
}

int EXFileInfoArray::QSortFn_SortByHash(void* arg1, void* arg2)
{
    EXHashCode HashCode1 = ((EXFILEINFO*)arg1)->HashCode;
    EXHashCode HashCode2 = ((EXFILEINFO*)arg2)->HashCode;

    if (HashCode1 < HashCode2)
    {
        return -1;
    }

    return HashCode1 > HashCode2;
}

void EXFileInfoArray::SortByHash()
{
    qsort(m_pData, m_iSize, sizeof(EXFILEINFO),
          (int (*)(const void*, const void*))QSortFn_SortByHash);
}
