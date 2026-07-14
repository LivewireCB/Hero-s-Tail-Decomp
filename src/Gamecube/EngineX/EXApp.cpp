#include "EngineX/EXApp.h"

#include "EngineX/EXMalloc.h"

// EXAMPLE:
// For you to be able to use {} on a EXFixedArray, its struct must have this criteria

// No user-declared constructors
// No private or protected non-static data members
// No base classes
// No virtual functions

EXFixedArray<signed char, 2> g_bTraceInfo = { 1, 1 };
EXFixedArray<signed char, 2> g_bTraceShort = { 1, 1 };
Bool EXBaseApp::m_UseVarRateScheduler = true;
u32 EXBaseApp::m_FrameRateHoldFrames = 0;
u32 EXBaseApp::m_NominalGameFrameRate = 60;
u32 EXBaseApp::m_NominalEngineFrameRate = 60;
u32 EXBaseApp::m_VideoFrameRate = 60;
u32 EXBaseApp::m_FrameRateInt = 60;
float EXBaseApp::m_FrameRate = 60.0f;
float EXBaseApp::m_FrameLength = 1.0f / 60.0f;
float EXBaseApp::m_GameFrameRateDiv = 1.0f;
float EXBaseApp::m_GameFrameRateMul = 1.0f;
float EXBaseApp::m_EngineFrameRateDiv = 1.0f;
float EXBaseApp::m_EngineFrameRateMul = 1.0f;
float EXBaseApp::m_RenderFrameScale = 1.0f;
float EXBaseApp::m_GameRenderFrameRateDiv = 1.0f;
float EXBaseApp::m_GameRenderFrameRateMul = 1.0f;
float EXBaseApp::m_EngineRenderFrameRateDiv = 1.0f;
float EXBaseApp::m_EngineRenderFrameRateMul = 1.0f;
EXBaseApp* EXBaseApp::m_pTheApp = NULL;

EXBaseApp::EXBaseApp()
{
}

EXBaseApp::~EXBaseApp()
{
}

Bool EXBaseApp::InitInstance()
{
}

s32 EXBaseApp::ExitInstance()
{
    // I thought this was correct but i guess not

    ShutdownItemSystem();
    ShutdownFileSystem();
    ShutdownSoundManager();
    ShutdownMouse();
    ShutdownKeyboard();
    ShutdownPads();
    ShutdownDisplay();
    ShutdownWatcher();
    ShutdownDebugWndMgr();

    return 0;
}

Bool EXBaseApp::InitDisplay()
{
}

Bool EXBaseApp::InitPads()
{
}

Bool EXBaseApp::InitSoundManager()
{
}

Bool EXBaseApp::InitKeyboard()
{
}

Bool EXBaseApp::InitMouse()
{
}

Bool EXBaseApp::InitFileSystem()
{
}

Bool EXBaseApp::InitMallocMemory()
{
}

Bool EXBaseApp::InitWatcher()
{
}

Bool EXBaseApp::InitDebugWndMgr()
{
}

void EXBaseApp::ShutdownDisplay()
{
}

void EXBaseApp::ShutdownPads()
{
}

void EXBaseApp::ShutdownItemSystem()
{
}

void EXBaseApp::ShutdownSoundManager()
{
}

void EXBaseApp::ShutdownKeyboard()
{
    // STRIPPED
}

void EXBaseApp::ShutdownMouse()
{
    // STRIPPED
}

void EXBaseApp::ShutdownFileSystem()
{
}

void EXBaseApp::ShutdownWatcher()
{
}

void EXBaseApp::ShutdownDebugWndMgr()
{
}

void EXBaseApp::Update()
{
}

void EXBaseApp::Render()
{
}

void EXBaseApp::UpdateDisplay()
{
}

void EXBaseApp::UpdatePads()
{
}

void EXBaseApp::UpdateSoundManager()
{
}

void EXBaseApp::UpdateKeyboard()
{
}

void EXBaseApp::UpdateMouse()
{
}

void EXBaseApp::UpdateGame()
{
}

void EXBaseApp::UpdateFileSystem()
{
    // EXFileSys::m_pFileSys;
    // EXFileSys::Update();
}

void EXBaseApp::UpdateMemory()
{
    EXMemHeap::UpdateAllHeaps(0, 1);
}

void EXBaseApp::UpdateFrameRate(u64 FrameRate)
{
}

void EXBaseApp::UpdateRenderFrameRate()
{
    m_GameRenderFrameRateDiv = m_GameFrameRateDiv / m_RenderFrameScale;
    m_EngineRenderFrameRateDiv = m_EngineFrameRateDiv / m_RenderFrameScale;
    m_GameRenderFrameRateMul = m_GameFrameRateMul * m_RenderFrameScale;
    m_EngineRenderFrameRateMul = m_EngineFrameRateMul * m_RenderFrameScale;
}

char* EXBaseApp::QueryDataRootDirectory()
{
    return 0;
}

void EXBaseApp::EnableEscapeKey(signed char)
{
}
