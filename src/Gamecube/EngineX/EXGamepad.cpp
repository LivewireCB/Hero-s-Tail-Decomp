#include "EngineX/EXGamepad.h"

#include "EngineX/GC/GCGamepad.h"

EXBaseGamePad* EXBaseGamePad::m_pGamePad = NULL;

EXBaseGamePad::EXBaseGamePad()
{
    for (int p = 0; p < 8; p++)
    {
        m_ButtonState.SetAt(p, 0);
        m_LastButtonState.SetAt(p, 0);
        m_ButtonEdgeDown.SetAt(p, 0);
        m_ButtonEdgeUp.SetAt(p, 0);

        for (int c = 0; c < 16; c++)
        {
            m_AnalogChan.data[p].data[c] = 0.0f;
        }

        unsigned char* pDeadZoneMode = &m_DeadZoneMode.data[0].data[0];

        pDeadZoneMode[p * 2] = 0;
        pDeadZoneMode[p * 2 + 1] = 0;
        m_ActionState.SetAt(p, 0);
        m_LastActionState.SetAt(p, 0);
        m_ActionEdgeDown.SetAt(p, 0);
        m_ActionEdgeUp.SetAt(p, 0);
        m_ActionMapCount.SetAt(p, 0);
        m_RumbleTimeHi.SetAt(p, 0);
        m_RumbleTimeLo.SetAt(p, 0);
        m_RumbleStrengthHi.SetAt(p, 0);
        m_RumbleStrengthLo.SetAt(p, 0);
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
    for (int p = 0; p < 8; p++)
    {
        if (m_ActionMapCount.GetAt(p) != 0)
        {
            m_LastActionState.SetAt(p, m_ActionState.GetAt(p));

            u32 ActionState = 0;
            u32 State = m_ButtonState.GetAt(p);
            EXPadActionMap* pAction = m_ActionMap.ElementAt(p).data;
            for (int a = 0; a < m_ActionMapCount.GetAt(p); a++)
            {
                if ((State & pAction->ButtonBits) != 0)
                {
                    ActionState |= pAction->ActionBits;
                }

                pAction++;
            }

            m_ActionState.SetAt(p, ActionState);
            m_ActionEdgeDown.SetAt(p, ActionState & ~m_LastActionState.GetAt(p));
            m_ActionEdgeUp.SetAt(p, m_LastActionState.GetAt(p) & ~m_ActionState.GetAt(p));
        }
        else
        {
            m_ActionState.SetAt(p, 0);
            m_LastActionState.SetAt(p, 0);
            m_ActionEdgeDown.SetAt(p, 0);
            m_ActionEdgeUp.SetAt(p, 0);
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
