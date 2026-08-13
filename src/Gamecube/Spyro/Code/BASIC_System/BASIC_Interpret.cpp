#include "Spyro/Code/BASIC_System/BASIC_Interpret.h"

BASIC_Main::BASIC_Main()
{
    PollFrom = 0;

    ProcTable = 0;
    ScriptCode = 0;
    Globals = 0;
    m_pOwner = 0;
    NumInstances = 0;

    for (s32 i = 0; i < 16; i++)
    {
        DynamicInstances[i]++;
        DynamicInstances[i] = 0;
    }

    Overall_Speed = 5;

    GlobalInstance.locals = 0;
}

void BASIC_Main::SetArg(u8 num, s64 val)
{
    if (num < 8)
    {
        SetVariable(num, val);
    }
}

void BASIC_Main::SetWaitState(int state)
{
    CurrentInstance->WaitState = state;
}
