#ifndef EXGEOSPREADSHEET_H
#define EXGEOSPREADSHEET_H

#include "types.h"

struct EXGeoTextSection
{
    u32 m_HashCode;
    u32 m_RefPtrIndex;
};

struct EXGeoDataSheet
{
    u32 m_ElementCount;
    unsigned int m_Elements[1];
};

// struct EXRelPtr<EXGeoDataSheet>
// {
// EXRELOFFSET32 m_rPtr;

// EXRelPtr<EXGeoDataSheet>& operator=();
// EXRelPtr();
// EXRelPtr();
// EXRELOFFSET32& RelPtr();
// EXGeoDataSheet* operator EXGeoDataSheet*();
// };

struct EXGeoSpreadSheet
{
    // union
    // {
    //     struct
    //     {
    //         u32 m_SectionCount;
    //         EXGeoTextSection m_Section[1];
    //     };
    //     struct
    //     {
    //         u32 m_SheetCount;
    //         // EXRelPtr<EXGeoDataSheet> m_SheetData[1];
    //     };
    // };

    // EXGeoSpreadSheet& operator=();
    EXGeoSpreadSheet();
    // EXGeoSpreadSheet();
    // EXGeoTextItem* FindTextItem();
    u32 DataSheetCount();
    u32 DataSheetSize(u64) const;
    void* DataSheetData(u64) const;
};

#endif // EXGEOSPREADSHEET_H
