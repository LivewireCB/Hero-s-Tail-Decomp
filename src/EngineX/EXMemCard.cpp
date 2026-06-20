#include <EngineX/EXMemcard.h>

// Bool EXBaseMemCard::Init(EXSaveInfo& Info)
// {
// }

s32 EXBaseMemCard::CardChanged(Bool& Changed)
{
    Changed = 0;
    return true;
}

s32 EXBaseMemCard::CheckSavePossible(u64 Flags)
{
    return true;
}

s32 EXBaseMemCard::CheckLoadPossible(u64 Flags)
{
    return true;
}
