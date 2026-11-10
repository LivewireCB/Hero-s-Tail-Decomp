#ifndef EXITEMHANDLER_H
#define EXITEMHANDLER_H

#include "types.h"

#include "EXRuntimeClass.h"
// Creates a cyclic dependency if EXItem is included. Using forward dec instead.
// #include "EXItem.h"
#include "EXMalloc.h"

struct EXItem;
struct EXItemAnimator;
struct GEOSCRIPT_EVENT;
struct GEOSCRIPT_BASECMD;
struct GEOSCRIPT_RUNCONTROL;
struct EXGeoAnimSetHeader;
struct EXGeoAnimModeFunction;

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

    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    ~EXItemHandler();
    // /* vtable[2] */ virtual EXItemHandler(EXItemHandler*, int, void);
    void SetItem();
    EXItem* GetItem();
    /* vtable[3] */ virtual Bool Initialise();
    /* vtable[4] */ virtual Bool DoUpdate();
    /* vtable[5] */ virtual Bool DoPostUpdate();
    /* vtable[6] */ virtual u32 DoScriptCmdEvent(GEOSCRIPT_EVENT* pEventCmd,
                                                 EXItemAnimator* pParentAnimator);
    /* vtable[7] */ virtual u32 DoScriptCmdObject(GEOSCRIPT_BASECMD* pCmd,
                                                  EXItemAnimator* pAnimator);
    /* vtable[8] */ virtual u32 DoScriptCmdRunControl(GEOSCRIPT_RUNCONTROL* pRCCmd,
                                                      EXItemAnimator* pAnimator);
    /* vtable[9] */ virtual u32 DoAnimModeFunction(EXGeoAnimSetHeader* pAnimSetHeader,
                                                   EXGeoAnimModeFunction* pFunc,
                                                   EXItemAnimator* pAnimator);
};

#endif // EXITEMHANDLER_H
