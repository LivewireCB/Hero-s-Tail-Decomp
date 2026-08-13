#include <BASIC_System/BASIC_InterpretInterfaceLayer.h>

// CLEANUP
u8 BASIC_Main::ProcessGameSpecificInstruction(FinalCompile* line, u32* lnum)
{
    Error_ID = 9;
    return 0xbb; // 187 // Kind of seems like a magic number. Possibly an enum
        // somewhere?
}

Bool BASIC_Main::CheckWaitState(s32 state)
{
    return true;
}
