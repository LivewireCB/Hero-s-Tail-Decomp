#ifndef EXGEOFACE_H
#define EXGEOFACE_H

#include "types.h"

#include "EXGeoCommon.h"
#include "EXHashcode.h"
#include "EXVector.h"
#include "EXRGB.h"

struct GEOFACE_VTX
{ // 0x20
    /* 0x00 */ MXVector v;
    /* 0x10 */ union
    { // 0x10
        /* 0x10 */ MXVector uvc;
        /* 0x10 */ struct
        { // 0x10
            /* 0x10 */ float tu;
            /* 0x14 */ float tv;
            /* 0x18 */ u32 Pad;
            /* 0x1c */ XRGBA rgba;
        };
    };
};

struct EXGeoFace : /* 0x00 */ EXGeoCommonObject
{ // 0x90
    static EXRuntimeClass classEXGeoFace;
    /* 0x04 */ EXHashCode m_TextureRef;
    /* 0x08 */ u32 m_VertexCount;
    /* 0x0c */ u32 m_Flags;
    /* 0x10 */ GEOFACE_VTX m_vtx[4];

    // EXGeoFace& operator=();
    EXGeoFace();
    // EXGeoFace();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    void Create();
    static void _GCO_N_EXGeoFace(/* parameters unknown */);
    /* vtable[4] */ virtual void Draw(EXGDiData* pGDiData, unsigned long Flags);
    u32 VertexCount();
    EXHashCode TextureRef();
    GEOFACE_VTX* Vtx();
};

#endif // EXGEOFACE_H
