#ifndef EXMATHS_H
#define EXMATHS_H

#include "types.h"

struct vec_xyzw
{
    vec128_t vec128;

    // vec_xyzw& operator=();
    vec_xyzw();
    // vec_xyzw();
    vec128_t get128();
    // float operator float();
    void set();
    // void set();
    // void set();
    // void set();
    void set_zero();
    void set_zero1();
    vec_xyzw operator+();
    vec_xyzw operator-();
    vec_xyzw operator*();
    // vec_xyzw operator*();
    // vec_xyzw operator/();
    // void operator+=();
    // void operator-=();
    // void operator/=();
    // void operator*=();
    // void operator*=();
    // vec_xyzw operator-();
    // float& operator[]();
    // float operator[]();
    // float& operator()();
    // float operator()();
    void set_x();
    void set_y();
    void set_z();
    void set_w();
    void set_w_no_float_check();
    float get_x();
    float get_y();
    float get_z();
    float get_w();
    float get_w_no_float_check();
    void set_w0();
    void set_w1();
    vec_xyzw get_w0();
    vec_xyzw get_w1();
    // Bool operator==();
    // Bool operator!=();
    vec_xyzw Abs();
    vec_xyzw Sign();
    vec_xyzw Max();
    vec_xyzw Min();
    float Dot();
    float DotXYZ();
    vec_xyzw Cross();
    vec_xyzw Reflect();
    vec_xyzw Perp();
    vec_xyzw Parallel();
    float ScalarTripleProduct();
    float LengthSquared();
    float Length();
    float LengthXYZSquared();
    float LengthXYZ();
    vec_xyzw& Normalise();
    vec_xyzw& NormaliseNonZero();
    vec_xyzw& ReNormalise();
    vec_xyzw Interp();
    vec_xyzw InterpXYZ();
    u32 ClipFlag();
    Bool PointInTri();
    Bool PointInTriY();
    Bool PointInTriShadow();
    void Print();
    void Trace();
};

typedef vec_xyzw MXVector;

// should be in its own header file, but EXMaths has to be reconstructued since its not included in dwarf ig

// struct EXFixedArray<EXMaths::vec_xyzw, 3>
// { // 0x30
//     /* 0x00 */ vec_xyzw m_Data[3];

//     EXFixedArray<EXMaths::vec_xyzw, 3>& operator=();
//     EXFixedArray();
//     // EXFixedArray();
//     size_t Size();
//     size_t GetUpperBound();
//     MXVector& ElementAt();
//     MXVector GetAt();
//     void SetAt();
//     MXVector* GetData();
//     MXVector* GetData();
//     MXVector* operator EXMaths::vec_xyzw*();
//     MXVector* operator EXMaths::vec_xyzw*();
// };

#endif // EXMATHS_H
