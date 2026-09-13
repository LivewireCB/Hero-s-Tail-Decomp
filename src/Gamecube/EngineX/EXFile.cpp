#include "EngineX/EXFile.h"

#include "EngineX/EXFileSys.h"
#include "EngineX/EXMalloc.h"
#include "EngineX/EXSoundManager.h"

char* EXFileNotInit = "EXFile Not initialised";
EXFileSys* EXFileSys::m_pFileSys = 0;
Bool EXFileSys::m_DebugLoadInfo = true;

extern EXMemHeap* _SystemHeapList[4];

EXFile* EXFile::CreateObject()
{
    return new EXFile();
}

MXFile::MXFile(u64 Length, u64 SeekPos)
{
    Initialise(Length, SeekPos);
}

// EXAMPLE:
// This function exhibits a good example of how register and scheduling shit doesnt make sense
// The asm says that the order should be 0x30, 0x3C, 0x34, 0x38
// Having them in the order below somehow generates the order I listed above
void MXFile::Initialise(u64 Length, u64 SeekPos)
{
    for (u32 l = 0; l != 4; l++)
    {
        m_SysFile[l].pSysFilename = NULL;
        m_SysFile[l].SysFileLoc = NULL;
    }

    m_Length = Length; // 0x30
    m_SeekPos = SeekPos; // 0x34
    m_FileHandle = NULL; // 0x38
    m_pLoadAddr = NULL; // 0x3c
}

void MXFile::SetFileHandle(u64 FileHandle)
{
    u32 ID = EXFileSys::m_pFileSys->m_UniqueID;

    EXFileSys::m_pFileSys->m_UniqueID = (ID + 1) & 0xffffff;
    FileHandle |= ID << 8;
    m_FileHandle = FileHandle;
}

EXFile::EXFile()
{
    Initalise();
}

EXFile::EXFile(EXFILEINFO* pFinf, u64 Length, u64 SeekPos)
{
    Initalise();
    CreateMXFile(pFinf, Length, SeekPos);
}

EXFile::EXFile(char* pFilename, u64 Length, u64 SeekPos)
{
    Initalise();
    CreateMXFile(pFilename, Length, SeekPos);
}

EXFile::~EXFile()
{
    EXFileSys::m_pFileSys->RemoveFile(this);
    CleanUpMemory();
    DeleteMXFile();
}

void EXFile::Initalise()
{
    m_pFilename = EXFileNotInit;
    m_pNext = 0;
    m_pPrev = 0;
    m_pMXFile = 0;
    m_pMemAddr = 0;
    m_Priority = 0;
    m_Status = 0;
}

void EXFile::ChangeMemOwner()
{
    if (m_pMXFile != NULL)
    {
        EXAllocSetOwner(m_pMXFile->m_pLoadAddr, &m_pMemAddr);
    }

    EXFile::DeleteMXFile();
}

void EXFile::CreateMXFile(EXFILEINFO* pFinf, u64 Length, u64 SeekPos)
{
    if (m_pMXFile != NULL)
    {
        EXFree(m_pMXFile);
        m_pMXFile = NULL;
    }

    m_pMXFile = new MXFile(Length, SeekPos);

    if (m_pMXFile == NULL)
    {
        do
        {
        } while (true);
    }

    EXFileSys::m_pFileSys->GetSysFileInfo(m_pMXFile, pFinf->pFileName);

    m_pFilename = pFinf->pFileName;
}

void EXFile::CreateMXFile(char* pFilename, u64 Length, u64 SeekPos)
{
    if (m_pMXFile != NULL)
    {
        EXFree(m_pMXFile);
        m_pMXFile = NULL;
    }

    m_pMXFile = new MXFile(Length, SeekPos);

    if (m_pMXFile == NULL)
    {
        do
        {
        } while (true);
    }

    EXFileSys::m_pFileSys->GetSysFileInfo(m_pMXFile, pFilename);

    m_pFilename = pFilename;
}

void EXFile::DeleteMXFile()
{
    if (m_pMXFile != NULL)
    {
        EXFree(m_pMXFile);
        m_pMXFile = NULL;
    }
}

void EXFile::CleanUpMemory()
{
    if ((m_pMXFile != NULL) && (m_pMXFile->m_pLoadAddr != NULL))
    {
        EXFree(m_pMXFile->m_pLoadAddr);
        m_pMXFile->m_pLoadAddr = NULL;
    }

    if (m_pMemAddr != NULL)
    {
        EXFree(m_pMemAddr);
        m_pMemAddr = NULL;
    }
}

Bool EXFile::OnLoad(EXMemHeap* pHeap)
{
    if (m_pMXFile == NULL)
    {
        do
        {
        } while (true);
    }

    if ((m_pMemAddr != NULL) || ((m_pMXFile != NULL) && (m_pMXFile->m_pLoadAddr != NULL)))
    {
        EXFile::OnKill();
    }

    u32 nLength = m_pMXFile->m_Length;
    if (nLength == 0)
    {
        EXFILEINFO* pFInf = EXFileSys::m_pFileSys->GetFileInfo(m_pFilename);
        if (pFInf != NULL)
        {
            nLength = pFInf->Length;
        }

        if (nLength == 0)
        {
            nLength = m_pMXFile->GetLength();
            if (nLength == 0)
            {
                m_Status = 6;
                return false;
            }
        }
    }

    m_pMXFile->m_Length = (nLength + 0x1f) & ~0x1f;
    m_pMXFile->m_pLoadAddr = pHeap->_EXAlloc(m_pMXFile->m_Length, 9);

    if (m_pMXFile->m_pLoadAddr == NULL)
    {
        return false;
    }

    return EXFileSys::AsyncReadFile(m_pMXFile, m_Priority);
}

Bool EXFile::OnLoad()
{
    return OnLoad(_SystemHeapList[0]);
}

Bool EXFile::OnLoaded()
{
    EXFile::ChangeMemOwner();
    m_Status = 3;

    return true;
}

Bool EXFile::OnKill()
{
    EXFile::CleanUpMemory();

    return true;
}

Bool EXFile::GetFileLoadedStatus() const
{
    if (m_pMXFile != NULL)
    {
        u32 FileHandle = m_pMXFile->m_FileHandle;
        u32 FileStatus = EXBaseSoundManager::m_pSoundManager->GetFileStatus(FileHandle & 0xff);

        if (((FileStatus >> 8) == (FileHandle >> 8)) && ((FileStatus & 0xff) == 0x83))
        {
            return true;
        }
    }

    return false;
}

EXRuntimeClass* EXFile::GetRuntimeClass() const
{
    return &classEXFile;
}
