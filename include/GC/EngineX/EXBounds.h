#ifndef EXBOUNDS_H
#define EXBOUNDS_H

#include "types.h"

#include "EXVector.h"

struct MXBoundsBox
{ // 0x20
protected:
    /* 0x00 */ vec_xyzw m_vct[2];

public:
    // MXBoundsBox& operator=();
    MXBoundsBox();
    // MXBoundsBox();
    MXVector vctMin();
    MXVector vctMax();
    void _ApplyXForm();
    Bool _Intersect();
    // Bool _Intersect();
    // Bool _Intersect();
};

struct EXBoundsBox3
{ // 0x18
protected:
    /* 0x00 */ EXVector3 m_vct[2];

public:
    // EXBoundsBox3& operator=();
    EXBoundsBox3();
    // EXBoundsBox3();
    EXVector3& vctMin();
    EXVector3& vctMax();
    void Set();
    void SetMin();
    void SetMax();
    Bool Intersect();
    // Bool Intersect();
    // Bool Intersect();
};

struct EXBoundsBox : /* 0x00 */ MXBoundsBox
{ // 0x20
    // EXBoundsBox& operator=();
    EXBoundsBox();
    // EXBoundsBox();
    // float* operator float*();
    void Set();
    // void Set();
    // void Set();
    // void Set();
    void SetMin();
    void SetMax();
    void SetZero();
    void SetMaxRange();
    void Accumulate();
    void ApplyXForm();
    Bool Intersect();
    // Bool Intersect();
    // Bool Intersect();
    float CentreAndRadius();
    float CentreAndRadiusSquared();
    float Volume();
};

struct EXBoundsSphere : /* 0x0 */ vec_xyzw
{ // 0x10
    // EXBoundsSphere& operator=();
    EXBoundsSphere();
    // EXBoundsSphere();
    void SetCentre();
    // void SetCentre();
    void SetRadius();
    // MXVector Centre();
    EXVector3& Centre3();
    // void Centre();
    float Radius();
};

#endif // EXBOUNDS_H
