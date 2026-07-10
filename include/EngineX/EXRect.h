#ifndef EXRECT_H
#define EXRECT_H

#include "types.h"

#include "EXPoint.h"

struct EXRECT
{
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 w;
    /* 0xc */ s32 h;
};

struct EXRECTF
{
    /* 0x0 */ float x;
    /* 0x4 */ float y;
    /* 0x8 */ float w;
    /* 0xc */ float h;
};

struct EXRect : /* 0x0 */ EXRECT
{ // 0x10
    EXRect();
    // EXRect();
    // EXRect();
    // EXRect();
    // EXRect(EXRect*, int, void);
    // EXRect& operator=();
    // EXRect& operator=();
    void Set();
    // void Set();
    int Width();
    int Height();
    Bool IsEmpty();
    Bool IsNull();
    EXPoint TopLeft();
    EXPoint TopRight();
    EXPoint BottomLeft();
    EXPoint BottomRight();
    EXPoint Centre();
    Bool ContainsPoint();
    void Inflate();
    void Deflate();
    void Offset();
    // void Offset();
    // EXRECT* operator ex::EXRECT*();
};

struct EXRectf : /* 0x0 */ EXRECTF
{ // 0x10
    EXRectf();
    // EXRectf();
    // EXRectf();
    // EXRectf();
    // EXRectf(EXRectf*, int, void);
    // EXRectf& operator=();
    // EXRectf& operator=();
    void Set();
    // void Set();
    float Width();
    float Height();
    Bool IsEmpty();
    Bool IsNull();
    EXPointf TopLeft();
    EXPointf TopRight();
    EXPointf BottomLeft();
    EXPointf BottomRight();
    EXPointf Centre();
    Bool ContainsPoint();
    void Inflate();
    void Deflate();
    void Offset();
    // void Offset();
    // EXRectf* operator EXRectf*();
};

#endif // EXRECT_H
