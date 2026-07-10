#include "include/EngineX/EXItemHandler.h"

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

// u32 EXItemHandler::DoScriptCmdEvent(GEOSCRIPT_EVENT* pEventCmd, EXItemAnimator* pParentAnimator)
// {
// }

// u32 EXItemHandler::DoScriptCmdRunControl(GEOSCRIPT_RUNCONTROL* pRCCmd, EXItemAnimator* pAnimator)
// {
// }

// u32 EXItemHandler::DoScriptCmdObject(GEOSCRIPT_BASECMD* pCmd, EXItemAnimator* pAnimator)
// {
// }

// u32 EXItemHandler::DoAnimModeFunction(EXGeoAnimSetHeader* pAnimSetHeader,
//                                       EXGeoAnimModeFunction* pFunc, EXItemAnimator* pAnimator)
// {
// }
