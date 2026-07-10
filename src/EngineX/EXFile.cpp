#include "include/EngineX/EXFile.h"

#include "include/EngineX/EXFileSys.h"
#include "include/EngineX/EXMalloc.h"
#include "include/EngineX/EXFileSys.h"

char* EXFileNotInit = "0";
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
    u32 ID;

    EXFileSys::m_pFileSys->m_UniqueID = 0;
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
}

void EXFile::CreateMXFile(char* pFilename, u64 Length, u64 SeekPos)
{
}

void EXFile::DeleteMXFile()
{
    if (m_pMXFile != NULL)
    {
        EXFree(m_pMXFile);
    }

    m_pMXFile = NULL;
}

void EXFile::CleanUpMemory()
{
}

Bool EXFile::OnLoad(EXMemHeap* pHeap)
{
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
    u32 a;
}

EXRuntimeClass* EXFile::GetRuntimeClass() const
{
    return &classEXFile;
}
