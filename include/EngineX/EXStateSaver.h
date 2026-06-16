#ifndef EXSTATESAVER_H
#define EXSTATESAVER_H

#include "types.h"

#include "include/EngineX/EXString.h"

struct EXStateSaver
{
    static EXString m_StateFile;
    static EXStringArray m_Data;
    static Bool m_Loaded;
    /* 0x0 */ EXString m_Section;
    /* 0x4 */ s32 m_SectionIndex;
    /* 0x8 */ Bool m_StateChanged;

    /* 0xc */ __vtbl_ptr_type* vf20838;

    // EXStateSaver& operator=();
    EXStateSaver(EXString&);
    ~EXStateSaver();
    // /* vtable[1] */ virtual EXStateSaver(EXStateSaver*, int, void);
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
