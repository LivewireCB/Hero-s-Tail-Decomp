#ifndef GCWND_H
#define GCWND_H

#include <types.h>

#include <include/GC/EngineX/EXWnd.h>

// TODO: Fill out struct
struct EXWnd : /* 0x0000 */ EXBaseWnd
{ // 0x12b0
protected:
    // /* 0x0140 */ EXDrawStream m_PreStream;
    // /* 0x0280 */ EXDrawStream m_DebugStream3D;
    // /* 0x03c0 */ EXDrawStream m_DebugStream2D;
    // /* 0x0500 */ EXArray<EXDrawStream, EXDrawStream&> m_SpriteStream;
    // /* 0x0520 */ EXDrawStream m_TextStream;
    // /* 0x0660 */ EXDrawStream m_LineStream;
    // /* 0x07a0 */ EXArray<EXDrawStream, EXDrawStream&> m_TriFanStream;
    // /* 0x07b4 */ EXArray<EXDrawStream, EXDrawStream&> m_TriStripStream;
    // /* 0x07d0 */ EXDrawStream m_FxDrawStream;
    // /* 0x0910 */ EXDrawStream m_BloomStream;
    // /* 0x0a50 */ EXDrawStream m_FSSDrawStream;
    // /* 0x0b90 */ EXDrawStream m_TexCapStream;
    // /* 0x0cd0 */ EXDrawStream m_BeginShadowStream;
    // /* 0x0e10 */ EXDrawStream m_EndShadowStream;
    // /* 0x0f50 */ EXFixedArray<EXFixedArray<EXWndDMAQueue, 14>, 2> m_DMAQueue;
    /* 0x1180 */ u32 m_LineSeq;
    /* 0x1184 */ u32 m_TriFanSeq;
    /* 0x1188 */ u32 m_TriStripSeq;
    // /* 0x1190 */ sceGifTag m_LineGifTag;
    // /* 0x11a0 */ sceGifTag m_TriFanGifTag;
    // /* 0x11b0 */ sceGifTag m_TriStripGifTag;
    // /* 0x11c0 */ sceGifTag m_TriStripEnvTag;
    // /* 0x11d0 */ EXVifSCDmaPacket m_SPpkt;
    /* 0x1200 */ u128* m_BloomPacket[2];
    // static EXWndDMAItem* m_LastDMAItem;
    // static EXWndDMAItem* m_LastDMAItem1;
    // static EXWndDMAItem* m_LastDMAItem2;
    // /* 0x1210 */ EXMatrix m_ShadowWorldToView;
    // /* 0x1250 */ EXMatrix m_ShadowViewToScreen;
    /* 0x1290 */ float m_fOffsetU;
    /* 0x1294 */ float m_fOffsetV;
    /* 0x1298 */ u8 m_NoDrawTriFanStreams;
    /* 0x129a */ u16 m_CurrentDrawTriFan_TexPages;
    /* 0x129c */ u16 m_CurrentDrawTriFan_PalCount;
    /* 0x129e */ u8 m_NoDrawTriStripStreams;
    /* 0x12a0 */ u16 m_CurrentDrawTriStrip_TexPages;
    /* 0x12a2 */ u16 m_CurrentDrawTriStrip_PalCount;
    /* 0x12a4 */ u8 m_NoDrawSpriteStreams;
    /* 0x12a6 */ u16 m_CurrentDrawSprite_TexPages;
    /* 0x12a8 */ u16 m_CurrentDrawSprite_PalCount;
    /* 0x12aa */ s8 m_iHadBloom;

public:
    // EXWnd& operator=();
    EXWnd();
    // EXWnd();
    // /* vtable[1] */ virtual EXWnd(EXWnd*, int, void);
    /* vtable[12] */ virtual void BeginDrawShadow();
    /* vtable[14] */ virtual void EndDrawShadow();
    /* vtable[50] */ virtual void SetShadowWorldToView();
    /* vtable[51] */ virtual void SetShadowViewToScreen();
    // MXMatrix44& ShadowWorldToView();
    // MXMatrix44& ShadowViewToScreen();
    /* vtable[16] */ virtual void BeginDraw();
    /* vtable[18] */ virtual void EndDraw();
    /* vtable[28] */ virtual void DrawLine();
    /* vtable[29] */ virtual void DrawLines();
    // /* vtable[30] */ virtual void DrawLines();
    /* vtable[31] */ virtual void SetTriFanBlendMode();
    /* vtable[32] */ virtual void SetTriFanZMode();
    /* vtable[33] */ virtual void SelectTriFanTexture();
    /* vtable[34] */ virtual void DrawTriFan();
    void UseNextDrawTriFanStream();
    /* vtable[35] */ virtual void SetTriStripBlendMode();
    /* vtable[36] */ virtual void SetTriStripZMode();
    /* vtable[37] */ virtual void SelectTriStripTexture();
    /* vtable[38] */ virtual void DrawTriStrip();
    void UseNextDrawTriStripStream();
    /* vtable[40] */ virtual void _SelectSprite2DTexture();
    /* vtable[39] */ virtual void _SetSprite2DBlendMode();
    /* vtable[41] */ virtual void _SetSprite2DClipRect();
    /* vtable[42] */ virtual void _DrawSprite2D();
    // /* vtable[43] */ virtual void _DrawSprite2D();
    // /* vtable[44] */ virtual void _DrawSprite2D();
    void UseNextDrawSpriteStream();
    void DrawSprite2DData();
    /* vtable[19] */ virtual void DeleteRenderMem();
    void AddPacketToQueue();
    // void AddPacketToQueue();
    // void AddPacketToQueue();
    // void AddPacketToQueue();
    void StopTexUpload();
    void RestartTexUpload();
    void CaptureToTexture();
    void BuildMasterPacket();
    static void InitGSPacket(/* parameters unknown */);
    void DrawFullScreenShadowSprite();
    void DrawFSTexSprite();
    void DrawFullScreenNoiseSprite();
    void DrawFSTexSprite2();
    void DrawFullScreenFeedbackSprite();
    void DrawFSTexSprite3();
    void InvertFrameBufferVideo();
    void DrawFSTexSprite4();
    void DrawMotionBlurSprite();
    void MoBTexSprite();
    void MoBTexSprite2();
    void DrawZBufferFog();
    void FogMoveRG2BA();
    void FogSprite();
    void FogTexSprite();
    void DrawZBufferDoF();
    void DoFMoveRG2BA();
    void DoFTexSprite1();
    void DoFTexSprite2();
    void InitBloomBlit();
    void DoBloomBlit();
    void ApplyBloomEffect();
    void RebuildBloomPackets();
    void DoBlitTex();
    void BlitTexture();
    /* vtable[45] */ virtual void MovieOpen();
    /* vtable[46] */ virtual void MovieUpdate();
    /* vtable[47] */ virtual void MovieRender();
    /* vtable[48] */ virtual void MovieClose();
    void LineList2D();

protected:
    /* vtable[49] */ virtual void RebuildBloom();
    /* vtable[52] */ virtual void _SetDebugObjectToWorld();
    /* vtable[53] */ virtual void _Line2D();
    /* vtable[54] */ virtual void _Rect2D();
    /* vtable[55] */ virtual void _SolidRect2D();
    /* vtable[56] */ virtual void _Line3D();
    // /* vtable[57] */ virtual void _Line3D();
    /* vtable[58] */ virtual void _TriLine3D();
    /* vtable[59] */ virtual void _QuadLine3D();
    /* vtable[60] */ virtual void _Text3D();
    void ResetDMAQueues();
    // EXWndDMAItem& NextDMAQueueItem();
    void InitLineStream();
    void InitTriFanStream();
    void InitTriStripStream();
    void EndLineStream();
    void EndTriFanStream();
    void EndTriStripStream();
    void SortDMAQueue();
    void SortDMAEntries();
    void RadixSortDMAEntries();
    static Bool SendDMAQueuesChild(/* parameters unknown */);
    static Bool BuildMasterPacketChild(/* parameters unknown */);
    void DrawDebugText();
};

#endif // GCWND_H
