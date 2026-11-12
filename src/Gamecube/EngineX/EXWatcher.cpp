#include "EngineX/EXWatcher.h"

#include "EngineX/EXStateSaver.h"
#include "EngineX/EXString.h"

EXWatcher* EXWatcher::m_pWatcher;

EXWatcher::EXWatcher() : EXDebugTree(200, 200)
{
    m_WatchItems.AllocMem(200);
    m_WatchItems.SetGrowBy(200);
}

EXWatcher::~EXWatcher()
{
}

Bool EXWatcher::Init(EXWatcher* pWatcher)
{
    m_pWatcher = pWatcher;
    pWatcher->AddSectionFunc("-Engine-", 0);
    pWatcher->AddSectionFunc("-Game-", 0);
    return 1;
}

void EXWatcher::Shutdown()
{
    if (m_pWatcher != NULL)
    {
        delete m_pWatcher;
    }
}

unsigned long EXWatcher::AddSectionFunc(char* Name, unsigned long ParentSectionHandle)
{
    unsigned long SectionHandle;
    EXDebugTreeSection* pSect;

    SectionHandle = EXDebugTree::AddSection(Name, ParentSectionHandle, ADD_DUPLICATES);
    if (SectionHandle == 0)
    {
        return 0;
    }

    pSect = &m_Sections[SectionHandle];
    EXStateSaver state("WatcherSections");
    EXString ItemName(pSect->NameCopy);
    pSect->Open = state.Restore(ItemName + "-Open", 0);
    return SectionHandle;
}

unsigned long EXWatcher::AddItem(char* Name, unsigned long SectionHandle, EXWATCH::DataType Type, void* pAddr)
{
    unsigned long ItemHandle;
    EXWatchItem* pWatch;

    ItemHandle = EXDebugTree::AddItem(Name, SectionHandle, 0, DONT_ADD_DUPLICATES);
    if (ItemHandle == 0)
    {
        return 0;
    }
    if (ItemHandle >= m_WatchItems.Size())
    {
        m_WatchItems.SetSize(ItemHandle + 1, -1);
    }
    pWatch = &m_WatchItems[ItemHandle];
    m_Items[ItemHandle].uData = ItemHandle;
    m_Items[ItemHandle].uData2 = (u32)pAddr;
    pWatch->DataType = Type;
    return ItemHandle;
}

void EXWatcher::DelItem(unsigned long ItemHandle)
{
    m_WatchItems[ItemHandle].DataType = EXWATCH::DTnone;
    m_Items[ItemHandle].uData2 = 0;
    EXDebugTree::DelItem(ItemHandle);
}

void EXWatcher::EnableItemEdit(unsigned long ItemHandle, Bool Persistent)
{
    EXDebugTreeItem* pItem;
    EXWatchItem* pWatch;

    if (ItemHandle != 0)
    {
        pItem = &m_Items[ItemHandle];
        pItem->UserFlags |= 1;
        pWatch = &m_WatchItems[ItemHandle];
        pWatch->MinVal.i = 0;
        pWatch->MaxVal.i = 0;
        pWatch->Step.i = 0;
        pItem->UserFlags |= Persistent ? 2 : 0;
        if (Persistent)
        {
            RestoreItemValue(ItemHandle);
        }
    }
}

void EXWatcher::EnableItemEdit(unsigned long ItemHandle, ex::EXVar32& Min, ex::EXVar32& Max, ex::EXVar32& Step,
                               Bool Persistent)
{
    EXDebugTreeItem* pItem;
    EXWatchItem* pWatch;

    if (ItemHandle != 0)
    {
        pItem = &m_Items[ItemHandle];
        pItem->UserFlags |= 1;
        pWatch = &m_WatchItems[ItemHandle];
        pWatch->MinVal = Min;
        pWatch->MaxVal = Max;
        pWatch->Step = Step;
        pItem->UserFlags |= Persistent ? 2 : 0;
        if (Persistent)
        {
            RestoreItemValue(ItemHandle);
        }
    }
}

void EXWatcher::EnableItemEdit(unsigned long ItemHandle, unsigned long Min, unsigned long Max, unsigned long Step,
                               Bool Persistent)
{
    ex::EXVar32 MinVar;
    ex::EXVar32 MaxVar;
    ex::EXVar32 StepVar;

    MinVar.h = Min;
    MaxVar.h = Max;
    StepVar.h = Step;
    EnableItemEdit(ItemHandle, MinVar, MaxVar, StepVar, Persistent);
}

void EXWatcher::RestoreItemValue(unsigned long ItemHandle)
{
    EXDebugTreeItem* pItem;
    EXWatchItem* pWatch;

    pItem = &m_Items[ItemHandle];
    pWatch = &m_WatchItems[ItemHandle];
    EXStateSaver state("WatcherItems");
    EXString ItemName(m_Sections[pItem->SectionHandle].NameCopy);
    ItemName += "-";
    ItemName += pItem->NameCopy;

    switch (pWatch->DataType)
    {
    case EXWATCH::DTu8:
    case EXWATCH::DTs8:
        *(u8*)pItem->uData2 = state.Restore(ItemName, *(u8*)pItem->uData2);
        break;
    case EXWATCH::DTu16:
    case EXWATCH::DTs16:
        *(u16*)pItem->uData2 = state.Restore(ItemName, *(u16*)pItem->uData2);
        break;
    case EXWATCH::DTu32:
    case EXWATCH::DTs32:
    case EXWATCH::DTfloat:
    case EXWATCH::DTrgba:
        *(u32*)pItem->uData2 = state.Restore(ItemName, *(u32*)pItem->uData2);
        break;
    case EXWATCH::DTbool:
        *(Bool*)pItem->uData2 = state.Restore(ItemName, *(Bool*)pItem->uData2);
        break;
    }
}
