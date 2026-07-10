#ifndef EXMATRIX_H
#define EXMATRIX_H

#include "types.h"

#include "EXVector.h"

struct mat_44
{ // 0x40
    /* 0x00 */ vec_xyzw row0;
    /* 0x10 */ vec_xyzw row1;
    /* 0x20 */ vec_xyzw row2;
    /* 0x30 */ vec_xyzw row3;

    // mat_44& operator=();
    // mat_44();
    // mat_44();
    void set_zero();
    void set_identity();
    void set_scale();
    void set_rotate_x();
    void set_rotate_y();
    void set_rotate_z();
    void set_rotate_xyz();
    void set_rotate_xzy();
    void set_rotate_zxy();
    void set_rotate_zyx();
    void set_rotate_yzx();
    void set_rotate_yxz();
    void set_rotate_axis();
    void set_rotate_quat();
    void set_rotate();
    vec_xyzw operator*();
    // mat_44 operator*();
    mat_44 operator+();
    mat_44 operator-();
    // mat_44 operator*();
    // mat_44 operator-();
    mat_44 transpose();
    mat_44 transpose3();
    mat_44 inverse();
    mat_44 inverse3();
    mat_44 inverse3trans();
    mat_44 fastinverse();
    // void operator+=();
    // void operator-=();
    void set_row0();
    void set_row1();
    void set_row2();
    void set_row3();
    vec_xyzw get_row0();
    vec_xyzw get_row1();
    vec_xyzw get_row2();
    vec_xyzw get_row3();
    void set_column0();
    void set_column1();
    void set_column2();
    void set_column3();
    vec_xyzw get_column0();
    vec_xyzw get_column1();
    vec_xyzw get_column2();
    vec_xyzw get_column3();
    void Print();
    void Trace();
};

typedef mat_44 MXMatrix44;

struct EXMatrix
{
    /* 0x00 */ union
    { // 0x40
        /* 0x00 */ MXMatrix44 m;
        /* 0x00 */ vec_xyzw r[4];
        /* 0x00 */ float f[4][4];
    };

    EXMatrix();
    // EXMatrix();
    // EXMatrix();
    // EXMatrix();
    void Set();
    // MXMatrix44& operator EXMaths::mat_44&();
    void SetTranslation();
    EXVector GetTranslation();
    float& operator()();
    // float operator()();
    // EXMatrix& operator=();
    // EXMatrix& operator+=();
    // EXMatrix& operator-=();
    // EXMatrix& operator*=();
    // EXMatrix& operator*=();
    // EXMatrix& operator/=();
    EXMatrix operator*();
    EXMatrix operator-();
    EXMatrix operator+();
    // EXMatrix operator*();
    // EXMatrix operator/();
    EXMatrix& SetFromRotX();
    EXMatrix& SetFromRotY();
    EXMatrix& SetFromRotZ();
    static EXMatrix RotMatrixX(/* parameters unknown */);
    static EXMatrix RotMatrixY(/* parameters unknown */);
    static EXMatrix RotMatrixZ(/* parameters unknown */);
    void SetIdentity();
    void SetZero();
    void SetScale();
    void SetTranslate();
    void SetRotMatrix();
    static EXMatrix MakeIdentity(/* parameters unknown */);
    EXMatrix Transpose();
    EXMatrix Inverse();
    EXMatrix Inverse3();
    EXMatrix FastInverse();
    void Scale();
    void SetRotationXYZ();
    void SetRotationXZY();
    void SetRotationYXZ();
    void SetRotationYZX();
    void SetRotationZXY();
    void SetRotationZYX();
    void SetRotation();
    // void SetRotation();
    // void SetRotation();
    // void SetRotation();
    // void SetRotation();
    void GetRotationXYZ();
    void GetRotationXZY();
    void GetRotationYXZ();
    void GetRotationYZX();
    void GetRotationZXY();
    void GetRotationZYX();
    void GetRotation();
    // void GetRotation();
    // void GetRotation();
    void GetRotationTo();
    EXVector GetDir();
    EXVector GetUp();
    EXVector GetNorm();
    void SetDir();
    void SetUp();
    void SetNorm();
    void AlignToPlane();
    void AlignToDir();
    void AlignToUp();
    void LookAt();
    void GetScale();
    void Decompose();
    float Determinant();
    void Print();
    void Trace();

private:
    float _det2x2();
    float _det3x3();
};

struct EXScaleMatrix : EXMatrix
{
};

#endif // EXMATRIX_H
