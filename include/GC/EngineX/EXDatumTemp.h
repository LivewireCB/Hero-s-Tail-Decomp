#ifndef EXDATUMTEMP_H
#define EXDATUMTEMP_H

#include "types.h"

#include "EXDataArray.h"
#include "EXFixedArray.h"
#include "EXQuaternion.h"
#include "EXVector.h"

struct EXDatumTemp
{ // 0x30
    /* 0x00 */ EXVector vctPos;
    /* 0x10 */ EXQuaternion vctDir;
    /* 0x20 */ EXFixedArray<float, 3> Extents;
    /* 0x2c */ u16 Flags;
    /* 0x2e */ u8 FrameFlags;
    /* 0x2f */ u8 Type;

    EXDatumTemp()
    {
    }
    EXDatumTemp& operator=(const EXDatumTemp& d)
    {
        vctPos = d.vctPos;
        vctDir = d.vctDir;
        Extents = d.Extents;
        Flags = d.Flags;
        FrameFlags = d.FrameFlags;
        Type = d.Type;
        return *this;
    }
};

struct EXDatumTempArray : /* 0x0 */ EXDataArray<EXDatumTemp, EXDatumTemp&>
{ // 0x10
};

#endif // EXDATUMTEMP_H
