#ifndef EXVECTOR_H
#define EXVECTOR_H

#include "types.h"

#include "EXMaths.h"

template <typename T> struct vec_template;

struct VEC_XYZW
{
    /* 0x0 */ float x;
    /* 0x4 */ float y;
    /* 0x8 */ float z;
    /* 0xc */ float w;
};

typedef long long unsigned int vec128_t;

struct x_base
{
    static unsigned int broadcast_field;
    static unsigned int valid_fields;
    /* 0x0 */ vec128_t vec128;
};

struct y_base
{
    static unsigned int broadcast_field;
    static unsigned int valid_fields;
    /* 0x0 */ vec128_t vec128;
};

struct z_base
{
    static unsigned int broadcast_field;
    static unsigned int valid_fields;
    /* 0x0 */ vec128_t vec128;
};

struct w_base
{
    static unsigned int broadcast_field;
    static unsigned int valid_fields;
    /* 0x0 */ vec128_t vec128;
};

struct xyzw_base
{
    static unsigned int broadcast_field;
    static unsigned int valid_fields;
    /* 0x0 */ vec128_t vec128;
};

struct vec_template<EXMaths::x_base> : x_base
{
    // vec_template<EXMaths::x_base>& operator=();
    vec_template();
    // vec_template();
    vec128_t get128();
    void set();
    // void set();
    void set_zero();
};

struct vec_x : /* 0x0 */ vec_template<EXMaths::x_base>
{ // 0x10
};

struct vec_template<EXMaths::y_base> : y_base
{ // 0x10
    // vec_template<EXMaths::y_base>& operator=();
    // vec_template();
    vec_template();
    vec128_t get128();
    // void set();
    void set();
    void set_zero();
};

struct vec_y : /* 0x0 */ vec_template<EXMaths::y_base>
{ // 0x10
};

struct vec_template<EXMaths::z_base> : z_base
{ // 0x10
    // vec_template<EXMaths::z_base>& operator=();
    // vec_template();
    vec_template();
    vec128_t get128();
    // void set();
    void set();
    void set_zero();
};

struct vec_z : vec_template<EXMaths::z_base>
{ // 0x10
};

struct vec_template<EXMaths::w_base> : w_base
{ // 0x10
    // vec_template<EXMaths::w_base>& operator=();
    // vec_template();
    vec_template();
    vec128_t get128();
    // void set();
    void set();
    void set_zero();
};

struct vec_w : /* 0x0 */ vec_template<EXMaths::w_base>
{ // 0x10
};

struct vec_xyzw
{ // 0x10
    /* 0x0 */ vec128_t vec128;

    // vec_xyzw& operator=();
    // vec_xyzw();
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
    float& operator()();
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

struct vec_template<EXMaths::xyzw_base> : /* 0x0 */ xyzw_base
{ // 0x10
    // vec_template<EXMaths::xyzw_base>& operator=();
    vec_template();
    // vec_template();
    vec128_t get128();
    void set();
    // void set();
    void set_zero();
};

typedef vec_xyzw MXVector;
typedef u8 EXRotOrder;

struct EXVector2
{ // 0x8
    /* 0x0 */ float x;
    /* 0x4 */ float y;

    EXVector2();
    // EXVector2();
    // EXVector2();
    // EXVector2& operator=();
    // EXVector2& operator+=();
    // EXVector2& operator-=();
    // EXVector2& operator*=();
    // EXVector2& operator/=();
    void Set();
    void SetZero();
    float Normalise();
    EXVector2 UnitVector();
    float Length();
    float LengthSquared();
};

struct EXVector3
{ // 0xc
    /* 0x0 */ float x;
    /* 0x4 */ float y;
    /* 0x8 */ float z;

    EXVector3();
    // EXVector3();
    // EXVector3();
    // EXVector3& operator=();
    // EXVector3& operator+=();
    // EXVector3& operator-=();
    // EXVector3& operator*=();
    // EXVector3& operator/=();
    void Set();
    void SetZero();
    float Normalise();
    EXVector3 UnitVector();
    float Length();
    float LengthSquared();
};

struct EXVector
{
    union
    {
        struct
        {
            /* 0x0 */ float x;
            /* 0x4 */ float y;
            /* 0x8 */ float z;
            /* 0xc */ float w;
        };
        MXVector xyzw;
    };

    EXVector();
    // EXVector();
    // EXVector();
    // EXVector();
    // EXVector();
    // EXVector& operator=();
    // MXVector operator EXMaths::vec_xyzw();
    // EXVector& operator+=();
    // EXVector& operator-=();
    // EXVector& operator*=();
    // EXVector& operator/=();
    // EXVector& operator*=();
    // EXVector& operator*=();
    // EXVector operator-();
    // float& operator[]();
    // float operator[]();
    // float& operator()();
    // float operator()();
    float Dot();
    float DotXYZ();
    EXVector Cross();
    void set_x();
    void set_y();
    void set_z();
    void set_w();
    void set_w_no_float_check();
    void Set();
    // void Set();
    void SetZero();
    float get_x();
    float get_y();
    float get_z();
    float get_w();
    float get_w_no_float_check();
    float Length();
    float LengthSquared();
    float LengthXYZ();
    float LengthXYZSquared();
    float LengthXY();
    float LengthXYSquared();
    float LengthXZ();
    float LengthXZSquared();
    float LengthYZ();
    float LengthYZSquared();
    EXVector UnitVectorXYZ();
    EXVector UnitVector();
    float Normalise();
    static void GenerateOrthonormalBasis(/* parameters unknown */);
    EXVector& ApplyXForm();
    u32 ClipFlag();
    void Print();
    void Trace();
};

#endif // EXVECTOR_H
