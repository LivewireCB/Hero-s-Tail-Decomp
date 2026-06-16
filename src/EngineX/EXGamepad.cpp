#include "include/EngineX/EXGamepad.h"

EXBaseGamePad* EXBaseGamePad::m_pGamePad;

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
