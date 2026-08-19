#ifndef EXMEMCARD_H
#define EXMEMCARD_H

#include "types.h"

#include "EXFixedArray.h"
#include "EXHashcode.h"
#include "EXRuntimeClass.h"
#include "EXMalloc.h"

struct EXBaseSaveInfo
{ // 0x24
    /* 0x00 */ u32 NumSaves;
    /* 0x04 */ EXFixedArray<unsigned int, 8> SaveSize;
};

struct EXSaveInfo : /* 0x000 */ EXBaseSaveInfo
{ // 0x124
    /* 0x024 */ EXFixedArray<char, 32> SaveName;
    /* 0x044 */ EXFixedArray<char, 34> SaveDescription;
    /* 0x066 */ Bool UseCustomBgColor;
    /* 0x068 */ EXFixedArray<int[4], 4> BgColor;
    /* 0x0a8 */ Bool UseCustomLighting;
    /* 0x0ac */ EXFixedArray<float[4], 3> LightDir;
    /* 0x0dc */ EXFixedArray<float[4], 3> LightColor;
    /* 0x10c */ _iconVu0FVECTOR Ambient;
    /* 0x11c */ void* pIconData;
    /* 0x120 */ u32 IconDataSize;
};

struct EXMemCardDlgData
{ // 0x38
    /* 0x00 */ u32 DlgType;
    /* 0x04 */ EXHashCode MessageHash;
    /* 0x08 */ EXFixedArray<unsigned int, 4> OptHash;
    /* 0x18 */ u16 OptCount;
    /* 0x1a */ u16 DefaultOpt;
    /* 0x1c */ u32 MemRequired;
    /* 0x20 */ char* pSlotName;
    /* 0x24 */ char* pMessage;
    /* 0x28 */ EXFixedArray<const char*, 4> pOpt;
};

struct EXMemCardDlg
{ // 0x8
    static EXRuntimeClass classEXMemCardDlg;

protected:
    s32 paduntilthebelowisimplemented; // created for createObject and constructorto have correct offsets
    // /* 0x0 */ EXMemCardDlgWnd* m_pWnd;

public:
    // /* 0x4 */ __vtbl_ptr_type* vf24075;

    // EXMemCardDlg& operator=();
    EXMemCardDlg();

    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXMemCardDlg* CreateObject(/* parameters unknown */);
    // EXMemCardDlg();
    /* vtable[2] */ virtual ~EXMemCardDlg();
    /* vtable[3] */ virtual void ShowDlg();
    /* vtable[4] */ virtual void HideDlg();
    /* vtable[5] */ virtual u32 DlgResult();
};

struct EXBaseMemCard
{ // 0x48
protected:
    /* 0x00 */ EXRuntimeClass* m_pDlgClass;
    /* 0x04 */ EXMemCardDlgData m_DlgData;
    /* 0x3c */ EXMemCardDlg* m_pMemCardDlg;
    /* 0x40 */ Bool m_bIgnoreNewMessages;
    /* 0x41 */ Bool m_bMultiCardOpFlag;

public:
    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // /* 0x44 */ __vtbl_ptr_type* vf24091;

    // EXBaseMemCard& operator=();
    EXBaseMemCard();
    /* vtable[1] */ virtual ~EXBaseMemCard();
    /* vtable[2] */ virtual Bool Init(EXSaveInfo& Info);
    /* vtable[3] */ virtual s32 CardChanged(Bool& Changed);
    /* vtable[4] */ virtual s32 CheckSavePossible(u64 Flags);
    /* vtable[5] */ virtual s32 CheckLoadPossible(u64 Flags);
    /* vtable[6] */ virtual s32 SavesPresent(u8& SaveBits, u32 Flags);
    /* vtable[7] */ virtual s32 Save(u8 Save, void* pData, u64 Flags);
    /* vtable[8] */ virtual s32 Load(u8 Save, void* pData, u64 Flags, u64 Size);
    /* vtable[9] */ virtual Bool CheckHardDiskSpace();
    /* vtable[10] */ virtual void SetSaveDirectory();
    void SetMemCardDlgClass();
    char* Message(s64 Code) const;
    void StartMultiCardOp();
    void EndMultiCardOp();

protected:
    void SetDlgHashCodes(u64 MessageHash, u64 OptCount, u64 OptHash1, u64 OptHash2, u64 OptHash3,
                         u64 OptHash4);
    void SetDlgMessages(char* Message, u64 OptCount, char* Opt1, char* Opt2, char* Opt3,
                        char* Opt4);
    void SetDlgMemRequired();
    void SetDlgSlotName();
    void ShowDlg(u64 DlgType, u64 DefaultOpt);
    Bool DlgVisible();
    void HideDlg();
    u32 DlgResult();
    u32 CRC32();
};

#endif // EXMEMCARD_H
