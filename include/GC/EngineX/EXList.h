#ifndef EXLIST_H
#define EXLIST_H

#include "types.h"

struct EXDListItem
{ // 0x8
    /* 0x0 */ EXDListItem* m_pPrev;
    /* 0x4 */ EXDListItem* m_pNext;

public:
    // EXDListItem& operator=();
    // EXDListItem();
    void Init();
    void Add(EXDListItem* pDlistItem);
    void Insert(EXDListItem* pDlistItem);
    void Remove();
    EXDListItem* Next();
    EXDListItem* Prev();
    void SetNext();
    void SetPrev();
    Bool Apply(void* func, void* parm1);
    Bool ApplyBack();
};

struct EXDList
{ // 0x8

    /* 0x0 */ EXDListItem* m_pHead;
    /* 0x4 */ EXDListItem* m_pTail;

public:
    // EXDList& operator=();
    // EXDList();
    void Init();
    void AddHead(EXDListItem* pDListItem);
    void AddTail(EXDListItem* pDListItem);
    void Remove(EXDListItem* pDListItem);
    void Insert(EXDListItem* pItemAt, EXDListItem* pDListItem);
    // void AddHead();
    // void AddTail();
    // void Remove();
    EXDListItem* RemoveHead();
    EXDListItem* RemoveTail();
    EXDListItem* Head();
    EXDListItem* Tail();
    void SetHead();
    void SetTail();
    Bool Apply();
    Bool ApplyBack();
    Bool IsMember(EXDListItem* pDListItem) const;
    u32 Count() const;
};

struct EXLDListItem;

struct EXLDList : EXDList
{
    EXLDList();
    void AddHead(EXLDListItem* pDListItem);
    void AddTail();
};

struct EXLDListItem : /* 0x0 */ EXDListItem
{ // 0xc
    /* 0x8 */ EXLDList* m_pList;

public:
    // EXLDListItem& operator=();
    EXLDListItem();
    // EXLDListItem();
    void Init();
    void Remove();
    void Add();
    void Insert();
    void SetList();
    EXLDList* List();
};

struct EXODListItem
{
    EXODListItem* m_pPrev;
    EXODListItem* m_pNext;
    void* m_pObject;

    EXODListItem();
    void Init();
    void Remove();
    void Add(EXODListItem* pDlistItem, void* pObject);
    void Insert(EXODListItem* pDlistItem, void* pObject);
    EXODListItem* Next();
    EXODListItem* Prev();
    void SetNext();
    void SetPrev();
    void* Object();
    void SetObject();
    Bool Apply();
    Bool ApplyBack();
};

struct EXODList
{
    EXODListItem* m_pHead;
    EXODListItem* m_pTail;

    // EXODList(); unused
    void Init();
    void AddHead(EXODListItem* pDlistItem, void* pObject);
    void AddTail(EXODListItem* pDlistItem, void* pObject);
    void Remove(EXODListItem* pDlistItem);
    EXODListItem* RemoveHead();
    EXODListItem* RemoveTail();
    EXODListItem* Head();
    EXODListItem* Tail();
    Bool Apply();
    Bool ApplyBack();
    Bool IsMember(EXODListItem* pDListItem);
    u32 Count();
};

#endif // EXLIST_H
