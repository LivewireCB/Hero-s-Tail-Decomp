#ifndef EXGAMEPAD_H
#define EXGAMEPAD_H

#include "types.h"
#include "EngineX/EXMalloc.h"
#include "EXFixedArray.h"

enum AnalogChan
{
    LAX = 0,
    LAY = 1,
    RAX = 2,
    RAY = 3,
    PLDUp = 4,
    PLDDown = 5,
    PLDLeft = 6,
    PLDRight = 7,
    PBtn1 = 8,
    PBtn2 = 9,
    PBtn3 = 10,
    PBtn4 = 11,
    ALS1 = 12,
    ALS2 = 13,
    ARS1 = 14,
    ARS2 = 15,
    ANALOGCOUNT = 16
};

enum DeadZoneMode
{
    DZCentre = 0,
    DZIndependent = 1,
    DZRaw = 2
};

struct EXPadActionMap
{ // 0x8
    /* 0x0 */ u32 ButtonBits;
    /* 0x4 */ u32 ActionBits;
};

struct EXFixedArray<EXFixedArray<EXPadActionMap, 32>, 8>
{ // 0x800
    /* 0x000 */ EXFixedArray<EXPadActionMap, 32> m_Data[8];

    // EXFixedArray<EXFixedArray<EXPadActionMap, 32>, 8>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    // size_t Size();
    // size_t GetUpperBound();
    // EXFixedArray<EXPadActionMap, 32>& ElementAt();
    // EXFixedArray<EXPadActionMap, 32> GetAt();
    // void SetAt();
    // EXFixedArray<EXPadActionMap, 32>* GetData();
    // EXFixedArray<EXPadActionMap, 32>* GetData();
    // EXFixedArray<EXPadActionMap, 32>* operator EXFixedArray<EXPadActionMap, 32>*();
    // EXFixedArray<EXPadActionMap, 32>* operator EXFixedArray<EXPadActionMap, 32>*();
};

struct EXFixedArray<unsigned int, 8>
{ // 0x20
    /* 0x00 */ unsigned int m_Data[8];

    // EXFixedArray<unsigned int, 8>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    // size_t Size();
    // size_t GetUpperBound();
    // u32& ElementAt();
    // u32 GetAt();
    // void SetAt();
    // u32* GetData();
    // u32* GetData();
    // u32* operator unsigned int*();
    // u32* operator unsigned int*();
};

struct EXFixedArray<unsigned char, 8>
{ // 0x8
    /* 0x0 */ unsigned char m_Data[8];

    // EXFixedArray<unsigned char, 8>& operator=();
    // EXFixedArray();
    // EXFixedArray();
    // size_t Size();
    // size_t GetUpperBound();
    // EXRotOrder& ElementAt();
    // EXRotOrder GetAt();
    // void SetAt();
    // EXRotOrder* GetData();
    // EXRotOrder* GetData();
    // EXRotOrder* operator unsigned char*();
    // EXRotOrder* operator unsigned char*();
};

struct EXBaseGamePad
{
    static EXBaseGamePad* m_pGamePad;

    /* 0x000 */ EXFixedArray<unsigned int, 8> m_ButtonState;
    /* 0x020 */ EXFixedArray<unsigned int, 8> m_LastButtonState;
    /* 0x040 */ EXFixedArray<unsigned int, 8> m_ButtonEdgeDown;
    /* 0x060 */ EXFixedArray<unsigned int, 8> m_ButtonEdgeUp;
    /* 0x080 */ EXFixedArray<EXFixedArray<float, 16>, 8> m_AnalogChan;
    /* 0x280 */ EXFixedArray<EXFixedArray<unsigned char, 2>, 8> m_DeadZoneMode;
    /* 0x290 */ EXFixedArray<unsigned int, 8> m_ActionState;
    /* 0x2b0 */ EXFixedArray<unsigned int, 8> m_LastActionState;
    /* 0x2d0 */ EXFixedArray<unsigned int, 8> m_ActionEdgeDown;
    /* 0x2f0 */ EXFixedArray<unsigned int, 8> m_ActionEdgeUp;
    /* 0x310 */ EXFixedArray<EXFixedArray<EXPadActionMap, 32>, 8> m_ActionMap;
    /* 0xb10 */ EXFixedArray<unsigned char, 8> m_ActionMapCount;
    /* 0xb18 */ EXFixedArray<unsigned int, 8> m_RumbleTimeHi;
    /* 0xb38 */ EXFixedArray<unsigned int, 8> m_RumbleTimeLo;
    /* 0xb58 */ EXFixedArray<unsigned char, 8> m_RumbleStrengthHi;
    /* 0xb60 */ EXFixedArray<unsigned char, 8> m_RumbleStrengthLo;
    /* 0xb68 */ EXFixedArray<signed char, 8> m_EnableRumble;
    /* 0xb70 */ EXFixedArray<signed char, 8> m_Inserted;

    // /* 0xb78 */ __vtbl_ptr_type* vf12701;

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXBaseGamePad& operator=();
    EXBaseGamePad();
    /* vtable[1] */ virtual ~EXBaseGamePad();
    static EXBaseGamePad* GetGamePad(/* parameters unknown */);
    static Bool Init(EXBaseGamePad*);
    static void Shutdown(/* parameters unknown */);
    void UpdateActions();
    void SetActionMap();
    Bool ButtonDown();
    Bool ButtonUp();
    Bool ButtonPressed();
    Bool ButtonReleased();
    u32 Buttons();
    u32 ButtonsPressed();
    u32 ButtonsReleased();
    u32* LastButtons();
    u32* ButtonState();
    u32* ButtonEdgeDown();
    u32* ButtonEdgeUp();
    void SetButtonState();
    void SetButtonEdgeDown();
    void SetButtonEdgeUp();
    Bool ActionDown();
    Bool ActionUp();
    Bool ActionPressed();
    Bool ActionReleased();
    u32 Actions();
    // u32 ActionPressed();
    // u32 ActionReleased();
    u32* ActionState();
    float Analog();
    float* AnalogChan();
    // DeadZoneMode LeftDeadZoneMode();
    // DeadZoneMode RightDeadZoneMode();
    void SetDeadZoneMode();
    void SetLeftDeadZoneMode();
    void SetRightDeadZoneMode();
    void StartRumbleAll();
    void StartRumbleHi();
    void StartRumbleLo();
    void StopRumbleAll(u8 nPad);
    void StopRumbleHi();
    void StopRumbleLo();
    void KillAllRumble();
    void EnableAllRumble();
    void EnableRumble();
    Bool RumbleEnabled();
    Bool Inserted();
    void SetInserted();
    void SetRemoved();

    void RumbleUpdate();
};

#endif // EXGAMEPAD_H
