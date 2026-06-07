#ifndef EXMEMCARD_H
#define EXMEMCARD_H

#include "types.h"

struct EXBaseMemCard
{
    // /* 0x00 */ EXRuntimeClass* m_pDlgClass;
    // /* 0x04 */ EXMemCardDlgData m_DlgData;
    // /* 0x3c */ EXMemCardDlg* m_pMemCardDlg;
    /* 0x40 */ Bool m_bIgnoreNewMessages;
    /* 0x41 */ Bool m_bMultiCardOpFlag;
    // /* 0x44 */ __vtbl_ptr_type* $vf24091;

    // EXBaseMemCard& operator=();
    EXBaseMemCard();
    // EXBaseMemCard();
    // /* vtable[1] */ virtual EXBaseMemCard(EXBaseMemCard*, int, void);
    /* vtable[2] */ virtual Bool Init();
    /* vtable[3] */ virtual s32 CardChanged();
    /* vtable[4] */ virtual s32 CheckSavePossible();
    /* vtable[5] */ virtual s32 CheckLoadPossible();
    /* vtable[6] */ virtual s32 SavesPresent();
    /* vtable[7] */ virtual s32 Save();
    /* vtable[8] */ virtual s32 Load();
    /* vtable[9] */ virtual Bool CheckHardDiskSpace();
    /* vtable[10] */ virtual void SetSaveDirectory();
    void SetMemCardDlgClass();
    char* Message();
    void StartMultiCardOp();
    void EndMultiCardOp();

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
