#ifndef EXSOUNDMANAGER_H
#define EXSOUNDMANAGER_H

#include "types.h"

#include "EXAllocator.h"
#include "EXDataArray.h"
#include "EXFile.h"
#include "EXFileSys.h"
#include "ExPtrArray.h"
#include "EXHashcode.h"
#include "EXList.h"
#include "EXVector.h"

#include "EXSoundManagerStructs.h" // debug info shows that this file was included
// I have no clue what this is supposed to have in it. Should it be the EXSound stuff or the SoundManager struct itself?

#include "EXSfxcmds.h"

enum TrSndTypes
{
    TrType2d = 0,
    TrTypeAmb = 1,
    TrType3d = 2,
    TrType3dRndPos = 3,
    TrType2dPL2 = 4,
    TrType2dRndPos = 5
};

struct EXSoundDetails
{ // 0xc
    /* 0x0 */ s16 InnerRadius;
    /* 0x2 */ s16 OuterRadius;
    /* 0x4 */ float Duration;
    /* 0x8 */ u8 Looping;
    /* 0x9 */ u8 TrackingType;
    /* 0xa */ s8 StreamType;
    /* 0xb */ Bool Type3D;
};

struct EXSoundDetailsFileHeader
{ // 0x34
    /* 0x00 */ u32 Marker;
    /* 0x04 */ s32 FileHash;
    /* 0x08 */ s32 Version;
    /* 0x0c */ s32 Length;
    /* 0x10 */ s32 Platform;
    /* 0x14 */ s32 TimeStamp;
    /* 0x18 */ s32 Pad1;
    /* 0x1c */ s32 Pad2;
    /* 0x20 */ s32 MinIndex;
    /* 0x24 */ s32 MaxIndex;
    /* 0x28 */ EXSoundDetails Details[1];
};

struct EXSoundDetailsFile : /* 0x00 */ EXFile
{ // 0x2c
protected:
    /* 0x20 */ u32 m_DetailsHandle;
    /* 0x24 */ s32 m_MinIndex;
    /* 0x28 */ s32 m_MaxIndex;

public:
    // EXSoundDetailsFile& operator=();
    EXSoundDetailsFile();
    /* vtable[2] */ virtual ~EXSoundDetailsFile();
    // EXSoundDetailsFile();
    /* vtable[3] */ virtual Bool OnLoad();
    /* vtable[4] */ virtual Bool OnLoaded();
    /* vtable[5] */ virtual Bool OnKill();
    s32 MinIndex();
    s32 MaxIndex();
    u32 DetailsHandle();
    EXSoundDetailsFileHeader* DetailsHeader();
    EXSoundDetails& SoundDetails();
};

struct EXSoundFileEntry
{ // 0x8
    /* 0x0 */ EXFILEINFO* pFInf;
    /* 0x4 */ EXFileList* pFileList;
};

// TODO: move this struct to its proper location
struct XFileHandle
{ // 0x1a0
    /* 0x000 */ u32 DiskStartSector[4];
    /* 0x010 */ u32 FileStart[4];
    /* 0x020 */ u32 FileLength;
    /* 0x024 */ char FileName[4][94];
    /* 0x19c */ u16 IsBigFileFile;
};

struct EXDataArray<EXSoundFileEntry, const EXSoundFileEntry&>
{ // 0x10
protected:
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ EXSoundFileEntry* m_pData;

public:
    EXDataArray();
    // EXDataArray();
    ~EXDataArray();
    void Init();
    int Size();
    int AllocSize();
    int GetUpperBound();
    void SetSize();
    void SetGrowBy(EXDataArray<EXSoundFileEntry, const EXSoundFileEntry&>*, int, void);
    void AllocMem(EXDataArray<EXSoundFileEntry, const EXSoundFileEntry&>*, int, void);
    void FreeExtra();
    void Empty();
    void RemoveAll();
    void SetAt();
    EXSoundFileEntry GetAt();
    EXSoundFileEntry& ElementAt();
    EXSoundFileEntry* GetData();
    // EXSoundFileEntry* GetData();
    void SetAtGrow();
    int Add();
    int Append();
    void Copy();
    EXSoundFileEntry& AddSpace();
    s32 AddUnique();
    s32 Find();
    // EXSoundFileEntry& operator[]();
    // EXSoundFileEntry& operator[]();
    void InsertAt();
    void RemoveAt();
    // void InsertAt();
    // EXDataArray<EXSoundFileEntry, const EXSoundFileEntry&>& operator=();

protected:
    void GrowArray();
};

struct EXSoundFileListArray : /* 0x0 */ EXDataArray<EXSoundFileEntry, const EXSoundFileEntry&>
{ // 0x10
};

