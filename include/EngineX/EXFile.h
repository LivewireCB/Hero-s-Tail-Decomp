#ifndef EXFILE_H
#define EXFILE_H

#include "types.h"

#include "include/EngineX/EXRuntimeClass.h"
#include "include/EngineX/EXList.h"

struct EXSYSFILEINFO
{
    char* pSysFilename;
    u32 SysFileLoc;
    Bool IsBigFileFile;
};

struct MXFile
{
    /* 0x00 */ EXSYSFILEINFO m_SysFile[4];
    /* 0x30 */ u32 m_Length;
    /* 0x34 */ u32 m_SeekPos;
    /* 0x38 */ u32 m_FileHandle;
    /* 0x3c */ void* m_pLoadAddr;

public:
    // MXFile& operator=();
    MXFile();
    MXFile(u64 Length, u64 SeekPos);
    void Initialise(u64, u64);
    u32 Length();
    void SetLength();
    u32 SeekPos();
    void SetSeekPos();
    void*& LoadAddr();
    // void* LoadAddr();
    EXSYSFILEINFO& SysFile();
    u32 FileHandle();
    void SetFileHandle(u64 FileHandle);

protected:
    u32 GetLength();
};

struct EXFile : EXDListItem
{
    static EXRuntimeClass classEXFile;

protected:
    /* 0x08 */ MXFile* m_pMXFile;
    /* 0x0c */ char* m_pFilename;
    /* 0x10 */ void* m_pMemAddr;
    /* 0x14 */ u32 m_Status;
    /* 0x18 */ u32 m_Priority;

public:
    /* 0x1c */ __vtbl_ptr_type* vf2506;

    // EXFile& operator=();
    EXFile();

    // void* operator new(std::size_t size)
    // {
    // return _EXAlloc(size, 0);
    // }

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    static EXFile* CreateObject(/* parameters unknown */);

protected:
    void CreateMXFile();
    // void CreateMXFile();
    void DeleteMXFile();

public:
    // EXFile(EXFILEINFO* pFinf, u32 Length, u32 SeekPos);
    ~EXFile();
    EXFile(char* pFilename, u64 Length, u64 SeekPos);
    // /* vtable[2] */ virtual EXFile(EXFile*, int, void);
    void Initalise();
    // Bool OnLoad();
    Bool IsLoaded();
    char* Filename();
    void* MemData();
    u32 Status();
    void SetStatus(EXFile*, int, void);
    void SetPriority();
    u32 Priority();
    MXFile* GetMXFile();
    s32 GetFilelength();
    void* MemDetach();
    /* vtable[3] */ virtual Bool OnLoad();
    /* vtable[4] */ virtual Bool OnLoaded();
    /* vtable[5] */ virtual Bool OnKill();

protected:
    void ChangeMemOwner();
    void CleanUpMemory();
    Bool GetFileLoadedStatus();
};

#endif // EXFILE_H
