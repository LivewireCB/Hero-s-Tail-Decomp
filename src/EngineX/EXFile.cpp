#include "include/EngineX/EXFile.h"

#include "include/EngineX/EXMalloc.h"

EXRuntimeClass EXFile::classEXFile;
char* EXFileNotInit;

EXFile* EXFile::CreateObject()
{
    // return new EXFile();
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
    // Requires usage of "EXFileSys::m_pFileSys". This lives in EXFileSys.cpp
}

EXFile::EXFile()
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

EXRuntimeClass* EXFile::GetRuntimeClass() const
{
    return &classEXFile;
}