struct EXSoundTag : /* 0x0 */ EXLDList
{ // 0x8
    // EXSoundTag& operator=();
    EXSoundTag();
    // EXSoundTag();
    ~EXSoundTag();
    void Remove();
    void RemoveAll();
    // EXSoundHandle* StartSound();
    // EXSoundHandle* StartSound();
    // EXSoundHandle* StartSound();
    // EXSoundHandle* AddTrackingSound();
    void UpdatePositionAndVelocity();
    void SetVolume(EXHashCode SoundHash, u64 Volume) const;
    void SetPitch(u64 Pitch) const;
    Bool IsPlaying();
    void SetVolume(u64 Volume) const;
    // void SetPitch();
    // Bool IsPlaying();
    void KillSoundPlaying();
    // void KillSoundPlaying();
    void KillSoundPlayingLooping();
    // void KillSoundPlayingLooping();

protected:
    void Add();
    // void Remove();
};

struct EXSoundHandle : /* 0x00 */ EXLDListItem
{ // 0x30
protected:
    /* 0x0c */ EXODListItem m_ManagerList;
    /* 0x18 */ u32 m_Handle;
    /* 0x1c */ EXHashCode m_HashCode;
    /* 0x20 */ float m_InnerRadius;
    /* 0x24 */ float m_OuterRadius;
    /* 0x28 */ u16 m_SoundTimeout;
    /* 0x2a */ Bool m_fLoopingSound;
    /* 0x2b */ Bool m_fSoundActive;
    /* 0x2c */ Bool m_fTrackingSound;
    /* 0x2d */ s8 m_UpdateState;
    /* 0x2e */ s8 m_TempTimer;

public:
    // EXSoundHandle& operator=();
    EXSoundHandle();
    // EXSoundHandle();

private:
    void UpdateTrackingSound();

public:
    void Initialise();
    void* HandleAddr();
    u32 Handle();
    void SetHandle();
    void SetHashCode();
    EXHashCode HashCode();
    void SetTrackingSound();
    Bool TrackingSound();
    void SetSoundActive();
    Bool SoundActive();
    Bool LoopingSound();
    void SetLoopingSound();
    s8 UpdateState();
    void SetUpdateState();
    void SetSoundTimeout();

protected:
    u16& SoundTimeout();
    s8& TempTimer();
    void Remove();
    EXODListItem& ManagerList();
};

struct EXAllocator<EXSoundHandle>
{ // 0x14
protected:
    /* 0x00 */ EXAllocatorBlockArray m_Blocks;
    /* 0x10 */ u32 m_BlockSize;

public:
    // EXAllocator<EXSoundHandle>& operator=();
    EXAllocator();
    // EXAllocator();
    ~EXAllocator();
    EXSoundHandle* Get();
    void Remove();
};

struct EXSoundListener
{ // 0x60
protected:
    /* 0x00 */ EXVector m_vPos;
    /* 0x10 */ EXVector m_vVel;
    /* 0x20 */ EXVector m_vDir;
    /* 0x30 */ EXVector m_vUp;
    /* 0x40 */ EXVector m_vNorm;
    /* 0x50 */ Bool m_Active;

public:
    // EXSoundListener& operator=();
    EXSoundListener();
    // EXSoundListener();
    void SystemUpdate();
    void UpdatePosition();
    // void UpdatePosition();
    EXVector& Position();
    void SetActive();
    Bool IsActive();
};

struct EXBaseSoundManager
{ // 0xf38
    // protected:
    static EXBaseSoundManager* m_pSoundManager;
    static EXPtrArray<EXSoundDetailsFile> m_SoundDetailsFileArray;
    static EXSoundDetails DefaultSFXOutputData;
    /* 0x000 */ EXSoundFileListArray m_SoundFileArray;
    /* 0x010 */ EXPtrArray<EXSoundListener> m_ListenerArray;
    /* 0x020 */ EXAllocator<EXSoundHandle> m_SoundAllocator;
    /* 0x034 */ EXODList m_SoundList;
    /* 0x03c */ u32 m_NumActiveListeners;
    /* 0x040 */ EXHashCode m_MusicHash;
    /* 0x044 */ Bool m_MusicForceReStart;
    /* 0x048 */ s32 m_EnvReverbDepth;
    /* 0x04c */ Bool m_EnvIndoors;
    /* 0x04d */ Bool m_EnvUnderwater;
    /* 0x050 */ s32 m_MusicMasterVolume;
    /* 0x054 */ s32 m_SfxMasterVolume;
    /* 0x058 */ s32 m_SFXLanguageNumber;
    /* 0x05c */ s32 m_SFXModeNumber;
    /* 0x060 */ s32 m_StreamFileInitialise;
    /* 0x064 */ char m_TempDataBuf[1024];
    /* 0x464 */ SFXRequestedActiveDetails m_SFXRequestedActiveData;
    /* 0x738 */ SFXActiveDetails* m_pSFXActiveData;
    /* 0x73c */ SFXCommandBuffer m_CmdBuf;
    /* 0x750 */ int m_FileCount;
    /* 0x754 */ u32 m_LastTime;
    /* 0x758 */ u32 m_DebugTime;
    /* 0x75c */ unsigned int m_LoadPercent[300];
    /* 0xc0c */ unsigned int m_MaxSeekDelta[100];
    /* 0xd9c */ unsigned int m_Markers[100];
    /* 0xf2c */ u32 m_SetMarker;
    /* 0xf30 */ u32 m_Max_MaxSeekDelta;

public:
    // /* 0xf34 */ __vtbl_ptr_type* $vf13906;

