#ifndef GCRENDERENV_H
#define GCRENDERENV_H

#include "types.h"

#include "EngineX/EXRenderEnv.h"

struct EXRenderEnv : EXBaseRenderEnv
{ // 0x4
    // EXRenderEnv& operator=();
    EXRenderEnv();
    // EXRenderEnv();
    /* vtable[1] */ virtual ~EXRenderEnv();
};

#endif // GCRENDERENV_H
