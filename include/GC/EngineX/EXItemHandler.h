#ifndef EXITEMHANDLER_H
#define EXITEMHANDLER_H

#include "types.h"

#include "EXRuntimeClass.h"
#include "EXItem.h"
#include "EXMalloc.h"

struct EXItemHandler
{ // 0x8
    static EXRuntimeClass classEXItemHandler;

    /* 0x0 */ EXItem* m_pItem;

    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // /* 0x4 */ __vtbl_ptr_type* vf8842;

    // EXItemHandler& operator=();
    EXItemHandler();

    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    ~EXItemHandler();
    // /* vtable[2] */ virtual EXItemHandler(EXItemHandler*, int, void);
    void SetItem();
    EXItem* GetItem();
    /* vtable[3] */ virtual Bool Initialise();
    /* vtable[4] */ virtual Bool DoUpdate();
    /* vtable[5] */ virtual Bool DoPostUpdate();
    /* vtable[6] */ virtual u32 DoScriptCmdEvent();
    /* vtable[7] */ virtual u32 DoScriptCmdObject();
    /* vtable[8] */ virtual u32 DoScriptCmdRunControl();
    /* vtable[9] */ virtual u32 DoAnimModeFunction();
};

#endif // EXITEMHANDLER_H
