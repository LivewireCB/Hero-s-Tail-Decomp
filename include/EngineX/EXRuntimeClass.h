#ifndef EXRUNTIMECLASS_H
#define EXRUNTIMECLASS_H

#include "types.h"

struct EXRuntimeClass
{
    EXRuntimeClass* m_pBaseClass;
    char* m_pClassName;
    s32 m_nObjectSize;
    void* (*m_pCreateObject)(/* parameters unknown */);

    // EXRuntimeClass& operator=();
    EXRuntimeClass();
    ~EXRuntimeClass();
    void* CreateObject();
    Bool IsDerivedFrom();
};

#endif
