#include "EngineX/EXStateSaver.h"

#include "EngineX/EXString.h"

Bool EXStateSaver::m_Loaded;

// EXAMPLE: Force a data section with the __attribute__((section(".section"))) part.
EXString EXStateSaver::m_StateFile __attribute__((section(".sbss")));

EXStringArray EXStateSaver::m_Data;

EXStateSaver::EXStateSaver(EXString& Section)
{
    m_Section.m_pData = NULL;

    if (EXStateSaver::m_Loaded == 0)
    {
        LoadFile();
    }
    SetSection(Section);

    m_StateChanged = 0;
}

EXStateSaver::~EXStateSaver()
{
    if (m_StateChanged != NULL)
    {
        SaveFile();
    }
    m_Section.DeallocMem();
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
