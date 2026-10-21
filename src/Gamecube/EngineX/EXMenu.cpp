#include "EngineX/EXMenu.h"

EXMenuItem::~EXMenuItem()
{
}

// Uncompleteable until EXWnd is implemented?
EXMenu::EXMenu()
{
    m_TopLevel = 1;
    m_PushPinIn = NULL;
    m_Items.m_pHead = NULL;
    m_Items.m_pTail = NULL;
    m_pMenuWnd->m_pPrev = NULL;
    m_pWnd->m_pPrev = NULL;
    m_ShowPushPin = NULL;
    m_ShowClose = NULL;
}

EXMenu::~EXMenu()
{
}

EXMenu* EXMenu::AddSubMenu(EXString& Name, unsigned long ID)
{
    EXMenuItem* pElement;
    void* pm;
}

void EXMenu::AddItem(EXString& Name, unsigned long ID)
{
    EXMenuItem* pElement;
    void* pm;
}

Bool EXMenu::DelItemByIndex(unsigned long index)
{
    /* v1 3 */ u32 Item;
    /* a1 5 */ EXODListItem* pListItem;
    // /* a1 5 */ EXODListItem *this;
}

Bool EXMenu::DelItemByID(unsigned long ID, Bool SearchSubMenus)
{
    /* s0 16 */ EXODListItem* pListItem;
    /* s1 17 */ EXMenuItem* pItem;
    // /* s0 16 */ EXODListItem* this;
    // /* s1 17 */ EXMenuItem* pItem;
}

Bool EXMenu::DelAllItems()
{
    /* a0 4 */ EXODListItem* pListItem;
    // /* a0 4 */ EXODListItem* this;
}

void EXMenu::Open(EXWnd* pWnd, s32 x, s32 y)
{
    // /* v0 2 */ EXBaseWnd *this;
    // /* a0 4 */ EXBaseWnd *this;
    /* v0 2 */ s32 w;
    /* v0 2 */ s32 _w;
    // /* v1 3 */ EXBaseWnd *this;
    /* 0x0(sp) */ EXRect rct;
    /* a1 5 */ u16 dh;
    // /* a1 5 */ EXBaseWnd *this;
    // /* a0 4 */ s32 &n1;
    // /* v1 3 */ s32 &n2;
    // /* a1 5 */ EXMenuWnd *this;
    // /* v1 3 */ EXBaseWnd *this;
}

void EXMenu::Close()
{
}

EXMenuWnd::EXMenuWnd(EXMenu* pMenu)
{
    // /* s4 20 */ EXDataArray<EXRect,EXRect &> *this;
    // /* s3 19 */ u32 MaxChars;
    // /* s2 18 */ EXODListItem *pListItem;
    // /* v0 2 */ EXRect *this;
    // /* s1 17 */ EXWnd *pWnd;
    // /* v0 2 */ EXMenu *this;
    // /* s1 17 */ EXWnd *pWnd;
    // /* v0 2 */ EXMenu *this;
    // /* a0 4 */ EXMenuItem *pItem;
    // /* s2 18 */ EXODListItem *this;
    // /* v0 2 */ EXMenu *this;
    // /* v0 2 */ EXMenu *this;
    // /* v0 2 */ EXMenu *this;
}

EXMenuWnd::~EXMenuWnd()
{
}

