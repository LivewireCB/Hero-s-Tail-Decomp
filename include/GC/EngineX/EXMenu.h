#ifndef EXMENU_H
#define EXMENU_H

#include "types.h"

#include "EngineX/EXAllocator.h"
#include "EngineX/EXString.h"
#include "EngineX/GC/GCWnd.h"

struct EXMenuItem;
struct EXMenuWnd;

struct EXAllocator<EXMenuItem>
{ // 0x14
protected:
    /* 0x00 */ EXAllocatorBlockArray m_Blocks;
    /* 0x10 */ u32 m_BlockSize;

public:
    // EXAllocator<EXMenuItem>& operator=();
    EXAllocator();
    // EXAllocator();
    ~EXAllocator();
    EXMenuItem* Get();
    void Remove();
};

// EXClassAllocator is only ever used here? Thanks Eurocom
template <typename T> struct EXClassAllocator
{
};

struct EXClassAllocator<EXMenuItem> : /* 0x00 */ EXAllocator<EXMenuItem>
{ // 0x14
    // EXClassAllocator<EXMenuItem>& operator=();
    EXClassAllocator();
    ~EXClassAllocator();
    // EXClassAllocator();
    EXMenuItem* Get();
    void Remove();
};

struct EXMenu
{ // 0x1c
protected:
    /* 0x00 */ Bool m_TopLevel;
    /* 0x04 */ EXODList m_Items;
    /* 0x0c */ EXWnd* m_pWnd;
    /* 0x10 */ EXMenuWnd* m_pMenuWnd;
    /* 0x14 */ Bool m_ShowClose;
    /* 0x15 */ Bool m_ShowPushPin;
    /* 0x16 */ Bool m_PushPinIn;
    static EXClassAllocator<EXMenuItem> m_MenuItemAllocator;

public:
    // /* 0x18 */ __vtbl_ptr_type* $vf2778;

    // EXMenu& operator=();
    EXMenu();
    // EXMenu();
    /* vtable[1] */ virtual ~EXMenu();
    EXMenu* AddSubMenu(EXString& Name, unsigned long ID);
    void AddItem(EXString& Name, unsigned long ID);
    EXMenuItem* ItemByIndex(unsigned long);
    EXMenuItem* ItemByID();
    Bool DelItemByIndex(unsigned long);
    Bool DelItemByID(unsigned long, Bool);
    Bool DelAllItems();
    void Open(EXWnd* pWnd, s32 x, s32 y);
    void Close();
    Bool IsOpen();
    Bool TopLevel();
    void SetTopLevel();
    void ShowCloseButton();
    Bool CloseButtonVisible();
    void ShowPushPin();
    Bool PushPinVisible();
    void SetPushPinIn();
    Bool PushPinIn();
    EXWnd* Wnd();
    EXMenuWnd* MenuWnd();

protected:
    EXODListItem* FirstListItem();
    EXMenuItem* FirstItem();
};

struct EXMenuItem
{ // 0x18
    /* 0x00 */ EXODListItem ListItem;
    /* 0x0c */ EXString Name;
    /* 0x10 */ u32 ID;
    /* 0x14 */ EXMenu* pSubMenu;

    ~EXMenuItem();
};

struct EXMenuWnd : /* 0x0000 */ EXWnd
{ // 0x12f0
protected:
    /* 0x12b0 */ EXWnd* m_pOldFocusWnd;
    /* 0x12b4 */ EXWnd* m_pOldMouseWnd;
    /* 0x12b8 */ EXMenu* m_pTheMenu;
    /* 0x12bc */ EXDataArray<EXRect, EXRect&> m_ItemRect;
    /* 0x12cc */ EXMenu* m_pSubMenu;
    /* 0x12d0 */ EXRect m_rctHilite;
    /* 0x12e0 */ Bool m_ScrollMenu;
    /* 0x12e4 */ u32 m_ScrollOffset;
    /* 0x12e8 */ u32 m_ItemCount;
    /* 0x12ec */ u16 m_MenuTimer;

public:
    // EXMenuWnd& operator=();
    // EXMenuWnd();
    EXMenuWnd(EXMenu* pMenu);
    /* vtable[1] */ virtual ~EXMenuWnd();
    void SetScrollMenu();
    /* vtable[10] */ virtual Bool Update();
    /* vtable[17] */ virtual Bool Draw();
    /* vtable[21] */ virtual void ButtonDown(unsigned long Button);
    /* vtable[22] */ virtual void ButtonUp(unsigned long Button);
    /* vtable[23] */ virtual void MouseMove(s64 dx, s64 dy);
    void CloseSubMenu();

protected:
    void ProcessItem(EXMenuItem* pItem, EXRect& rct);
};

#endif // EXMENU_H
