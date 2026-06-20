#ifndef EXITEM_H
#define EXITEM_H

#include "types.h"

#include "EXFlagTemplate.h"
#include "EXList.h"

struct EXBaseItem : /* 0x00 */ EXDListItem
{ // 0x1c
protected:
    /* 0x08 */ EXBaseItem* m_pOwner;
    /* 0x0c */ EXFlag16 m_ItemFlags;
    /* 0x0e */ s16 m_pad0;
    /* 0x10 */ EXDList m_Nodes;

public:
    /* 0x18 */ __vtbl_ptr_type* vf8249;

    // EXBaseItem& operator=();
    EXBaseItem();
    // EXBaseItem();
    // /* vtable[1] */ virtual EXBaseItem(EXBaseItem*, int, void);
    EXDList& Nodes();
    void SetOwner();
    EXBaseItem* GetOwner();
    EXBaseItem* GetBaseOwner() const;
};

#endif // EXITEM_H
