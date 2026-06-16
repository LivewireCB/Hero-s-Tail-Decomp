#include "include/EngineX/EXApp.h"

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
}

void EXBaseApp::UpdateMemory()
{
}

void EXBaseApp::UpdateFrameRate(u64 FrameRate)
{
}

void EXBaseApp::UpdateRenderFrameRate()
{
}

char* EXBaseApp::QueryDataRootDirectory()
{
    return 0;
}

void EXBaseApp::EnableEscapeKey(signed char)
{
}
