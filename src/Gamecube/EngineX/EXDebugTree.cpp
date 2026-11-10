#include "EngineX/EXDebugTree.h"

#include "include/GC/libc/string.h"

#include "EngineX/EXMemoryManager.h"
#include "EngineX/EXString.h"

EXDebugTree::EXDebugTree(unsigned long InitSections, unsigned long InitItems)
{
    EXDebugTreeSection* pRoot;

    m_Sections.SetSize(InitSections, -1);
    m_Sections.SetSize(1, InitSections);
    m_Items.SetSize(InitItems, -1);
    m_Items.SetSize(1, InitItems);

    pRoot = &m_Sections[0];
    pRoot->Name = "*ROOT*";
    strncpy(pRoot->NameCopy, "*ROOT*", 14);
    pRoot->NameCopy.ElementAt(14) = 0;
    pRoot->Flags = 0;
}

EXDebugTree::~EXDebugTree()
{
}

unsigned long EXDebugTree::SectionHandle(char* Name, unsigned long SectionFlags2)
{
    EXDebugTreeSection* pSect;
    int s;

    for (s = 1; s < m_Sections.Size(); s++)
    {
        pSect = &m_Sections[s];
        if (pSect->Name == Name && strcmp(Name, pSect->NameCopy) == 0)
        {
            if (SectionFlags2 == 0 || SectionFlags2 == pSect->Flags2)
            {
                return s;
            }
        }
    }

    for (s = 1; s < m_Sections.Size(); s++)
    {
        pSect = &m_Sections[s];
        if (strcmp(Name, pSect->NameCopy) == 0)
        {
            if (SectionFlags2 == 0 || SectionFlags2 == pSect->Flags2)
            {
                return s;
            }
        }
    }

    return 0;
}

unsigned long EXDebugTree::AddSection(char* Name, unsigned long ParentSectionHandle,
                                      ADD_DUPLICATE_ACTION AddDuplicateAction)
{
    unsigned long handle;
    Bool bAdd;
    Bool bUpdate;
    EXDebugTreeSection* pSect;
    int nIndex;

    handle = SectionHandle(Name, 0);
    bAdd = 1;
    bUpdate = 0;

    switch (AddDuplicateAction)
    {
    case ADD_DUPLICATES:
        break;
    case DONT_ADD_DUPLICATES:
    default:
        if (handle != 0)
        {
            bAdd = 0;
        }
        break;
    case UPDATE_DUPLICATES:
        if (handle != 0)
        {
            bUpdate = 1;
        }
        break;
    }

    if (bUpdate)
    {
        pSect = &m_Sections[handle];
        pSect->Name = Name;
        strncpy(pSect->NameCopy, Name, 14);
        pSect->NameCopy.ElementAt(14) = 0;
    }
    else if (bAdd)
    {
        handle = 0;
        for (nIndex = 1; nIndex < m_Sections.Size(); nIndex++)
        {
            if (m_Sections[nIndex].Deleted)
            {
                handle = nIndex;
                break;
            }
        }

        if (handle == 0)
        {
            EXDebugTreeItem* pOldItems;

            handle = m_Sections.Size();
            pOldItems = m_Items.GetData();
            m_Sections.SetSize(handle + 1, -1);
            if (pOldItems != m_Items.GetData())
            {
                RemapItems((long)m_Items.GetData() - (long)pOldItems);
            }
        }

        pSect = &m_Sections[handle];
        pSect->Name = Name;
        strncpy(pSect->NameCopy, Name, 14);
        pSect->NameCopy.ElementAt(14) = 0;
        pSect->Flags = 0;
        m_Sections[ParentSectionHandle].Children.AddTail(pSect);
        pSect->ParentSectionHandle = ParentSectionHandle;
    }

    return handle;
}

unsigned long EXDebugTree::AddSection(char* Name, char* ParentSection)
{
    return AddSection(Name, SectionHandle(ParentSection, 0), DONT_ADD_DUPLICATES);
}

void EXDebugTree::DelSection(unsigned long SectionHandle)
{
    if (SectionHandle != 0 && SectionHandle < m_Sections.Size())
    {
        DelSection(&m_Sections[SectionHandle]);
    }
}

