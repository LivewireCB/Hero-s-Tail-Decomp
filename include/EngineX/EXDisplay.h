#ifndef EXDISPLAY_H
#define EXDISPLAY_H

#include "types.h"

#include "EXFlagTemplate.h"
#include "EXList.h"
#include "EXString.h"
#include "EXRect.h"
#include "EXRGB.h"
#include "EXVector.h"
#include "EXMatrix.h"
#include "GC/GCWnd.h"
#include "EXTexture.h"
#include "EXGeoFile.h"

struct _EXResolution
{
    /* 0x0 */ u32 Width;
    /* 0x4 */ u32 Height;
    /* 0x8 */ u32 BitDepth;
};

typedef _EXResolution EXResolution;

struct EXPresentParams
{
    /* 0x00 */ u16 FBWidth;
    /* 0x02 */ u16 FBHeight;
    /* 0x04 */ u16 FBDepth;
    /* 0x06 */ u16 BBWidth;
    /* 0x08 */ u16 BBHeight;
    /* 0x0a */ u16 BBDepth;
    /* 0x0c */ u16 ZBDepth;
    /* 0x0e */ u16 PresentMode;
    /* 0x10 */ u32 Flags;
    /* 0x14 */ Bool EnableVsync;
};

struct EXBaseDisplay
{ // 0x54
protected:
    static EXBaseDisplay* m_pDisplay;
    /* 0x00 */ EXPresentParams m_Params;
    static EXPoint ms_Offset;
    static EXFlag32 ms_Flags;
    static RGBA ms_BkColor;
    static EXGeoHeader* ms_pGeoHeader;
    static EXWnd* ms_pActiveWnd;
    /* 0x18 */ EXDList m_WndList;
    /* 0x20 */ EXWnd* m_pFocusWnd;
    /* 0x24 */ EXWnd* m_pMouseWnd;
    /* 0x28 */ EXString m_CaptureDir;
    /* 0x2c */ Bool m_DoCapture;
    /* 0x2d */ Bool m_bCaptureContinuous;
    /* 0x2e */ Bool m_FeedbackOn;
    static float ms_TintRed;
    static float ms_TintGreen;
    static float ms_TintBlue;
    /* 0x2f */ u8 m_MouseTimer;
    /* 0x30 */ Bool m_ResizeCursor;
    static Bool m_bPerformanceGraphsActivated;
    /* 0x31 */ Bool m_DrawSafeFrame;
    /* 0x32 */ u8 m_SafeFramePlatforms;
    /* 0x34 */ EXRect m_SafeFrame;
    /* 0x44 */ EXTextureArray* m_pRuntimeTex;
    static mat_44 ms_mtxArray[16];
    static MXVector ms_VtxViewToCull;
    static Bool ms_UpdObjectToWorld;
    static Bool ms_UpdWorldToView;
    static Bool ms_UpdViewToClip;
    static Bool ms_UpdViewToCull;
    static Bool ms_UpdClipToScreen;
    static Bool ms_UpdViewToScreen;
    /* 0x48 */ u32 m_Effects;
    /* 0x4c */ unsigned int m_iRunTimeTextureRefCount;
    // /* 0x50 */ unsigned int unk50;

public:
    /* 0x50 */ __vtbl_ptr_type* vf3887;

    // EXBaseDisplay& operator=();
    EXBaseDisplay();
    // ~EXBaseDisplay();

    // EXAMPLE: the line above the destructor is a compiler quirk. Each one of these should be
    // replaced with the actual ~ destructor

    // /* vtable[1] */ virtual EXBaseDisplay(EXBaseDisplay*, int, void);
    /* vtable[1] */ virtual ~EXBaseDisplay();

