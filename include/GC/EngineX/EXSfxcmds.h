#ifndef EXSFXCMDS_H
#define EXSFXCMDS_H

#include "types.h"

struct Command_Buffer_tag
{ // 0x3000
    /* 0x0000 */ char Buffer[12288];
};

typedef Command_Buffer_tag Command_Buffer;

struct SFXCommandBuffer
{ // 0x14
    /* 0x00 */ Command_Buffer* CmdBuf[2];
    /* 0x08 */ int CmdBufNum;
    /* 0x0c */ char* CmdBufPtr;
    /* 0x10 */ int CmdBufSize;

    // SFXCommandBuffer& operator=();
    SFXCommandBuffer();
    // SFXCommandBuffer();
    SFXCommandBuffer(SFXCommandBuffer*, int, void);
    void SwapBuffers();
    void IncPtr(SFXCommandBuffer*, int, void);
    void Init();
};

// debug info shows that these were typedef-ed for some reason.
typedef struct
{ // 0x8
    /* 0x0 */ s32 HashCode;
    /* 0x4 */ void* Handle;
} SFXActiveDetails2;

typedef struct
{ // 0x2b8
    /* 0x000 */ int FileStatus[16];
    /* 0x040 */ s32 Count;
    /* 0x044 */ SFXActiveDetails2 ActiveData[60];
    /* 0x224 */ int MusicLastJump[2];
    /* 0x22c */ int MusicSectionNowPlaying[2];
    /* 0x234 */ s32 DriveActivity;
    /* 0x238 */ int SoundBanksLoaded[10];
    /* 0x260 */ s32 SFX_Fade_Status;
    /* 0x264 */ s32 MFX_Fade_Status;
    /* 0x268 */ s32 EnableAudio;
    /* 0x26c */ u32 MaxSeekDelta;
    /* 0x270 */ unsigned int LoadPercent[3];
    /* 0x27c */ u32 IOP_Error_ReturnCode;
    /* 0x280 */ u32 IOP_ThreadCounterHP;
    /* 0x284 */ u32 IOP_ThreadCounterMU;
    /* 0x288 */ u32 IOP_ThreadCounterHD;
    /* 0x28c */ u32 IOP_ThreadStepCountHP;
    /* 0x290 */ u32 IOP_ThreadStepCountMU;
    /* 0x294 */ s32 IOP_FileKperSecond;
    /* 0x298 */ s32 IOP_FileActiveTimePercent;
    /* 0x29c */ s32 IOP_FileKperLast2Seconds;
    /* 0x2a0 */ s32 IOP_FileActiveTimePercentLast2Seconds;
    /* 0x2a4 */ s32 IOP_FileKperSecondLast10Seconds;
    /* 0x2a8 */ s32 IOP_FileActiveTimePercentLast10Seconds;
    /* 0x2ac */ u32 MemoryFree;
    /* 0x2b0 */ u32 MemoryAlloc;
    /* 0x2b4 */ s32 IOP_FileSystemShutdownComplete;
} SFXActiveDetails;

typedef struct
{ // 0xc
    /* 0x0 */ s32 HashCode;
    /* 0x4 */ void* Handle;
    /* 0x8 */ s32 Life;
} SFXRequestedActiveDetails2;

typedef struct
{ // 0x2d4
    /* 0x000 */ s32 Count;
    /* 0x004 */ SFXRequestedActiveDetails2 ActiveData[60];
} SFXRequestedActiveDetails;

#endif // EXSFXCMDS_H
