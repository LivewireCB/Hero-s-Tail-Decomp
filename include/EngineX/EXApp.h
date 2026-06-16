#ifndef EXAPP_H
#define EXAPP_H

#include "types.h"

#include "include/EngineX/EXString.h"

struct EXAppInfo
{
    /* 0x00 */ u8 Language;
    /* 0x01 */ u8 Aspect;
    /* 0x02 */ u8 Demo;
    /* 0x03 */ u8 Pad;
    /* 0x04 */ u16 InactiveTimeout;
    /* 0x06 */ u16 GameplayTimeout;
    /* 0x08 */ float MasterVolume;
    // /* 0x0c */ EXFixedArray<char, 33> DataRootDir;
    /* 0x30 */ u32 WideScreen;
    /* 0x34 */ u32 Pal60;
};

struct EXAppTime
{
    /* 0x0 */ s16 m_Year;
    /* 0x2 */ s8 m_Month;
    /* 0x3 */ s8 m_Day;
    /* 0x4 */ s8 m_Hours;
    /* 0x5 */ s8 m_Minutes;
    /* 0x6 */ s8 m_Seconds;

    // EXAppTime& operator=();
    EXAppTime();
    void SetSeconds();
    void SetMinutes();
    void SetHours();
    void SetDay();
    void SetMonth();
    void SetYear();
    s32 Seconds();
    s32 Minutes();
    s32 Hours();
    s32 Day();
    s32 Month();
    s32 Year();
    // EXAppTime();
};

enum AppState
{
    ASRun = 0,
    ASStop = 1,
    ASRestart = 2
};

enum DebugGameState
{
    DGSRun = 0,
    DGSPause = 1,
    DGSSlow = 2
};

struct EXBaseApp
{
    static EXBaseApp* m_pTheApp;
    EXString m_AppName;
    AppState m_AppState;
    EXStringArray m_Args;
    EXAppInfo m_AppInfo;
    u32 m_RetVal;
    Bool m_FrameSkipped;
    u8 m_FrameSkipIndicator;
    Bool m_AllowGamePause;
    DebugGameState m_DebugGameState;
    u32 m_DebugGameStep;
    Bool m_DoGameUpdate;
    static Bool m_UseVarRateScheduler;
    static u32 m_FrameRateHoldFrames;
    static u32 m_VideoFrameRate;
    static u32 m_NominalGameFrameRate;
    static u32 m_NominalEngineFrameRate;
    static u32 m_MinFrameRate;
    static u32 m_MaxFrameRate;
    static u32 m_FrameRateInt;
    static float m_FrameRate;
    static float m_FrameLength;
    static float m_GameFrameRateDiv;
    static float m_GameFrameRateMul;
    static float m_EngineFrameRateDiv;
    static float m_EngineFrameRateMul;
    static float m_RenderFrameScale;
    static float m_GameRenderFrameRateDiv;
    static float m_GameRenderFrameRateMul;
    static float m_EngineRenderFrameRateDiv;
    static float m_EngineRenderFrameRateMul;

    __vtbl_ptr_type* vf15087;