    static EXBaseDisplay* GetDisplay(/* parameters unknown */);
    static Bool Init(EXBaseDisplay* pDisplay);
    static void Shutdown(/* parameters unknown */);
    /* vtable[2] */ virtual Bool OpenDefault();
    /* vtable[3] */ virtual Bool Open();
    /* vtable[4] */ virtual Bool ReOpen();
    /* vtable[5] */ virtual Bool Close();
    /* vtable[6] */ virtual void SetColorAdjustment();
    static EXFlag32& Flags(/* parameters unknown */);
    static RGBA BkColor(/* parameters unknown */);
    static void SetBkColor(/* parameters unknown */);
    static void SetTintColors(/* parameters unknown */);
    static EXPoint& Offset(/* parameters unknown */);
    u16 Width();
    u16 Height();
    EXPresentParams& Params();
    void EnableVSync();
    Bool VSyncEnabled();
    void SetSafeFramePlatforms();
    // EXRect SafeFrame();
    void DrawSafeFrame();
    static EXVector DispToPrim(/* parameters unknown */);
    // static EXVector2 DispToPrim(/* parameters unknown */);
    // static EXPoint DispToPrim(/* parameters unknown */);
    static EXVector PrimToDisp(/* parameters unknown */);
    // static EXVector2 PrimToDisp(/* parameters unknown */);
    // static EXPoint PrimToDisp(/* parameters unknown */);
    static EXVector2 WorldToDisp(/* parameters unknown */);
    /* vtable[7] */ virtual void SetDefaultRenderState();
    /* vtable[8] */ virtual void UpdateRenderState();
    static void SetGeoHeader(/* parameters unknown */);
    // static EXGeoHeader* GeoHeader(/* parameters unknown */);
    static void SetActiveWnd(/* parameters unknown */);
    // static EXWnd* ActiveWnd(/* parameters unknown */);
    static void SetObjectToWorld(/* parameters unknown */);
    static void SetReflectMatrix(/* parameters unknown */);
    static void SetWorldToView(/* parameters unknown */);
    static void SetViewToClip(/* parameters unknown */);
    static void SetViewToCull(/* parameters unknown */);
    static void SetViewToScreen(/* parameters unknown */);
    static void SetViewToScreenCoords(/* parameters unknown */);
    static void SetClipToScreen(/* parameters unknown */);
    static void SetWorldToShadowTex(/* parameters unknown */);
    static void SetObjectToVap(/* parameters unknown */);
    static void SetViewToCullScale(/* parameters unknown */);
    static MXMatrix44& ObjectToWorld(/* parameters unknown */);
    static MXMatrix44& ReflectMatrix(/* parameters unknown */);
    static MXMatrix44& WorldToView(/* parameters unknown */);
    static MXMatrix44& ViewToClip(/* parameters unknown */);
    static MXMatrix44& ViewToCull(/* parameters unknown */);
    static MXMatrix44& ViewToScreen(/* parameters unknown */);
    static MXMatrix44& ViewToScreenCoords(/* parameters unknown */);
    static MXMatrix44& ClipToScreen(/* parameters unknown */);
    static MXMatrix44& WorldToShadowTex(/* parameters unknown */);
    static MXMatrix44& ObjectToVap(/* parameters unknown */);
    static MXMatrix44& WorldToClip(/* parameters unknown */);
    static MXMatrix44& WorldToScreen(/* parameters unknown */);
    static MXMatrix44& ObjectToScreen(/* parameters unknown */);
    static MXMatrix44& ObjectToClip(/* parameters unknown */);
    static MXMatrix44& ObjectToCull(/* parameters unknown */);
    static MXVector& ViewToCullScale(/* parameters unknown */);
    /* vtable[9] */ virtual void UpdateTransforms();
    /* vtable[10] */ virtual Bool BeginDraw();
    /* vtable[11] */ virtual Bool EndDraw();
    /* vtable[12] */ virtual Bool Present();
    void DoCaptureToFile();
    void SetCaptureDir();
    /* vtable[13] */ virtual EXString CaptureToFile();
    void SetFeedbackWrite();
    EXWnd* AddWnd();
    void DelWnd();
    void RemoveWnd();
    void WndToTop();
    void WndToBottom();
    EXWnd* TopWnd();
    EXWnd* BottomWnd();
    Bool IsWndVisible();
    void SetFocusWnd();
    EXWnd* FocusWnd();
    void SetMouseWnd();
    EXWnd* MouseWnd();
    void UpdateWindows();
    void RedrawWindows();
    /* vtable[14] */ virtual void FlushAllWindowMem();
    /* vtable[15] */ virtual void DeleteAllWindowMem();
    EXWnd* WindowUnder();
    /* vtable[16] */ virtual void WaitDrawSync();
    EXTexture* NewRuntimeTexture();
    void DelRuntimeTexture();
    void ModifyEffects();
    u32 GetEffects();
    /* vtable[17] */ virtual void RegisterWatcherVars();
    // /* vtable[18] */ virtual EXDataArray<_EXResolution, _EXResolution>* GetAvailableResolutions();

protected:
    static Bool CalcPrimRectWindow(/* parameters unknown */);
    static Bool UpdateWindow(/* parameters unknown */);
    static Bool RedrawWindow(EXDListItem* pItem);
    static Bool FlushWindowMem(/* parameters unknown */);
    static Bool DeleteWindowMem(/* parameters unknown */);
    void SetupSafeFrame();
};

#endif // EXDISPLAY_H
