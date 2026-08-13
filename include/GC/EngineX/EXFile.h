#ifndef EXFILE_H
#define EXFILE_H

#include "types.h"

#include "EXHashcode.h"
#include "include/GC/EngineX/EXRuntimeClass.h"
#include "include/GC/EngineX/EXList.h"
#include "EXMalloc.h"

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

    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

public:
    // MXFile& operator=();
    // MXFile();
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

struct EXFILEINFO;

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
    // /* 0x1c */ __vtbl_ptr_type* vf2506;

    // EXFile& operator=();
    EXFile();

    inline void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

    inline void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    static EXFile* CreateObject(/* parameters unknown */);

protected:
    void CreateMXFile(EXFILEINFO* pFinf, u64 Length, u64 SeekPos);
    void CreateMXFile(char* pFilename, u64 Length, u64 SeekPos);
    void DeleteMXFile();

public:
    EXFile(EXFILEINFO* pFinf, u64 Length, u64 SeekPos);
    ~EXFile();
    EXFile(char* pFilename, u64 Length, u64 SeekPos);
    // /* vtable[2] */ virtual EXFile(EXFile*, int, void);
    void Initalise();
    Bool OnLoad(EXMemHeap* pHeap);
    Bool IsLoaded();
    char* Filename();
    void* MemData();
    u32 Status();
    // void SetStatus(EXFile*, int, void);
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
    Bool GetFileLoadedStatus() const;
};

struct EXFILE
{ // 0xc
    /* 0x0 */ char* pFilename;
    /* 0x4 */ u32 Length;
    /* 0x8 */ u32 SeekPos;
};

struct EXFILELOC_BIN
{ // 0x8
    /* 0x0 */ u32 FileLoc;
    /* 0x4 */ u32 FileListNum;
};

struct EXFILEINFO_BIN
{ // 0x1c
    /* 0x00 */ u32 Length;
    /* 0x04 */ EXHashCode HashCode;
    /* 0x08 */ u32 Version;
    /* 0x0c */ u32 Flags;
    /* 0x10 */ u32 NumFileLoc;
    /* 0x14 */ EXFILELOC_BIN FileLocInfo[1];
};

struct EXFILELIST_BIN
{ // 0x30
    /* 0x00 */ u32 Version;
    /* 0x04 */ u32 FileSize;
    /* 0x08 */ s32 NumFiles;
    /* 0x0c */ u16 BuildType;
    /* 0x0e */ u16 NumFileLists;
    // /* 0x10 */ EXRelPtr<ex::EXRELOFFSET32> FileNameListOffset;
    /* 0x14 */ EXFILEINFO_BIN FileInfo;
};

struct EXFILEINFO
{ // 0x3c
    /* 0x00 */ char* pFileName;
    /* 0x04 */ u32 Length;
    /* 0x08 */ EXFILELOC_BIN FileLocInfo[4];
    /* 0x28 */ EXFile* pFile;
    /* 0x2c */ EXFILE* pFileList;
    /* 0x30 */ EXHashCode HashCode;
    /* 0x34 */ u32 Flags;
    /* 0x38 */ u32 Version;

    // EXFILEINFO& operator=();
    EXFILEINFO();
    ~EXFILEINFO();
    void Set();
};

#endif // EXFILE_H
