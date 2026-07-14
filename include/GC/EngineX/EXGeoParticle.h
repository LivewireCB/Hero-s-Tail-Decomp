#ifndef EXGEOPARTICLE_H
#define EXGEOPARTICLE_H

#include "types.h"

#include "EXBounds.h"
#include "EXGeoCommon.h"
#include "EXHashcode.h"
#include "EXRelPtr.h"

// warning: multiple differing types with the same name (enum constant not equal)
// enum Type
// {
// None = 0,
// XAxis = 1,
// YAxis = 2,
// ZAxis = 4
// };

// warning: multiple differing types with the same name (enum constant not equal)
enum Type
{
    Face = 0,
    Vertex = 1,
    Total = 2
};

struct EXGeoParticleLife
{ // 0x10
    /* 0x0 */ u32 m_Channel;
    /* 0x4 */ float m_Time;
    /* 0x8 */ float m_Value;
    /* 0xc */ float m_Step;
};

struct EXGeoParticle : /* 0x000 */ EXGeoCommonObject
{ // 0x110
    static EXRuntimeClass classEXGeoParticle;
    /* 0x004 */ u32 m_Type;
    /* 0x008 */ EXHashCode m_EmitterRef;
    /* 0x00c */ u32 m_EmitterFlags;
    /* 0x010 */ EXBoundsBox m_BoundsBox;
    /* 0x030 */ u16 m_SystemFlags;
    /* 0x032 */ u16 m_UserFlags;
    /* 0x034 */ float m_StartFrame;
    /* 0x038 */ u32 m_ReducedParticles;
    /* 0x03c */ float m_Fps;
    /* 0x040 */ float m_ZSortOffset;
    /* 0x044 */ u8 m_RenderOrder;
    /* 0x045 */ u8 m_Pad0;
    /* 0x046 */ u16 m_NewFlags;
    /* 0x048 */ EXVector3 m_Position;
    /* 0x054 */ EXVector3 m_PositionVar;
    /* 0x060 */ EXVector3 m_vSize;
    /* 0x06c */ EXVector3 m_vSizeVar;
    /* 0x078 */ EXVector3 m_Gravity;
    /* 0x084 */ EXVector3 m_Friction;
    /* 0x090 */ float m_Pitch;
    /* 0x094 */ float m_PitchVar;
    /* 0x098 */ float m_Yaw;
    /* 0x09c */ float m_YawVar;
    /* 0x0a0 */ float m_InitialVelocity;
    /* 0x0a4 */ float m_InitialVelocityVar;
    /* 0x0a8 */ float m_Life;
    /* 0x0ac */ float m_LifeVar;
    /* 0x0b0 */ float m_NearDistance;
    /* 0x0b4 */ float m_NearEmitsPerFrame;
    /* 0x0b8 */ u32 m_NearParticleLimit;
    /* 0x0bc */ float m_FarDistance;
    /* 0x0c0 */ float m_FarEmitsPerFrame;
    /* 0x0c4 */ u32 m_FarParticleLimit;
    /* 0x0c8 */ u32 m_UseMipSystem;
    /* 0x0cc */ u32 m_TextureMode;
    /* 0x0d0 */ u32 m_ColourMode;
    /* 0x0d4 */ u32 m_ColourVar;
    /* 0x0d8 */ u32 m_ViewportAlign;
    /* 0x0dc */ Type m_EmissionMode;
    /* 0x0e0 */ u16 m_EmitNormal;
    /* 0x0e2 */ u16 m_Local;
    /* 0x0e4 */ EXRelPtr24<int> m_rpValuesOffset;
    /* 0x0e8 */ EXHashCode m_TypeHashRef;
    /* 0x0ec */ u32 m_NumTexturesUsed;
    /* 0x0f0 */ EXRelPtr<unsigned int> m_rpTextureHashOffset;
    /* 0x0f4 */ u32 m_NumEntitysUsed;
    /* 0x0f8 */ EXRelPtr<unsigned int> m_rpEntityHashOffset;
    /* 0x0fc */ EXGeoParticleLife m_ParticleLife[1];

    // EXGeoParticle& operator=();
    // EXGeoParticle();
    // EXGeoParticle();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    void Create();
    static void _GCO_N_EXGeoParticle(/* parameters unknown */);
    s32 Value();
    EXHashCode GetTextureHash();
    EXHashCode GetEntityHash();
    s32 GetNumTexturesUsed();
    float GetNearEmitsPerFrame();
    float GetNearDistance();
    u32 GetNearParticleLimit();
    float GetFarEmitsPerFrame();
    float GetFarDistance();
    u32 GetFarParticleLimit();
    float GetFps();
    u32 GetLocal();
    float StartFrame();
    EXHashCode TypeHashRef();
    /* vtable[5] */ virtual EXBoundsBox& GetBoundsBox();
    EXBoundsBox& BoundsBox();
};

#endif // EXGEOPARTICLE_H
