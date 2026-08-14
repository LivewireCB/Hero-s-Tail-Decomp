#ifndef EXSTATESAVER_H
#define EXSTATESAVER_H

#include "types.h"

#include "EngineX/EXString.h"
#include "EngineX/EXMemoryManager.h"

struct EXStateSaver
{
    static EXString m_StateFile;
    static EXStringArray m_Data;
    static Bool m_Loaded;
    /* 0x0 */ EXString m_Section;
    /* 0x4 */ s32 m_SectionIndex;
    /* 0x8 */ Bool m_StateChanged;

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXStateSaver& operator=();
    EXStateSaver(EXString&);
    // ~EXStateSaver();
    /* vtable[1] */ virtual ~EXStateSaver();
    static void SetStateFile(/* parameters unknown */);
    void SetSection(EXString& Section);
    void Save(EXString& Item, u64);
    // void Save();
    void Savef();
    EXString Restore();
    u32 Restore(EXString& Item, u64) const;
    float Restoref();

    static Bool LoadFile(/* parameters unknown */);
    static Bool SaveFile(/* parameters unknown */);
};

#endif // EXSTATESAVER_H
