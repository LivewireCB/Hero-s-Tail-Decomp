#include "include/EngineX/EXFileSys.h"

#include "include/EngineX/EXGeoFile.h"

EXFileSys::EXFileSys()
{
}

EXFileSys::~EXFileSys()
{
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
}

void EXFileSys::UpdateFileLists() const
{
}

EXFILEINFO* EXFileSys::GetFileInfo(EXHashCode HashCode) const
{
}

EXFILEINFO* EXFileSys::GetFileInfo(char* pFileName) const
{
}

EXFILEINFO* EXFileSys::GetFileInfo(EXFile* pFile) const
{
}

Bool EXFileSys::GetSysFileInfo(MXFile* pMXFile, char* pFilename) const
{
}

EXFile* EXFileSys::OnQueueFile(EXFile* pFile, u64 Priority, Bool fWait)
{
}

EXFile* EXFileSys::OnLoadFile(EXFile* pFile)
{
}

void EXFileSys::RemoveFile(EXFile* pFile)
{
}

Bool EXFileSys::AsyncReadFile(MXFile* pFile, u64 Priority)
{
}

void EXFileSys::GetFileListFileName(char* destFileName, char* FileListName)
{
}

void EXFileSys::Poll()
{
}

void EXFileSys::WaitForFileCompletion(EXFile* pFile) const
{
}

void EXFileSys::WaitSyncOnFile(EXFile* pFile, Bool fAllowMemoryCompact)
{
}

void EXFileSys::WaitSync(Bool fAllowMemoryCompact)
{
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

Bool EXFileSys::GetLoadingStatus() const
{
}

EXFileList::EXFileList(EXFILE& FileList)
{
}

EXFileList::~EXFileList()
{
}

EXFILEINFO* EXFileList::FindFile(EXHashCode HashCode) const
{
}

EXFILEINFO* EXFileList::FindFile(char* pInFileName) const
{
}

EXFILEINFO* EXFileList::FindFile(EXFile* pFile) const
{
}

int EXFileInfoArray::QSortFn_SortByName(void* arg1, void* arg2)
{
}

void EXFileInfoArray::SortByName()
{
}

int EXFileInfoArray::QSortFn_SortByHash(void* arg1, void* arg2)
{
}

void EXFileInfoArray::SortByHash()
{
}

// void EXFileLoadActivity::Update(EXWnd* pWnd)
// {
// }
