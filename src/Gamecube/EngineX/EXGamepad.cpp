#include "EngineX/EXGamepad.h"

#include "EngineX/GC/GCGamepad.h"

EXBaseGamePad* EXBaseGamePad::m_pGamePad = NULL;

EXBaseGamePad::EXBaseGamePad()
{
    unsigned char* pDeadZoneMode = &m_DeadZoneMode.data[0].data[0];

    for (int p = 0; p < 8; p++)
    {
        m_ButtonState.m_Data[p] = 0;
        m_LastButtonState.m_Data[p] = 0;
        m_ButtonEdgeDown.m_Data[p] = 0;
        m_ButtonEdgeUp.m_Data[p] = 0;

        for (int c = 0; c < 16; c++)
        {
            m_AnalogChan.data[p].data[c] = 0.0f;
        }

        pDeadZoneMode[p * 2] = 0;
        pDeadZoneMode[p * 2 + 1] = 0;
        m_ActionState.m_Data[p] = 0;
        m_LastActionState.m_Data[p] = 0;
        m_ActionEdgeDown.m_Data[p] = 0;
        m_ActionEdgeUp.m_Data[p] = 0;
        m_ActionMapCount.m_Data[p] = 0;
        m_RumbleTimeHi.m_Data[p] = 0;
        m_RumbleTimeLo.m_Data[p] = 0;
        m_RumbleStrengthHi.m_Data[p] = 0;
        m_RumbleStrengthLo.m_Data[p] = 0;
        m_Inserted.data[p] = 0;
        m_EnableRumble.data[p] = 0;
    }
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
    EXPadActionMap* pActionMap = &m_ActionMap.m_Data[0].data[0];

    for (int p = 0; p < 8; p++)
    {
        if (m_ActionMapCount.m_Data[p] != 0)
        {
            m_LastActionState.m_Data[p] = m_ActionState.m_Data[p];

            u32 ActionState = 0;
            u32 State = m_ButtonState.m_Data[p];
            EXPadActionMap* pActions = &pActionMap[p * 32];
            EXPadActionMap* pAction = pActions;
            for (int a = 0; a < m_ActionMapCount.m_Data[p]; a++)
            {
                if ((State & pAction->ButtonBits) != 0)
                {
                    ActionState |= pAction->ActionBits;
                }

                pAction++;
            }

            m_ActionState.m_Data[p] = ActionState;
            m_ActionEdgeDown.m_Data[p] = ActionState & ~m_LastActionState.m_Data[p];
            m_ActionEdgeUp.m_Data[p] = m_LastActionState.m_Data[p] & ~m_ActionState.m_Data[p];
        }
        else
        {
            m_ActionState.m_Data[p] = 0;
            m_LastActionState.m_Data[p] = 0;
            m_ActionEdgeDown.m_Data[p] = 0;
            m_ActionEdgeUp.m_Data[p] = 0;
        }
    }
}

void EXBaseGamePad::StopRumbleAll(u8 nPad)
{
    m_RumbleTimeHi.m_Data[nPad] = 0;
    m_RumbleTimeLo.m_Data[nPad] = 0;
    m_RumbleStrengthHi.m_Data[nPad] = 0;
    m_RumbleStrengthLo.m_Data[nPad] = 0;

    ((EXGamePad*)this)->SetPadRumble(nPad);
}
