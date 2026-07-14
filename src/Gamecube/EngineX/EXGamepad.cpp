#include "EngineX/EXGamepad.h"

#include "EngineX/GC/GCGamepad.h"

EXBaseGamePad* EXBaseGamePad::m_pGamePad = NULL;

EXBaseGamePad::EXBaseGamePad()
{
}

EXBaseGamePad::~EXBaseGamePad()
{
}

Bool EXBaseGamePad::Init(EXBaseGamePad* pGamepad)
{
    m_pGamePad = pGamepad;
    return true;
}

void EXBaseGamePad::Shutdown()
{
    delete m_pGamePad;
}

void EXBaseGamePad::UpdateActions()
{
}

void EXBaseGamePad::StopRumbleAll(u8 nPad)
{
    m_RumbleTimeHi.m_Data[nPad] = 0;
    m_RumbleTimeLo.m_Data[nPad] = 0;
    m_RumbleStrengthHi.m_Data[nPad] = 0;
    m_RumbleStrengthLo.m_Data[nPad] = 0;

    ((EXGamePad*)this)->SetPadRumble(nPad);
}
