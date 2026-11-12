#ifndef EXWATCHER_H
#define EXWATCHER_H

#include "types.h"
#include "EngineX/EXDataArray.h"
#include "EngineX/EXDebugTree.h"
#include "EngineX/EXMemoryManager.h"

namespace ex
{
union EXVar32
{
    float f;
    s32 i;
    u32 h;
};
} // namespace ex

namespace EXWATCH
{
enum DataType
{
    DTnone = 0,
    DTu8 = 1,
    DTu16 = 2,
    DTu32 = 3,
    DTs8 = 4,
    DTs16 = 5,
    DTs32 = 6,
    DTfloat = 7,
    DTbool = 8,
    DTrgba = 9
};
} // namespace EXWATCH

struct EXWatchItem
{ // 0x10
    /* 0x0 */ EXWATCH::DataType DataType;
    /* 0x4 */ ex::EXVar32 MinVal;
    /* 0x8 */ ex::EXVar32 MaxVal;
    /* 0xc */ ex::EXVar32 Step;
};

struct EXDataArray<EXWatchItem, EXWatchItem&>
{ // 0x10
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ EXWatchItem* m_pData;

    EXDataArray()
    {
        Init(0, -1);
    }
    ~EXDataArray()
    {
        EXFree(m_pData);
    }
    void Init(int iSize, int iGrowBy);
    int Size()
    {
        return m_iSize;
    }
    void SetSize(int iSize, int nGrowBy);
    void SetGrowBy(int iGrowBy);
    void AllocMem(int iSize);
    EXWatchItem& ElementAt(int iPos)
    {
        return m_pData[iPos];
    }
    EXWatchItem& operator[](int iPos)
    {
        return m_pData[iPos];
    }
    void GrowArray(int iReqNewSize);
};

struct EXWatcher : EXDebugTree
{ // 0x3c
protected:
    static EXWatcher* m_pWatcher;
    /* 0x2c */ EXDataArray<EXWatchItem, EXWatchItem&> m_WatchItems;

public:
    EXWatcher();
    virtual ~EXWatcher();

protected:
    unsigned long AddSectionFunc(char* Name, unsigned long ParentSectionHandle);

public:
    static Bool Init(EXWatcher* pWatcher);
    static void Shutdown();
    unsigned long AddItem(char* Name, unsigned long SectionHandle, EXWATCH::DataType Type, void* pAddr);
    virtual void DelItem(unsigned long ItemHandle);
    void EnableItemEdit(unsigned long ItemHandle, Bool Persistent);
    void EnableItemEdit(unsigned long ItemHandle, ex::EXVar32& Min, ex::EXVar32& Max, ex::EXVar32& Step,
                        Bool Persistent);
    void EnableItemEdit(unsigned long ItemHandle, unsigned long Min, unsigned long Max, unsigned long Step,
                        Bool Persistent);

protected:
    void RestoreItemValue(unsigned long ItemHandle);
};

#endif // EXWATCHER_H
