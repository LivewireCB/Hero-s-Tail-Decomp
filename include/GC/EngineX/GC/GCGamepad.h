#ifndef GCGAMEPAD_H
#define GCGAMEPAD_H

#include "types.h"
#include "EngineX/EXGamepad.h"

struct EXGamePad : /* 0x000 */ EXBaseGamePad
{ // 0xbd0
protected:
    /* 0xb7c */ EXFixedArray<long long unsigned int*, 8> m_PadDMABuffer;
    /* 0xb9c */ EXFixedArray<signed char, 8> m_PadPhase;
    /* 0xba4 */ EXFixedArray<unsigned char, 8> m_PadType;
    /* 0xbac */ EXFixedArray<unsigned char, 8> m_PadID;
    /* 0xbb4 */ EXFixedArray<signed char, 8> m_PadRumble;
    /* 0xbbc */ EXFixedArray<unsigned char, 8> m_PadPort;
    /* 0xbc4 */ EXFixedArray<unsigned char, 8> m_PadSlot;
    /* 0xbcc */ Bool m_PadsInitialised;

public:
    // EXGamePad& operator=();
    EXGamePad();
    // EXGamePad();
    /* vtable[1] */ virtual ~EXGamePad();
    Bool OpenPads();
    void Update();
    Bool PadAttached();
    char* SlotName();
    Bool IsMultiTapConnected();
    Bool HasAnalogStick1();
    Bool HasAnalogStick2();
    Bool HasAnalogSticks();
    Bool HasAnalogShoulders();
    Bool HasPressureButtons();
    void SetPadRumble(unsigned char);

protected:
    void StorePadData();
    void UpdateController();
};

#endif // GCGAMEPAD_H
