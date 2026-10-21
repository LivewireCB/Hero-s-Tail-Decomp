#ifndef EXITEMANIMATOR_MAP_H
#define EXITEMANIMATOR_MAP_H

#include "types.h"

struct EXMapOn
{ // 0x2
protected:
    /* 0x0 */ s16 m_MapOn;

public:
    // EXMapOn();
    // EXMapOn();
    // EXMapOn();
    // EXMapOn();
    void Set();
    Bool IsValid();
    u8 Zone();
    s8 Map();
    s16 SetData();
    s16 Data();
    // EXMapOn operator=();
};

#endif // EXITEMANIMATOR_MAP_H
