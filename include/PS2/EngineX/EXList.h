#ifndef EXLIST_H
#define EXLIST_H

#include <PS2/types.h>

struct EXDListItem
{
    EXDListItem* m_pPrev;
    EXDListItem* m_pNext;

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
{
    EXDListItem* m_pHead;
    EXDListItem* m_pTail;

    void Init();
    void AddHead(EXDListItem* pDListItem);
    void AddTail(EXDListItem* pDListItem);
    void Remove(EXDListItem* pDListItem);
    void Insert(EXDListItem* pItemAt, EXDListItem* pDListItem);
    void Remove();
    EXDListItem* RemoveHead();
    EXDListItem* RemoveTail();
    EXDListItem* Head();
    EXDListItem* Tail();
    void SetHead();
    void SetTail();
    Bool Apply();
    Bool ApplyBack();
    Bool IsMember(EXDListItem* pDListItem) const;
    u32 Count();
};

struct EXLDListItem;

struct EXLDList : EXDList
{
    EXLDList();
    void AddHead(EXLDListItem* pDListItem);
    void AddTail();
};

struct EXLDListItem : EXDListItem
{
    EXLDList* m_pList;

    EXLDListItem();
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

    EXODList();
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
