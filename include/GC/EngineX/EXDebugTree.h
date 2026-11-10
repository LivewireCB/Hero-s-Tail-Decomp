#ifndef EXDEBUGTREE_H
#define EXDEBUGTREE_H

#include "types.h"
#include "EngineX/EXArray.h"
#include "EngineX/EXFixedArray.h"
#include "EngineX/EXList.h"

struct EXDebugTreeSection : EXDListItem
{ // 0x30
    /* 0x08 */ u16 ParentSectionHandle;
    /* 0x0a */ u16 Flags2;
    /* 0x0c */ EXDList Children;
    /* 0x14 */ EXDList Items;
    /* 0x1c */ char* Name;
    /* 0x20 */ EXFixedArray<char, 15> NameCopy;
    /* 0x2f */ union
    {
        u8 Flags;
        struct
        {
            u8 Open : 1;
            u8 Deleted : 1;
            u8 Pad : 2;
            u8 UserFlags : 4;
        };
    };
};

struct EXDebugTreeItem : EXDListItem
{ // 0x28
    /* 0x08 */ u16 SectionHandle;
    /* 0x0a */ u16 Flags2;
    /* 0x0c */ u32 uData;
    /* 0x10 */ u32 uData2;
    /* 0x14 */ char* Name;
    /* 0x18 */ EXFixedArray<char, 15> NameCopy;
    /* 0x27 */ union
    {
        u8 Flags;
        struct
        {
            u8 Deleted : 1;
            u8 Pad : 3;
            u8 UserFlags : 4;
        };
    };
};

struct EXDebugTree
{ // 0x2c
    enum ADD_DUPLICATE_ACTION
    {
        DONT_ADD_DUPLICATES = 0,
        ADD_DUPLICATES = 1,
        UPDATE_DUPLICATES = 2
    };

protected:
    /* 0x00 */ EXArray<EXDebugTreeSection, EXDebugTreeSection&> m_Sections;
    /* 0x14 */ EXArray<EXDebugTreeItem, EXDebugTreeItem&> m_Items;

public:
    EXDebugTree(unsigned long InitSections, unsigned long InitItems);
    virtual ~EXDebugTree();

    int NumSections();
    unsigned long SectionHandle(char* Name, unsigned long SectionFlags2);
    virtual unsigned long AddSection(char* Name, unsigned long ParentSectionHandle,
                                     ADD_DUPLICATE_ACTION AddDuplicateAction = DONT_ADD_DUPLICATES);
    virtual unsigned long AddSection(char* Name, char* ParentSection);
    virtual void DelSection(unsigned long SectionHandle);
    EXDebugTreeSection* Section(unsigned long SectionHandle);

    int NumItems();
    unsigned long ItemHandle(char* Name);
    unsigned long ItemHandle(char* Name, unsigned long SectionHandle);
    virtual unsigned long AddItem(char* Name, unsigned long SectionHandle, unsigned long uData,
                                  ADD_DUPLICATE_ACTION AddDuplicateAction = DONT_ADD_DUPLICATES);
    virtual unsigned long AddItem(char* Name, char* SectionName, unsigned long uData);
    virtual void DelItem(unsigned long ItemHandle);
    EXDebugTreeItem* Item(unsigned long ItemHandle);

protected:
    void DelSection(EXDebugTreeSection* pSect);
    virtual void DelItem(EXDebugTreeItem* pItem);
    void RemapItems(long ItemOffset);
};

struct EXInfoTree : EXDebugTree
{ // 0x2c
    EXInfoTree(unsigned long InitSections, unsigned long InitItems);
    virtual ~EXInfoTree();
    unsigned long AddInfoItem(char* Name, unsigned long SectionHandle, unsigned long uData, Bool DrawName,
                              ADD_DUPLICATE_ACTION AddDuplicateAction);
    unsigned long AddInfoItem(char* Name, unsigned long SectionHandle, char* pStr, Bool DrawName,
                              ADD_DUPLICATE_ACTION AddDuplicateAction);
    void Empty();

protected:
    virtual void DelItem(EXDebugTreeItem* pItem);
};

#endif // EXDEBUGTREE_H
