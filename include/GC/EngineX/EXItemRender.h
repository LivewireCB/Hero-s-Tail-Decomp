#ifndef EXITEMRENDER_H
#define EXITEMRENDER_H

#include "types.h"

#include "EXRuntimeClass.h"

#include "EXItem.h"
#include "EXMalloc.h"

typedef void ITEMRENDERCALLBACK(/* parameters unknown */);

struct EXItemRender
{ // 0xc
    static EXRuntimeClass classEXItemRender;

    /* 0x0 */ EXBaseItem* m_pOwner;
    /* 0x4 */ ITEMRENDERCALLBACK* m_pUserCallback;

    // EXAMPLE: the ItemRender constructor does NOT match with the vf8576 in the struct
    // Seems like these need to be commented out across the repo

    // /* 0x8 */ __vtbl_ptr_type* vf8576;

    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

    // EXItemRender& operator=();
    EXItemRender();

    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXItemRender* CreateObject(/* parameters unknown */);
    // EXItemRender();
    // /* vtable[2] */ virtual EXItemRender(EXItemRender*, int, void);
    void SetOwner();
    EXBaseItem* GetOwner();
    EXBaseItem* GetBaseOwner() const;
    void SetUserRender();
};

#endif // EXITEMRENDER_H
