#ifndef EXQUATERNION_H
#define EXQUATERNION_H

#include "types.h"

#include "EXVector.h"

struct quat_xyzw : /* 0x0 */ vec_xyzw
{ // 0x10
};

struct EXQuaternion : /* 0x0 */ quat_xyzw
{ // 0x10
    EXQuaternion() {}
    void SetIdentity()
    {
        vec128.z = 0.0f;
        vec128.y = 0.0f;
        vec128.x = 0.0f;
        vec128.w = 1.0f;
    }
    void Set(float fx, float fy, float fz, float fw)
    {
        vec128.x = fx;
        vec128.y = fy;
        vec128.z = fz;
        vec128.w = fw;
    }
    EXQuaternion(float fx, float fy, float fz, float fw)
    {
        vec128.x = fx;
        vec128.y = fy;
        vec128.z = fz;
        vec128.w = fw;
    }
    EXQuaternion& operator=(const EXQuaternion& q)
    {
        float fx = q.vec128.x;
        float fy = q.vec128.y;
        float fz = q.vec128.z;
        float fw = q.vec128.w;
        vec128.x = fx;
        vec128.y = fy;
        vec128.z = fz;
        vec128.w = fw;
        return *this;
    }
};

#endif // EXQUATERNION_H
