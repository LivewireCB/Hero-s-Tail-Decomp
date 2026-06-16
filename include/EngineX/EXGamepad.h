#ifndef EXGAMEPAD_H
#define EXGAMEPAD_H

#include "types.h"

struct EXBaseGamePad
{
    static EXBaseGamePad* m_pGamePad;

    // read about EXFixedArray issue in EXMaths.h

    // /* 0x000 */ EXFixedArray<unsigned int, 8> m_ButtonState;
    // /* 0x020 */ EXFixedArray<unsigned int, 8> m_LastButtonState;
    // /* 0x040 */ EXFixedArray<unsigned int, 8> m_ButtonEdgeDown;
    // /* 0x060 */ EXFixedArray<unsigned int, 8> m_ButtonEdgeUp;
    // /* 0x080 */ EXFixedArray<EXFixedArray<float, 16>, 8> m_AnalogChan;
    // /* 0x280 */ EXFixedArray<EXFixedArray<unsigned char, 2>, 8> m_DeadZoneMode;
    // /* 0x290 */ EXFixedArray<unsigned int, 8> m_ActionState;
    // /* 0x2b0 */ EXFixedArray<unsigned int, 8> m_LastActionState;
    // /* 0x2d0 */ EXFixedArray<unsigned int, 8> m_ActionEdgeDown;
    // /* 0x2f0 */ EXFixedArray<unsigned int, 8> m_ActionEdgeUp;
    // /* 0x310 */ EXFixedArray<EXFixedArray<EXPadActionMap, 32>, 8> m_ActionMap;
    // /* 0xb10 */ EXFixedArray<unsigned char, 8> m_ActionMapCount;
    // /* 0xb18 */ EXFixedArray<unsigned int, 8> m_RumbleTimeHi;
    // /* 0xb38 */ EXFixedArray<unsigned int, 8> m_RumbleTimeLo;
    // /* 0xb58 */ EXFixedArray<unsigned char, 8> m_RumbleStrengthHi;
    // /* 0xb60 */ EXFixedArray<unsigned char, 8> m_RumbleStrengthLo;
    // /* 0xb68 */ EXFixedArray<signed char, 8> m_EnableRumble;
    // /* 0xb70 */ EXFixedArray<signed char, 8> m_Inserted;

    /* 0xb78 */ __vtbl_ptr_type* vf12701;

    // EXBaseGamePad& operator=();
    EXBaseGamePad();
    ~EXBaseGamePad();
    // /* vtable[1] */ virtual EXBaseGamePad(EXBaseGamePad*, int, void);
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
    void StopRumbleAll();
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