Bool EXMenuWnd::Update()
{
    // /* s5 21 */ Bool CntUpdate;
    // /* 0x0(sp) */ EXPoint ptPrim;
    // /* s6 22 */ EXWnd *pMouseWnd;
    // /* s4 20 */ u32 nItem;
    // /* v1 3 */ s32 _x;
    // /* v0 2 */ s32 _y;
    // /* a1 5 */ EXMenu *this;
    // /* 0x10(sp) */ EXRect rct;
    // /* s3 19 */ EXODListItem *pListItem;
    // /* v0 2 */ s32 _x;
    // /* a0 4 */ s32 _y;
    // /* s2 18 */ EXMenuItem *pItem;
    // /* s3 19 */ EXODListItem *this;
    // /* s0 16 */ EXString *this;
    // /* 0x10(sp) */ EXRect rct;
    // /* 0x20(sp) */ EXRect nullrect;
    // /* s0 16 */ EXODListItem *pListItem;
    // /* a0 4 */ s32 _x;
    // /* v0 2 */ s32 _y;
    // /* v1 3 */ s32 _w;
    // /* s1 17 */ EXBaseWnd *this;
    // /* v0 2 */ EXMenu *this;
    // /* s2 18 */ EXMenuItem *pItem;
    // /* s0 16 */ EXODListItem *this;
    // /* s3 19 */ u16 Row;
    // /* s1 17 */ EXBaseWnd *this;
    // /* s1 17 */ EXBaseWnd *this;
    // /* s1 17 */ EXBaseWnd *this;
    // /* s1 17 */ EXBaseWnd *this;
    // /* s1 17 */ EXBaseWnd *this;
    // /* s1 17 */ EXBaseWnd *this;
    // /* a1 5 */ EXMenu *this;
    // /* 0x10(sp) */ EXRect rct;
    // /* s0 16 */ u16 XPos;
    // /* v0 2 */ s32 _x;
    // /* v1 3 */ s32 _y;
    // /* s1 17 */ EXBaseWnd *this;
    // /* v0 2 */ EXMenu *this;
    // /* v0 2 */ EXMenu *this;
    // /* s1 17 */ EXBaseWnd *this;
    // /* s1 17 */ EXBaseWnd *this;
}

/* 003855e0 00000244 */ Bool EXMenuWnd::Draw()
{
    // /* 0x0(sp) */ EXPoint ptPrim;
    // /* v0 2 */ s32 _x;
    // /* v1 3 */ s32 _y;
    // /* s1 17 */ EXRect *this;
    // /* s2 18 */ int nItem;
    // /* 0x10(sp) */ EXRect rct;
    // /* s3 19 */ EXDataArray<EXRect,EXRect &> *this;
    // /* s2 18 */ int iPos;
    // /* a0 4 */ s32 _y;
    // /* v1 3 */ s32 _x;
    // /* v0 2 */ EXRect *this;
    // /* a0 4 */ int nItem;
    // /* v1 3 */ EXODListItem *pListItem;
    // /* v0 2 */ EXMenu *this;
    // /* v1 3 */ EXODListItem *this;
    // /* a0 4 */ int iPos;
    // /* a0 4 */ EXRect *this;
    // /* a1 5 */ s32 _y;
    // /* v1 3 */ s32 _x;
    // /* s0 16 */ EXBaseWnd *this;
}

void EXMenuWnd::ButtonDown(unsigned long Button)
{
    // /* 0x0(sp) */ EXPoint ptPrim;
    // /* s4 20 */ u32 nItem;
    // /* s1 17 */ EXODListItem *pListItem;
    // /* a0 4 */ s32 _x;
    // /* a1 5 */ s32 _y;
    // /* a2 6 */ EXRect *this;
    // /* s0 16 */ EXWnd *pOldMouseWnd;
    // /* v0 2 */ EXMenu *this;
    // /* s2 18 */ EXMenuItem *pItem;
    // /* s1 17 */ EXODListItem *this;
    // /* 0x10(sp) */ EXRect rct;
    // /* a1 5 */ int iPos;
    // /* a1 5 */ EXMenu *this;
    // /* 0x10(sp) */ EXRect rct;
    // /* a1 5 */ u16 XPos;
    // /* a2 6 */ s32 _x;
    // /* v0 2 */ s32 _y;
    // /* s0 16 */ EXBaseWnd *this;
    // /* v0 2 */ EXMenu *this;
    // /* v0 2 */ EXMenu *this;
    // /* v1 3 */ EXMenu *this;
    // /* v1 3 */ u32 &n1;
    // /* a0 4 */ u32 &n2;
    // /* s0 16 */ EXBaseWnd *this;
    // /* s0 16 */ EXBaseWnd *this;
    // /* v0 2 */ u32 &n1;
    // /* v1 3 */ u32 &n2;
}

void EXMenuWnd::ButtonUp(unsigned long Button)
{
    // /* v0 2 */ EXMenu* this;
}

void EXMenuWnd::MouseMove(s64 dx, s64 dy)
{
}

void EXMenuWnd::CloseSubMenu()
{
}

void EXMenuWnd::ProcessItem(EXMenuItem* pItem, EXRect& rct)
{
    // /* 0x0(sp) */ EXPoint pt;
    // /* s0 16 */ EXRect *this;
    // /* a1 5 */ s32 _y;
    // /* a0 4 */ s32 _x;
    // /* v1 3 */ EXMenu *this;
    // /* v0 2 */ EXMenu *this;
}
