#ifndef EXFILESYS_H
#define EXFILESYS_H

#include "types.h"

#include "EXFile.h"
#include "EXFixedArray.h"
#include "ExPtrArray.h"
#include "EXString.h"
#include "EXDataArray.h"

struct EXDataArray<EXFILEINFO, const EXFILEINFO&>
{
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ EXFILEINFO* m_pData;

    EXDataArray();
    ~EXDataArray();
    EXDataArray(EXDataArray<EXFILEINFO, const EXFILEINFO&>*, int, void);
    void Init();
    int Size();
    int AllocSize();
    int GetUpperBound();
    void SetSize();
    void SetGrowBy(EXDataArray<EXFILEINFO, const EXFILEINFO&>*, int, void);
    void AllocMem(EXDataArray<EXFILEINFO, const EXFILEINFO&>*, int, void);
    void FreeExtra();
    void Empty();
    void RemoveAll();
    void SetAt();
    EXFILEINFO GetAt();
    EXFILEINFO& ElementAt();
    EXFILEINFO* GetData();
    // EXFILEINFO* GetData();
    void SetAtGrow();
    int Add();
    int Append();
    void Copy();
    EXFILEINFO& AddSpace();
    s32 AddUnique();
    s32 Find();
    // EXFILEINFO& operator[]();
    // EXFILEINFO& operator[]();
    void InsertAt();
    void RemoveAt();
    // void InsertAt();
    // EXDataArray<EXFILEINFO, const EXFILEINFO&>& operator=();

    void GrowArray();
};

struct EXFileInfoArray : EXDataArray<EXFILEINFO, const EXFILEINFO&>
{
    // EXFileInfoArray& operator=();
    EXFileInfoArray();
    ~EXFileInfoArray();
    // EXFileInfoArray(EXFileInfoArray*, int, void);

    static int QSortFn_SortByName(void* arg1, void* arg2);
    static int QSortFn_SortByHash(void* arg1, void* arg2);

    void SortByName();
    void SortByHash();
};

struct EXFileList
{
    /* 0x00 */ EXFILE m_FileList;
    /* 0x0c */ EXStringArray m_BinaryNames;
    /* 0x1c */ EXFileInfoArray m_FileInfo;
    /* 0x2c */ char* m_FileNameBuf;
    /* 0x30 */ u32 m_BinaryFileLength;
    /* 0x34 */ u32 m_NumFileLists;

    // EXFileList& operator=();
    EXFileList(EXFILE& FileList);
    ~EXFileList();
    EXFileList(EXFileList*, int, void);
    void UpdateList();
    EXFILEINFO* FindFile(EXHashCode HashCode) const;
    EXFILEINFO* FindFile(char* pInFileName) const;
    EXFILEINFO* FindFile(EXFile* pFile) const;
    EXFILE& FileList();
    // EXString& BinaryName();
    // EXFileInfoArray& FileInfo();
    // EXFileInfoArray& FileInfo();
    char*& FileNameBuf();
    u32 BinaryFileLength();
    u32 NumFileLists();
};

struct EXPtrArray<EXFileList> : EXDataArray<void*, void*>
{ // 0x10

    // stabs says 0x10, but theres nothing here.

    // EXPtrArray<EXFileList>& operator=();
    EXPtrArray();
    // EXPtrArray();
    EXPtrArray(EXPtrArray<EXFileList>*, int, void);
    EXFileList* GetAt();
    void SetAt();
    EXFileList*& ElementAt();
    EXFileList** GetData();
    // EXFileList** GetData();
    void SetAtGrow();
    int Add();
    void InsertAt();
    // void InsertAt();
    int Append();
    void Copy();
    u32 AddUnique();
    s32 Find();
    // EXFileList* operator EXFileList*();
};

struct EXFileSys
{
    static EXFileSys* m_pFileSys;
    static Bool m_CdRomBuild;
    static Bool m_DebugLoadInfo;
    /* 0x00 */ EXPtrArray<EXFileList> m_FileLists;
    /* 0x10 */ EXDList m_FileQueuedList;
    /* 0x18 */ EXDList m_FileLoadedList;
    /* 0x20 */ u32 m_Status;
    /* 0x24 */ EXFile* m_ActiveFiles[16];
    /* 0x64 */ u32 m_NumActiveFiles;
    /* 0x68 */ u32 m_UniqueID;
    /* 0x6c */ u32 m_ScanPos;

    // EXFileSys& operator=();
    EXFileSys();
    ~EXFileSys();
    EXFileSys(EXFileSys*, int, void);
    static EXFileSys* GetFileSys(/* parameters unknown */);
    static Bool Init(EXFileSys* pFileSys);
    static void Shutdown(/* parameters unknown */);
    void RegisterWatcherVars() const;
    void UpdateLoadedFiles(Bool fCompactMode) const;
    void Update();
    static void WaitSync(Bool fAllowMemoryCompact);
    Bool GetLoadingStatus() const;
    void AddFileList(EXFILE& FileList);
    void UpdateFileLists() const;
    Bool GetSysFileInfo(MXFile* pMXFile, char* pFilename) const;
    EXFILEINFO* GetFileInfo(EXHashCode HashCode) const;
    EXFILEINFO* GetFileInfo(char* pFileName) const;
    EXFILEINFO* GetFileInfo(EXFile* pFile) const;
    EXFileList* FileList();
    u32 FileListCount();
    u32 FileListQueueCount();
    Bool IsFileActive();
    u32 Status();
    EXDList& FileQueuedList();
    EXDList& FileLoadedList();
    void AddHeadQueueFile();
    EXFile* OnLoadFile(EXFile* pFile);
    EXFile* OnQueueFile(EXFile* pFile, u64 Priority, Bool fWait);
    void RemoveFile(EXFile* pFile);
    static Bool CdRomBuild(/* parameters unknown */);
    static Bool AsyncReadFile(MXFile* pFile, u64 Priority);
    static void GetFileListFileName(char* destFileName, char* FileListName);
    u32 GetUniqueID();
    static Bool& DebugLoadInfo(/* parameters unknown */);

    static void WaitSyncOnFile(EXFile* pFile, Bool fAllowMemoryCompact);
    void Poll();
    void WaitForFileCompletion(EXFile* pFile) const;
};

struct EXFixedArray<unsigned char, 4>
{
    unsigned char m_Data[4];

    // EXFixedArray<unsigned char,4>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    u8& ElementAt();
    u8 GetAt();
    void SetAt();
    u8* GetData();
    // u8* GetData();
    // u8* operator unsigned char *();
    // u8* operator unsigned char *();
};

struct EXFileLoadActivity
{
    /* 0x0 */ Bool m_bEnabled;
    /* 0x1 */ u8 m_Position;
    /* 0x2 */ u8 m_Alpha;
    /* 0x3 */ u8 m_Size;
    /* 0x4 */ EXFixedArray<unsigned char, 4> m_bFlags;

    // EXFileLoadActivity& operator=();
    EXFileLoadActivity();
    // EXFileLoadActivity();
    Bool* pEnabled();
    u8* pPosition();
    u8* pAlpha();
    u8* pSize();
    void SetActivityFlag();
    // void Update(EXWnd* pWnd);
};

#endif // EXFILESYS_H
