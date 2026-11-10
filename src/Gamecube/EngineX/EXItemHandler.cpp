#include "EngineX/EXItemHandler.h"

EXItemHandler::EXItemHandler()
{
    m_pItem = NULL;
}

EXItemHandler::~EXItemHandler()
{
}

Bool EXItemHandler::Initialise()
{
    return true;
}

Bool EXItemHandler::DoUpdate()
{
    return true;
}

Bool EXItemHandler::DoPostUpdate()
{
    return true;
}

u32 EXItemHandler::DoScriptCmdEvent(GEOSCRIPT_EVENT* pEventCmd, EXItemAnimator* pParentAnimator)
{
    return 0;
}

u32 EXItemHandler::DoScriptCmdObject(GEOSCRIPT_BASECMD* pCmd, EXItemAnimator* pAnimator)
{
    return 0;
}

u32 EXItemHandler::DoScriptCmdRunControl(GEOSCRIPT_RUNCONTROL* pRCCmd, EXItemAnimator* pAnimator)
{
    return 5;
}

u32 EXItemHandler::DoAnimModeFunction(EXGeoAnimSetHeader* pAnimSetHeader,
                                      EXGeoAnimModeFunction* pFunc, EXItemAnimator* pAnimator)
{
    return 0;
}

EXRuntimeClass* EXItemHandler::GetRuntimeClass() const
{
    return &classEXItemHandler;
}