    // EXBaseSoundManager& operator=();
    EXBaseSoundManager();
    // EXBaseSoundManager();
    /* vtable[1] */ virtual ~EXBaseSoundManager();
    static EXBaseSoundManager* GetSoundManager(/* parameters unknown */);
    static Bool Init(/* parameters unknown */);
    static void Shutdown(/* parameters unknown */);
    void SendExitCommand();
    /* vtable[2] */ virtual Bool OpenSoundManager();
    EXODList& SoundList();
    EXHashCode MusicHash();
    Bool MusicForceReStart();
    void SfxRemoveAll();
    // void SfxRemoveAll();
    void SfxRemoveAllHandle();
    EXSoundListener* AllocateListener();
    void RemoveListener();
    EXVector GetListenerPos();
    void StartMusic();
    static Bool AddSoundDetailsTable(/* parameters unknown */);
    // static Bool AddSoundDetailsTable(/* parameters unknown */);
    static Bool DeleteSoundDetailsTable(/* parameters unknown */);
    static Bool RemoveSoundDetailsTable(/* parameters unknown */);
    static Bool IsSoundDetailsTableLoaded(/* parameters unknown */);
    EXSoundDetails& SoundDetails();
    void Update();
    s32 SfxVolume();
    s32 MusicVolume();
    // void SetSfxVolume(EXBaseSoundManager*, int, void); // same params as destructor?
    // void SetMusicVolume(EXBaseSoundManager*, int, void); // same params as destructor?
    Bool SfxIsValidRange();
    Bool StartSound();
    // Bool StartSound();
    // Bool StartSound();
    void SfxSetEnvironment();
    s32 SfxNumberOfListeners();
    // void SfxSetReverbDepth(EXBaseSoundManager*, int, void);
    s32 SfxEnvReverbDepth();
    void PreCache();
    void BuildSoundFileList();
    s32 GetXFileFromHash();
    u32 GetFileStatus(int FileHandle) const;
    Bool IsSoundBankLoaded();
    void RegisterWatcherVars();
    void LoadSoundBank();
    void DeloadSoundBank();
    void PreMovieReset();
    void PostMovieReset();
    void StartCutscene();
    void EndCutscene();
    // void SetLanguage(EXBaseSoundManager*, int, void);
    // void SetMode(EXBaseSoundManager*, int, void);
    void SetEnvironment();
    void SetDebugFlags();
    s32 GetLanguage();
    s32 GetMode();
    void FadeSFXDown();
    // void FadeSFXUp(EXBaseSoundManager*, int, void);
    void FadeMusicDown();
    // void FadeMusicUp(EXBaseSoundManager*, int, void);
    s32 GetSFXFadeStatus();
    s32 GetMusicFadeStatus();
    /* vtable[3] */ virtual void AsyncReadFile(XFileHandle* pFile, char* pDestBuffer, u32 Priority,
                                               u32 FileIndex);
    void AsyncReadFile_();
    void AsyncStopFileRead(u32 FileHandle);
    u32 GetDriveActivity() const;
    /* vtable[4] */ virtual void Initialise();
    /* vtable[5] */ virtual void Exit();

    // protected:
    void CommandUpdate(u32 Command);
    void KillSoundPlaying();
    EXSoundHandle* AllocateHandle();
    void RemoveHandle();
    EXSoundHandle* _StartSound();
    // EXSoundHandle* _StartSound();
    // EXSoundHandle* _StartSound();
    void SetVolumeOverRide(EXSoundHandle* pSound, u64 Volume);
    void SetPitchOverRide();
    void SetPositionAndVelocity();
    Bool SfxIsPlaying();
    // void SendCommandBlock(EXBaseSoundManager*, int, void);
    void SendCommand();
    /* vtable[6] */ virtual u32 TransferCommandBlock();
    void End();
    void Initialise2();
    void LoadSoundBank2();
    void UnLoadSoundBank();
    void SFXAddToRequestedList();
    void SFXUpdateRequestedList();
    void StartMusicXFade();
    void Start3D();
    void Remove();
    void SetupListener();
    // void SetNumberOfListeners(EXBaseSoundManager*, int, void);

public:
    EXSoundHandle* Unsafe_StartSound();
    // EXSoundHandle* Unsafe_StartSound();
    // EXSoundHandle* Unsafe_StartSound();
    void Unsafe_SfxSetVolumeOverRide();
    void Unsafe_SfxSetPitchOverRide();
    void Unsafe_SfxKillSoundPlaying();
    Bool Unsafe_SfxIsPlaying();
    void Unsafe_RemoveHandle();
    void Unsafe_SfxSetPositionAndVelocity();
};

#endif // EXSOUNDMANAGER_H
