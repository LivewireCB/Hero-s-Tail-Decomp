#ifndef EXHASHCODE_H
#define EXHASHCODE_H

#include "types.h"

// Todo: Investigate the proper type for EXHashCode
// Dwarf shows u32, but symbols show u64???

// typedef u32 EXHashCode;
typedef u64 EXHashCode;

struct EXHashCodeFile
{ // 0x1
    // EXHashCodeFile& operator=();
    EXHashCodeFile();
    // EXHashCodeFile();
    static Bool LoadFile(/* parameters unknown */);
    static int QSortFn_SortByValue(/* parameters unknown */);
    static char* Debug_HashCodeName(EXHashCode HashRef);
    static EXHashCode Debug_HashRef(/* parameters unknown */);
};

struct EXHT // No Dwarf info available
{
    static char* HashCodeNotFoundMessage;
};

struct EXBit128
{ // 0x10
protected:
    /* 0x0 */ u128 m_Data;

public:
    // EXBit128& operator=();
    EXBit128();
    // EXBit128();
    void Set();
    // void Set();
    // void Set();
    void Clr();
    // void Set();
    void SetAll();
    void ClrAll();
    u32 IsSet();
    // u32 IsSet();
    u32 IsAnySet();
    // EXBit128 operator|=();
    // EXBit128 operator&=();
    // EXBit128 operator^=();
};

#endif // EXHASHCODE_H
