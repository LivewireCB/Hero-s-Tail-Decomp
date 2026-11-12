#ifndef EXPARTICLESYS_H
#define EXPARTICLESYS_H

#include "types.h"

#include "EXEffectsSys.h"
#include "EXMatrix.h"
#include "EXVector.h"

struct EXGDiDataArray;

struct CParticleMip
{ // 0xc
    /* 0x0 */ float m_Distance;
    /* 0x4 */ float m_EmitsPerFrame;
    /* 0x8 */ u32 m_ParticleLimit;
};

// Same member order as the PS2 build, but EXVector is only 8-aligned on GC so everything sits at different offsets.
// Only the members up to m_bDelaySystem are reconstructed so far.
struct EXBaseParticleSys : /* 0x00 */ EXEffectsSys
{
    static EXRuntimeClass classEXBaseParticleSys;
    /* 0x058 */ EXMatrix* m_pViewToScreenCoords;
    /* 0x05c */ EXMatrix* m_pWorldToView;
    /* 0x060 */ u32 (*m_pParticlePosCallback)(/* parameters unknown */);
    /* 0x064 */ EXGDiDataArray* m_pGDiArray;
    /* 0x068 */ u32 m_ParticleType;
    /* 0x06c */ EXGeoComplexRefObject m_GeoRefEmitter;
    /* 0x07c */ u16 m_SystemFlags;
    /* 0x07e */ u16 m_UserFlags;
    /* 0x080 */ EXVector m_Position;
    /* 0x090 */ EXVector m_PositionVar;
    /* 0x0a0 */ EXVector m_FadeScale;
    /* 0x0b0 */ EXVector m_vSize;
    /* 0x0c0 */ EXVector m_vSizeVar;
    /* 0x0d0 */ EXVector m_Gravity;
    /* 0x0e0 */ EXVector m_Friction;
    /* 0x0f0 */ EXVector m_LastEmitPos;
    /* 0x100 */ EXVector m_LastEmitRot;
    /* 0x110 */ EXVector m_EmitVelModifier;
    /* 0x120 */ EXVector m_GlobalScale;
    /* 0x130 */ EXVector m_ParticleColourHack;
    /* 0x140 */ s32 m_LastGetParticleIndex;
    /* 0x144 */ float m_Fps;
    /* 0x148 */ float m_RecipFps;
    /* 0x14c */ u32 m_Alignment;
    /* 0x150 */ float m_Pitch;
    /* 0x154 */ float m_PitchVar;
    /* 0x158 */ float m_Yaw;
    /* 0x15c */ float m_YawVar;
    /* 0x160 */ float m_InitialVelocity;
    /* 0x164 */ float m_InitialVelocityVar;
    /* 0x168 */ float m_InitialVelocityDelta;
    /* 0x16c */ float m_EmitCounter;
    /* 0x170 */ float m_Life;
    /* 0x174 */ float m_LifeVar;
    /* 0x178 */ float m_LifeStep;
    /* 0x17c */ float m_TimeElapsedColour;
    /* 0x180 */ float m_LODEmitsPerFrame;
    /* 0x184 */ float m_FrameMult;
    /* 0x188 */ s32 m_LODParticleLimit;
    /* 0x18c */ s32 m_SysLifeInc;
    /* 0x190 */ s32 m_LastTexture;
    /* 0x194 */ s32 m_LastTextureInc;
    /* 0x198 */ CParticleMip m_ParticleMips[2];
    /* 0x1b0 */ void* m_pParticles;
    /* 0x1b4 */ s32 m_MaxActiveParticles;
    /* 0x1b8 */ s32 m_UsedParticleCount;
    /* 0x1bc */ s32 m_ActiveParticleCount;
    /* 0x1c0 */ u32 m_NumEntitys;
    /* 0x1c4 */ u32 m_ColourMode;
    /* 0x1c8 */ u32 m_ColourVar;
    /* 0x1cc */ u32 m_TextureMode;
    /* 0x1d0 */ u32 m_EmitterType;
    /* 0x1d4 */ void* m_pEmitter;
    /* 0x1d8 */ Bool m_Enabled;
    /* 0x1d9 */ Bool m_Visible;
    /* 0x1da */ Bool m_bOptimised;
    /* 0x1db */ Bool m_bKillParticles;
    /* 0x1dc */ Bool m_bUsingFade;
    /* 0x1dd */ Bool m_bLocal;
    /* 0x1de */ Bool m_bRotateEmitVelModifier;
    /* 0x1df */ Bool m_bInhibitEmits;
    /* 0x1e0 */ Bool m_bEmitNormal;
    /* 0x1e1 */ Bool m_bMipSystem;
    /* 0x1e2 */ Bool m_bReuseParticles;
    /* 0x1e3 */ Bool m_bAggressiveCull;
    /* 0x1e4 */ Bool m_bDelaySystem;
};

struct EXParticleSys : /* 0x000 */ EXBaseParticleSys
{
    static EXRuntimeClass classEXParticleSys;
};

#endif // EXPARTICLESYS_H