    // EXBaseApp& operator=();
    EXBaseApp();
    ~EXBaseApp();
    // /* vtable[1] */ virtual EXBaseApp(EXBaseApp*, int, void);
    static EXBaseApp* GetApp(/* parameters unknown */);
    void SetAppName();
    // EXString& AppName();
    /* vtable[2] */ virtual char* QueryDataRootDirectory();
    // EXAppInfo& AppInfo();
    static u32 NominalGameFrameRate(/* parameters unknown */);
    static u32 NominalEngineFrameRate(/* parameters unknown */);
    static u32 FrameRateInt(/* parameters unknown */);
    static float FrameRate(/* parameters unknown */);
    static float FrameLength(/* parameters unknown */);
    static float GameFrameRateDiv(/* parameters unknown */);
    static float GameFrameRateMul(/* parameters unknown */);
    static float EngineFrameRateDiv(/* parameters unknown */);
    static float EngineFrameRateMul(/* parameters unknown */);
    static float EngineRenderFrameRateDiv(/* parameters unknown */);
    static float EngineRenderFrameRateMul(/* parameters unknown */);
    static float GameRenderFrameRateDiv(/* parameters unknown */);
    static float GameRenderFrameRateMul(/* parameters unknown */);
    /* vtable[3] */ virtual Bool InitHardware();
    /* vtable[4] */ virtual Bool InitInstance();
    /* vtable[5] */ virtual Bool InitGame();
    /* vtable[6] */ virtual Bool ExitGame();
    /* vtable[7] */ virtual s32 ExitInstance();
    /* vtable[8] */ virtual Bool ShutdownHardware();
    /* vtable[9] */ virtual Bool InitDisplay();
    /* vtable[10] */ virtual Bool InitPads();
    /* vtable[11] */ virtual Bool InitKeyboard();
    /* vtable[12] */ virtual Bool InitMouse();
    /* vtable[13] */ virtual Bool InitSoundManager();
    /* vtable[14] */ virtual Bool InitMallocMemory();
    /* vtable[15] */ virtual Bool InitFileSystem();
    /* vtable[16] */ virtual Bool InitWatcher();
    /* vtable[17] */ virtual Bool InitDebugWndMgr();
    /* vtable[18] */ virtual void ShutdownDisplay();
    /* vtable[19] */ virtual void ShutdownPads();
    /* vtable[20] */ virtual void ShutdownKeyboard();
    /* vtable[21] */ virtual void ShutdownMouse();
    /* vtable[22] */ virtual void ShutdownSoundManager();
    /* vtable[23] */ virtual void ShutdownFileSystem();
    /* vtable[24] */ virtual void ShutdownItemSystem();
    /* vtable[25] */ virtual void ShutdownWatcher();
    /* vtable[26] */ virtual void ShutdownDebugWndMgr();
    /* vtable[27] */ virtual Bool MainUpdate();
    /* vtable[28] */ virtual void Update();
    /* vtable[29] */ virtual void Render();
    /* vtable[30] */ virtual void UpdateDisplay();
    /* vtable[31] */ virtual void UpdatePads();
    /* vtable[32] */ virtual void UpdateSoundManager();
    /* vtable[33] */ virtual void UpdateKeyboard();
    /* vtable[34] */ virtual void UpdateMouse();
    /* vtable[35] */ virtual void UpdateFileSystem();
    /* vtable[36] */ virtual void UpdateMemory();
    /* vtable[37] */ virtual void UpdateGame();
    /* vtable[38] */ virtual void EnableEscapeKey(s8);
    static void UpdateFrameRate(float FrameRate);
    static void UpdateFrameRate(u64 FrameRate);
    static void UpdateRenderFrameRate(/* parameters unknown */);
    static void SetFrameRateHoldFrames(/* parameters unknown */);
    static void SetVideoFrameRate(/* parameters unknown */);
    static u32 VideoFrameRate(/* parameters unknown */);
    static void SetMinFrameRate(/* parameters unknown */);
    static u32 MinFrameRate(/* parameters unknown */);
    static void SetMaxFrameRate(/* parameters unknown */);
    static u32 MaxFrameRate(/* parameters unknown */);
    static void SetRenderFrameScale(/* parameters unknown */);
    static float RenderFrameScale(/* parameters unknown */);
    void EnableGamePause();
    void SetDebugGameState();
    DebugGameState GetDebugGameState();
    Bool DoGameUpdate();
    void Stop();
    void Restart();
    AppState GetAppState();
    void SetRetVal();
    // EXStringArray& Args();
    Bool FrameSkipped();
    Bool FrameSkipIndicator();
    void SetWideScreen();
    void SetPal60();
    void SetLanguage();
    /* vtable[39] */ virtual void v_OnFileSysRemoveFile();
};

#endif // EXAPP_H
