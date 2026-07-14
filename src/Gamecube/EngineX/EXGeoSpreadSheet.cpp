#include "EngineX/EXGeoSpreadSheet.h"

// I'm also certain that this is not correct. I believe this should be some type of operator but who knows i guess.
// Check this function in the artist build to see the proper inline name and its contents.

static inline EXGeoDataSheet* EXRelPtrToDataSheet(const EXRelPtr<EXGeoDataSheet>* pRel)
{
    EXGeoDataSheet* pSheetData = NULL;
    s32 relOffset = pRel->m_rPtr.RelOffset;

    if (relOffset != 0)
    {
        pSheetData = (EXGeoDataSheet*)((u8*)pRel + relOffset);
    }

    return pSheetData;
}

u32 EXGeoSpreadSheet::DataSheetSize(u64 Sheet) const
{
    EXGeoDataSheet* pSheetData = EXRelPtrToDataSheet(&m_SheetData[(u32)Sheet]);
    return pSheetData->m_ElementCount;
}

void* EXGeoSpreadSheet::DataSheetData(u64 Sheet) const
{
    EXGeoDataSheet* pSheetData = EXRelPtrToDataSheet(&m_SheetData[(u32)Sheet]);
    return pSheetData->m_Elements;
}

// The Code below can technically match DataSheetSize without the inline
// but im unsure which is more correct for the GC version.

// EXGeoDataSheet* pSheetData = NULL;
// u8* pRel = (u8*)((u32)Sheet << 2);
// pRel += (u32)this;
// s32 relOffset = *(s32*)(pRel += 4);

// if (relOffset != 0)
// {
//     pSheetData = (EXGeoDataSheet*)(pRel + relOffset);
// }

// return pSheetData->m_ElementCount;
