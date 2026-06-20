#ifndef EXMEMCARD_H
#define EXMEMCARD_H

#include "types.h"

#include "EXFixedArray.h"
#include "EXHashcode.h"
#include "EXRuntimeClass.h"

struct EXFixedArray<const char*, 4>
{ // 0x10
    /* 0x0 */ char* m_Data[4];

    // EXFixedArray<const char*, 4>& operator=();
    EXFixedArray();
    // EXFixedArray();
    size_t Size();
    size_t GetUpperBound();
    char*& ElementAt();
    char* GetAt();
    void SetAt();
    char** GetData();
    // char** GetData();
    // char** operator char**();
    // char** operator char**();
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
    // /* 0x0 */ EXMemCardDlgWnd* m_pWnd;

public:
    /* 0x4 */ __vtbl_ptr_type* vf24075;

    // EXMemCardDlg& operator=();
    EXMemCardDlg();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXMemCardDlg* CreateObject(/* parameters unknown */);
    // EXMemCardDlg();
    // /* vtable[2] */ virtual EXMemCardDlg(EXMemCardDlg*, int, void);
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
    /* 0x44 */ __vtbl_ptr_type* vf24091;

    // EXBaseMemCard& operator=();
    EXBaseMemCard();
    // EXBaseMemCard();
    // /* vtable[1] */ virtual EXBaseMemCard(EXBaseMemCard*, int, void);
    /* vtable[2] */ virtual Bool Init();
    /* vtable[3] */ virtual s32 CardChanged(Bool& Changed);
    /* vtable[4] */ virtual s32 CheckSavePossible(u64 Flags);
    /* vtable[5] */ virtual s32 CheckLoadPossible(u64 Flags);
    /* vtable[6] */ virtual s32 SavesPresent();
    /* vtable[7] */ virtual s32 Save();
    /* vtable[8] */ virtual s32 Load();
    /* vtable[9] */ virtual Bool CheckHardDiskSpace();
    /* vtable[10] */ virtual void SetSaveDirectory();
    void SetMemCardDlgClass();
    char* Message();
    void StartMultiCardOp();
    void EndMultiCardOp();

protected:
    void SetDlgHashCodes();
    void SetDlgMessages();
    void SetDlgMemRequired();
    void SetDlgSlotName();
    void ShowDlg();
    Bool DlgVisible();
    void HideDlg();
    u32 DlgResult();
    u32 CRC32();
};

#endif // EXMEMCARD_H