unsigned long EXDebugTree::ItemHandle(char* Name)
{
    EXDebugTreeItem* pItem;
    int i;

    for (i = 1; i < m_Items.Size(); i++)
    {
        pItem = &m_Items[i];
        if (pItem->Name == Name && strcmp(Name, pItem->NameCopy) == 0)
        {
            return i;
        }
    }

    for (i = 1; i < m_Items.Size(); i++)
    {
        if (strcmp(Name, m_Items[i].NameCopy) == 0)
        {
            return i;
        }
    }

    return 0;
}

unsigned long EXDebugTree::ItemHandle(char* Name, unsigned long SectionHandle)
{
    EXDebugTreeItem* pItem;
    EXDebugTreeSection* pSect;

    if (SectionHandle == 0 || SectionHandle >= m_Sections.Size())
    {
        return ItemHandle(Name);
    }

    pSect = &m_Sections[SectionHandle];

    for (pItem = (EXDebugTreeItem*)pSect->Items.Head(); pItem != NULL; pItem = (EXDebugTreeItem*)pItem->Next())
    {
        if (pItem->Name == Name && strcmp(Name, pItem->NameCopy) == 0)
        {
            return ((long)pItem - (long)m_Items.GetData()) / (long)sizeof(EXDebugTreeItem);
        }
    }

    for (pItem = (EXDebugTreeItem*)pSect->Items.Head(); pItem != NULL; pItem = (EXDebugTreeItem*)pItem->Next())
    {
        if (strcmp(Name, pItem->NameCopy) == 0)
        {
            return ((long)pItem - (long)m_Items.GetData()) / (long)sizeof(EXDebugTreeItem);
        }
    }

    return 0;
}

unsigned long EXDebugTree::AddItem(char* Name, unsigned long SectionHandle, unsigned long uData,
                                   ADD_DUPLICATE_ACTION AddDuplicateAction)
{
    unsigned long handle;
    Bool bAdd;
    Bool bUpdate;
    EXDebugTreeItem* pItem;
    int nIndex;

    handle = ItemHandle(Name, SectionHandle);
    bAdd = 1;
    bUpdate = 0;

    switch (AddDuplicateAction)
    {
    case ADD_DUPLICATES:
        break;
    case DONT_ADD_DUPLICATES:
    default:
        if (handle != 0)
        {
            bAdd = 0;
        }
        break;
    case UPDATE_DUPLICATES:
        if (handle != 0)
        {
            bUpdate = 1;
        }
        break;
    }

    if (SectionHandle == 0 || SectionHandle >= m_Sections.Size())
    {
        return 0;
    }

    if (bUpdate)
    {
        m_Items[handle].uData = uData;
    }
    else if (bAdd)
    {
        handle = 0;
        for (nIndex = 1; nIndex < m_Items.Size(); nIndex++)
        {
            if (m_Items[nIndex].Deleted)
            {
                handle = nIndex;
                break;
            }
        }

        if (handle == 0)
        {
            EXDebugTreeItem* pOldItems;

            handle = m_Items.Size();
            pOldItems = m_Items.GetData();
            m_Items.SetSize(handle + 1, -1);
            if (pOldItems != m_Items.GetData())
            {
                RemapItems((long)m_Items.GetData() - (long)pOldItems);
            }
        }

        pItem = &m_Items[handle];
        pItem->Name = Name;
        strncpy(pItem->NameCopy, Name, 14);
        pItem->Flags = 0;
        pItem->uData = uData;
        pItem->uData2 = 0;
        pItem->NameCopy.ElementAt(14) = 0;
        pItem->SectionHandle = SectionHandle;
        m_Sections[SectionHandle].Items.AddTail(pItem);
    }

    return handle;
}

unsigned long EXDebugTree::AddItem(char* Name, char* SectionName, unsigned long uData)
{
    return AddItem(Name, SectionHandle(SectionName, 0), uData, DONT_ADD_DUPLICATES);
}

void EXDebugTree::DelItem(unsigned long ItemHandle)
{
    if (ItemHandle != 0 && ItemHandle < m_Items.Size())
    {
        DelItem(&m_Items[ItemHandle]);
    }
}

