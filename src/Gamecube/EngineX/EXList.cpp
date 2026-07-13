#include <EngineX/EXList.h>

void EXDListItem::Add(EXDListItem* pDlistItem)
{
    EXDListItem* pNext;

    pNext = m_pNext;
    pDlistItem->m_pNext = pNext;
    pDlistItem->m_pPrev = this;

    if (pNext != 0)
    {
        pNext->m_pPrev = pDlistItem;
    }

    m_pNext = pDlistItem;
}

void EXDListItem::Insert(EXDListItem* pDlistItem)
{
    EXDListItem* pPrev;

    pPrev = m_pPrev;
    pDlistItem->m_pNext = this;
    pDlistItem->m_pPrev = pPrev;

    if (pPrev != 0)
    {
        pPrev->m_pNext = pDlistItem;
    }

    m_pPrev = pDlistItem;
}

void EXDListItem::Remove()
{
    EXDListItem* pPrev;
    EXDListItem* pNext;

    pPrev = m_pPrev;
    pNext = m_pNext;

    if (pPrev != 0)
    {
        pPrev->m_pNext = pNext;
        m_pPrev = 0;
    }

    if (pNext == 0)
    {
        return;
    }

    pNext->m_pPrev = pPrev;

    m_pNext = 0;
}

Bool EXDListItem::Apply(void* func, void* parm1) // Not our typo. The devs have it as parm1
{
    EXDListItem* pNext;
    Bool (*call)(void*, void*) = (Bool(*)(void*, void*))func;
    EXDListItem* pDListItem;

    pDListItem = this;
    if (pDListItem != 0)
    {
        do
        {
            pNext = pDListItem->m_pNext;

            if (!call(pDListItem, parm1))
            {
                return 0;
            }

            pDListItem = pNext;
        } while (pDListItem != 0);
    }
    return true;
}

void EXDList::AddHead(EXDListItem* pDListItem)
{
    EXDListItem* pHead;

    pHead = m_pHead;

    pDListItem->m_pPrev = NULL;
    pDListItem->m_pNext = pHead;

    if (pHead != NULL)
    {
        pHead->m_pPrev = pDListItem;
    }

    m_pHead = pDListItem;

    if (m_pTail == NULL)
    {
        m_pTail = pDListItem;
    }
}

void EXDList::AddTail(EXDListItem* pDListItem)
{
    EXDListItem* pTail;

    pTail = m_pTail;

    pDListItem->m_pPrev = pTail;
    pDListItem->m_pNext = NULL;

    if (pTail != NULL)
    {
        pTail->m_pNext = pDListItem;
    }

    m_pTail = pDListItem;

    if (m_pHead == NULL)
    {
        m_pHead = pDListItem;
    }
}

void EXDList::Insert(EXDListItem* pItemAt, EXDListItem* pDListItem)
{
    EXDListItem* pHead;
    EXDListItem* pPrev;

    pHead = m_pHead;
    if (pHead == 0)
    {
        AddHead(pDListItem);
    }
    else
    {
        pPrev = pItemAt->m_pPrev;
        pDListItem->m_pNext = pItemAt;

        pDListItem->m_pPrev = pPrev;

        if (pItemAt == pHead)
        {
            m_pHead = pDListItem;
        }
        else
        {
            pPrev->m_pNext = pDListItem;
        }

        pItemAt->m_pPrev = pDListItem;
    }
}

void EXDList::Remove(EXDListItem* pDListItem)
{
    if (pDListItem == m_pHead)
    {
        m_pHead = pDListItem->m_pNext;
    }

    if (pDListItem == m_pTail)
    {
        m_pTail = pDListItem->m_pPrev;
    }

    pDListItem->Remove();
}

EXDListItem* EXDList::RemoveTail()
{
    EXDListItem* pTail = m_pTail;
    if (m_pTail != NULL)
    {
        if (m_pTail == m_pHead)
        {
            m_pHead = pTail->m_pNext;
        }
        m_pTail = pTail->m_pPrev;
        pTail->Remove();
    }
    return pTail;
}

Bool EXDList::IsMember(EXDListItem* pDListItem) const
{
    EXDListItem* pItem;

    pItem = m_pHead;

    while (pItem != NULL)
    {
        if (pItem == pDListItem)
        {
            return true;
        }
        pItem = pItem->m_pNext;
    }

    return false;
}

