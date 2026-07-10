#include <include/EngineX/EXDisplay.h>

EXPoint EXBaseDisplay::ms_Offset;
EXFlag32 EXBaseDisplay::ms_Flags;
RGBA EXBaseDisplay::ms_BkColor;

EXGeoHeader* EXBaseDisplay::ms_pGeoHeader = NULL;
EXWnd* EXBaseDisplay::ms_pActiveWnd = NULL;
EXBaseDisplay* EXBaseDisplay::m_pDisplay = NULL;

Bool EXBaseDisplay::Init(EXBaseDisplay* pDisplay)
{
    m_pDisplay = pDisplay;
    return true;
}

// EXAMPLE:  uses the delete keyword instead of calling the virtual destructor
void EXBaseDisplay::Shutdown()
{
    delete m_pDisplay;
}

// void EXBaseDisplay::DelWnd(EXWnd* pWnd)
// {
// }

Bool EXBaseDisplay::RedrawWindow(EXDListItem* pItem)
{
}

void EXBaseDisplay::RedrawWindows()
{
}