void EXDebugTree::DelSection(EXDebugTreeSection* pSect)
{
    EXDebugTreeSection* pChild;
    EXDebugTreeSection* pChildNext;
    EXDebugTreeItem* pItem;
    EXDebugTreeItem* pItemNext;

    for (pChild = (EXDebugTreeSection*)pSect->Children.Head(); pChild != NULL; pChild = pChildNext)
    {
        pChildNext = (EXDebugTreeSection*)pChild->Next();
        DelSection(pChild);
    }

    for (pItem = (EXDebugTreeItem*)pSect->Items.Head(); pItem != NULL; pItem = pItemNext)
    {
        pItemNext = (EXDebugTreeItem*)pItem->Next();
        DelItem(pItem);
    }

    m_Sections[pSect->ParentSectionHandle].Children.Remove(pSect);
    pSect->Flags = 0;
    pSect->NameCopy.ElementAt(0) = 0;
    pSect->Name = NULL;
    pSect->ParentSectionHandle = 0;
    pSect->Deleted = 1;
}

void EXDebugTree::DelItem(EXDebugTreeItem* pItem)
{
    m_Sections[pItem->SectionHandle].Items.Remove(pItem);
    pItem->Flags = 0;
    pItem->NameCopy.ElementAt(0) = 0;
    pItem->uData = 0;
    pItem->Name = NULL;
    pItem->SectionHandle = 0;
    pItem->Deleted = 1;
}

void EXDebugTree::RemapItems(long ItemOffset)
{
    EXDebugTreeSection* pSect;
    EXDebugTreeItem* pItem;
    EXDListItem* pTail;
    EXDListItem* pNext;
    u32 s;
    u32 i;

    for (s = 0; s < m_Sections.Size(); s++)
    {
        pSect = &m_Sections[s];
        if (!pSect->Deleted)
        {
            pTail = pSect->Items.Tail();
            if (pSect->Items.Head() != NULL)
            {
                pSect->Items.SetHead((EXDListItem*)((long)pSect->Items.Head() + ItemOffset));
            }
            if (pTail != NULL)
            {
                pSect->Items.SetTail((EXDListItem*)((long)pTail + ItemOffset));
            }
        }
    }

    for (i = 1; i < m_Items.Size(); i++)
    {
        pItem = &m_Items[i];
        if (!pItem->Deleted)
        {
            pNext = pItem->Next();
            if (pItem->Prev() != NULL)
            {
                pItem->SetPrev((EXDListItem*)((long)pItem->Prev() + ItemOffset));
            }
            if (pNext != NULL)
            {
                pItem->SetNext((EXDListItem*)((long)pNext + ItemOffset));
            }
        }
    }
}

EXInfoTree::EXInfoTree(unsigned long InitSections, unsigned long InitItems) : EXDebugTree(InitSections, InitItems)
{
}

unsigned long EXInfoTree::AddInfoItem(char* Name, unsigned long SectionHandle, unsigned long uData, Bool DrawName,
                                      ADD_DUPLICATE_ACTION AddDuplicateAction)
{
    unsigned long ItemHandle;

    ItemHandle = AddItem(Name, SectionHandle, DrawName ? 0x80000000 : 0, AddDuplicateAction);
    if (ItemHandle != 0)
    {
        m_Items[ItemHandle].uData2 = uData;
    }
    return ItemHandle;
}

unsigned long EXInfoTree::AddInfoItem(char* Name, unsigned long SectionHandle, char* pStr, Bool DrawName,
                                      ADD_DUPLICATE_ACTION AddDuplicateAction)
{
    unsigned long ItemHandle;
    EXDebugTreeItem* pItem;
    EXString* pItemStr;

    ItemHandle = AddItem(Name, SectionHandle, DrawName ? 0x80000002 : 2, AddDuplicateAction);
    if (ItemHandle != 0)
    {
        pItem = &m_Items[ItemHandle];
        pItemStr = (EXString*)pItem->uData2;
        if (pItemStr == NULL)
        {
            pItemStr = new EXString;
            pItem->uData2 = (u32)pItemStr;
        }
        *pItemStr = pStr;
    }
    return ItemHandle;
}

void EXInfoTree::DelItem(EXDebugTreeItem* pItem)
{
    EXString* pStr;

    if ((pItem->uData & 0x7fffffff) == 2)
    {
        pStr = (EXString*)pItem->uData2;
        if (pStr != NULL)
        {
            pStr->DeallocMem();
            EXFree(pStr);
        }
        pItem->uData2 = 0;
    }
    EXDebugTree::DelItem(pItem);
}

void EXInfoTree::Empty()
{
    u32 i;

    for (i = 1; i < m_Sections.Size(); i++)
    {
        if (!m_Sections[i].Deleted)
        {
            DelSection(i);
        }
    }
}