u32 EXDList::Count() const
{
    u32 nCount = 0;
    EXDListItem* pItem;

    for (pItem = m_pHead; pItem != NULL; pItem = pItem->m_pNext)
    {
        nCount++;
    }

    return nCount;
}

void EXLDListItem::Remove()
{
    if (m_pList != NULL)
    {
        m_pList->Remove(this);
        m_pList = NULL;
    }
}

void EXLDList::AddHead(EXLDListItem* pDListItem)
{
    EXDListItem* pHead;

    pHead = this->m_pHead;
    pDListItem->m_pPrev = NULL;
    pDListItem->m_pNext = pHead;
    pDListItem->m_pList = this;

    if (pHead != NULL)
    {
        pHead->m_pPrev = pDListItem;
    }

    this->m_pHead = pDListItem;

    if (this->m_pTail == NULL)
    {
        this->m_pTail = pDListItem;
    }
}

void EXODListItem::Add(EXODListItem* pDlistItem, void* pObject)
{
    EXODListItem* pNext;

    pNext = m_pNext;
    pDlistItem->m_pPrev = this;
    pDlistItem->m_pNext = pNext;
    pDlistItem->m_pObject = pObject;

    if (pObject == 0)
    {
        pDlistItem->m_pObject = pDlistItem;
    }

    if (pNext != 0)
    {
        pNext->m_pPrev = pDlistItem;
    }
    m_pNext = pDlistItem;
}

void EXODListItem::Insert(EXODListItem* pDlistItem, void* pObject)
{
    EXODListItem* pPrev;

    pPrev = m_pPrev;
    pDlistItem->m_pPrev = pPrev;
    pDlistItem->m_pNext = this;
    pDlistItem->m_pObject = pObject;

    if (pObject == 0)
    {
        pDlistItem->m_pObject = pDlistItem;
    }

    if (pPrev != 0)
    {
        pPrev->m_pNext = pDlistItem;
    }
    m_pPrev = pDlistItem;
}

void EXODListItem::Remove()
{
    EXODListItem* pPrev;
    EXODListItem* pNext;

    pPrev = this->m_pPrev;
    pNext = this->m_pNext;

    if (pPrev != 0)
    {
        pPrev->m_pNext = pNext;
        m_pPrev = 0;
    }

    if (pNext != 0)
    {
        pNext->m_pPrev = pPrev;
        this->m_pNext = NULL;
    }
}

void EXODList::AddHead(EXODListItem* pDlistItem, void* pObject)
{
    EXODListItem* pHead;

    pHead = m_pHead;

    pDlistItem->m_pPrev = NULL;
    pDlistItem->m_pNext = pHead;

    if (pObject == 0)
    {
        pObject = pDlistItem;
    }

    pDlistItem->m_pObject = pObject;

    if (pHead != NULL)
    {
        pHead->m_pPrev = pDlistItem;
    }

    m_pHead = pDlistItem;

    if (m_pTail == NULL)
    {
        m_pTail = pDlistItem;
    }
}

void EXODList::AddTail(EXODListItem* pDlistItem, void* pObject)
{
    EXODListItem* pTail;

    pTail = m_pTail;

    pDlistItem->m_pPrev = pTail;
    pDlistItem->m_pNext = NULL;

    if (pObject == 0)
    {
        pObject = pDlistItem;
    }

    pDlistItem->m_pObject = pObject;

    if (pTail != NULL)
    {
        pTail->m_pNext = pDlistItem;
    }

    m_pTail = pDlistItem;

    if (m_pHead == NULL)
    {
        m_pHead = pDlistItem;
    }
}

void EXODList::Remove(EXODListItem* pDlistItem)
{
    if (pDlistItem == m_pHead)
    {
        m_pHead = pDlistItem->m_pNext;
    }

    if (pDlistItem == m_pTail)
    {
        m_pTail = pDlistItem->m_pPrev;
    }

    pDlistItem->Remove();
}

EXODListItem* EXODList::RemoveHead()
{
    EXODListItem* pHead = m_pHead;
    if (pHead != NULL)
    {
        Remove(pHead);
    }
    return pHead;
}

Bool EXODList::IsMember(EXODListItem* pDListItem)
{
    EXODListItem* pItem;

    pItem = m_pHead;

    while (pItem != NULL)
    {
        if (pItem == pDListItem)
        {
            return true;
        }
        pItem = pItem->m_pNext;
    }

    return false;
}
