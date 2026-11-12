#ifndef EXITEMANIMATOR_SOUND_H
#define EXITEMANIMATOR_SOUND_H

#include "types.h"

#include "EXItemAnimator.h"
#include "EXSoundManager.h"

struct EXItemAnimator_Sound : /* 0x000 */ EXItemAnimator
{ // 0x130
    static EXRuntimeClass classEXItemAnimator_Sound;

protected:
    /* 0x110 */ EXSoundTag m_SoundTag;
    /* 0x118 */ float m_InnerRadius;
    /* 0x11c */ float m_OuterRadius;
    /* 0x120 */ u32 m_SoundFlags;
    /* 0x124 */ s8 m_Volume;
    /* 0x125 */ Bool m_SoundCreated;
    /* 0x128 */ u32 m_Handle;

public:
    EXItemAnimator_Sound();
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    static EXItemAnimator_Sound* CreateObject();
    /* vtable[3] */ virtual char* TypeName() const;
    /* vtable[4] */ virtual int Size() const;
    static EXItemAnimator_Sound* NewItem();
    /* vtable[7] */ virtual Bool Initialise(EXGeoFile* pGeoFile, EXHashCode EntityHash);
    /* vtable[5] */ virtual void DoUpdate();
    /* vtable[6] */ virtual u32 DoRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo, u64 CtrlFlags);
    /* vtable[9] */ virtual void SetObjectTime(float rObjectTime);
    void SetSoundDetails(float InnerRadius, float OuterRadius, s64 Volume, u64 SoundFlags, u64 Handle);

private:
    void UpdateSound(Bool fRender);
};

#endif // EXITEMANIMATOR_SOUND_H
