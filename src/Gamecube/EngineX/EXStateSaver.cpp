#include "EngineX/EXStateSaver.h"

Bool EXStateSaver::m_Loaded;
EXString EXStateSaver::m_StateFile;
EXStringArray EXStateSaver::m_Data;

EXStateSaver::EXStateSaver(EXString& Section)
{
}

EXStateSaver::~EXStateSaver()
{
}

void EXStateSaver::SetSection(EXString& Section)
{
}

void EXStateSaver::Save(EXString& Item, u64)
{
}

u32 EXStateSaver::Restore(EXString& Item, u64 unk) const
{
    return unk;
}

Bool EXStateSaver::LoadFile()
{
    m_Loaded = true;
    return true;
}

Bool EXStateSaver::SaveFile()
{
    return true;
}
