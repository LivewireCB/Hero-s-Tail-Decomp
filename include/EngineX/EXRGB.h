#ifndef EXRGB_H
#define EXRGB_H

#include <types.h>

struct XRGBA
{ // 0x4
    /* 0x0 */ union
    { // 0x4
        /* 0x0 */ u32 rgba;
        /* 0x0 */ struct
        { // 0x4
            /* 0x0 */ u8 r;
            /* 0x1 */ u8 g;
            /* 0x2 */ u8 b;
            /* 0x3 */ u8 a;
        };
    };
};

struct RGBA : /* 0x0 */ XRGBA
{ // 0x4
    // RGBA& operator=();
    RGBA();
    // RGBA();
    // RGBA();
    // RGBA();
    void Set();
    u32 argb();
    // u32 operator unsigned int();
};

#endif
