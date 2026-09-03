#ifndef EXGEOFILE_H
#define EXGEOFILE_H

#include "types.h"

#include "EXRuntimeClass.h"
#include "EXFile.h"

// template <> struct EXRelPtr<EXGeoTextureHeader>
// { // 0x4
// protected:
//     /* 0x0 */ EXRELOFFSET32 m_rPtr;

// public:
//     // EXRelPtr<EXGeoTextureHeader>& operator=();
//     EXRelPtr();
//     // EXRelPtr();
//     EXRELOFFSET32& RelPtr();
//     // EXGeoTextureHeader* operator EXGeoTextureHeader*();
// };

// template <> struct EXGeoCommonArray<EXGeoTextureHeader>
// { // 0x8
// protected:
//     /* 0x0 */ s16 m_ArraySize;
//     /* 0x2 */ s16 m_HashSize;
//     /* 0x4 */ EXRelPtr<EXGeoTextureHeader> m_rpOffset;

// public:
//     EXGeoCommonArray<EXGeoTextureHeader>& operator=();
//     EXGeoCommonArray();
//     EXGeoCommonArray();
//     EXGeoTextureHeader* Data();
//     EXGeoTextureHeader* operator EXGeoTextureHeader*();
//     s32 Size();
//     s32 HashSize();
//     s32 FindIndex();
//     s32 FindIndex();
//     EXGeoTextureHeader* Find();
//     void UpdatePtrs();
//     void OnDelete();
//     void OnSectionDelete();
//     void SetPtrs();
//     void DeletePtrs();
// };

// TODO: Fill this shit out

// struct EXGeoObjectHeader : /* 0x0 */ EXGeoCommonArrayElement<EXGeoCommonObject>
// { // 0x10
// };

struct EXGeoHeader
{ // 0xd4
protected:
    /* 0x00 */ u32 m_Marker;
    // /* 0x04 */ EXHashCode m_HashCode;
    /* 0x08 */ u32 m_Version;
    /* 0x0c */ u32 m_Flags;
    /* 0x10 */ u32 m_Time;
    /* 0x14 */ u32 m_FileSize;
    /* 0x18 */ u32 m_BaseFileSize;
    /* 0x1c */ unsigned int m_Versions[6];
    // /* 0x34 */ EXABSOFFSET32 m_DebugSectionOffset;
    // /* 0x38 */ EXABSOFFSET32 m_DebugSectionEndOffset;
    // /* 0x3c */ EXGeoDebugFile* m_pDebugFile;
    // /* 0x40 */ EXGeoFile* m_pGeoFile;
    /* 0x44 */ u32 m_NumTextures;
    // /* 0x48 */ EXTextureArray* m_pTextureArray;
    // /* 0x4c */ EXGeoFileDataBlock* m_pGeoDataBlock;
    // /* 0x50 */ EXGeoAnimLoadArray* m_pGeoAnimLoadArray;
    // /* 0x54 */ EXGeoCommonArray<EXGeoSectionHeader> m_SectionList;
    // /* 0x5c */ EXGeoCommonArray<EXGeoRefPointerHeader> m_RefPointerList;
    // /* 0x64 */ EXGeoCommonArray<EXGeoEntityHeader> m_EntityList;
    // /* 0x6c */ EXGeoCommonArray<EXGeoAnimHeader> m_AnimList;
    // /* 0x74 */ EXGeoCommonArray<EXGeoAnimSkinHeader> m_AnimSkinList;
    // /* 0x7c */ EXGeoCommonArray<EXGeoScriptHeader> m_ScriptList;
    // /* 0x84 */ EXGeoCommonArray<EXGeoMapHeader> m_MapList;
    // /* 0x8c */ EXGeoCommonArray<EXGeoAnimModeHeader> m_AnimModeList;
    // /* 0x94 */ EXGeoCommonArray<EXGeoAnimSetHeader> m_AnimSetList;
    // /* 0x9c */ EXGeoCommonArray<EXGeoParticleHeader> m_ParticleList;
    // /* 0xa4 */ EXGeoCommonArray<EXGeoSwooshHeader> m_SwooshList;
    // /* 0xac */ EXGeoCommonArray<EXGeoSpreadSheetHeader> m_SpreadSheetList;
    // /* 0xb4 */ EXGeoCommonArray<EXGeoFontHeader> m_FontList;
    // /* 0xbc */ EXGeoCommonArray<EXGeoForceFeedbackHeader> m_ForceFeedbackList;
    // /* 0xc4 */ EXGeoCommonArray<EXGeoTextureHeader> m_TextureList;
    // /* 0xcc */ EXRelArray<short unsigned int> m_TextureUpdateList;
    static float ms_GlobalAnimTexSpeedScale;

public:
    // EXGeoHeader& operator=();
    EXGeoHeader();
    // EXGeoHeader();
    // EXGeoCommonArray<EXGeoSectionHeader>& SectionList();
    // EXGeoSectionHeader* SectionHeader();
    // EXGeoCommonArray<EXGeoRefPointerHeader>& RefPointerList();
    // EXGeoCommonObject* RefPointer();
    // EXGeoObjectArray* GeoObjectArray();
    // EXGeoObjectHeader* GeoObjectHeader();
    u32 GeoObjectStructSize();
    void* GeoObject();
    // EXHashCode GeoObjectHashIndex();
    // EXHashCode GeoObjectHashCode();
    // EXGeoCommonArray<EXGeoEntityHeader>& EntityList();
    // EXGeoEntityHeader* GeoEntityHeader();
    s32 GeoEntityIndex();
    // EXGeoEntity* GeoEntity();
    // EXGeoCommonArray<EXGeoAnimHeader>& AnimList();
    // EXGeoAnimHeader* GeoAnimHeader();
    s32 GeoAnimIndex();
    // EXGeoAnim* GeoAnim();
    // EXGeoCommonArray<EXGeoAnimSkinHeader>& AnimSkinList();
    // EXGeoAnimSkinHeader* GeoAnimSkinHeader();
    s32 GeoAnimSkinIndex();
    // EXGeoAnimSkin* GeoAnimSkin();
    // EXGeoCommonArray<EXGeoScriptHeader>& ScriptList();
    // EXGeoScriptHeader* GeoScriptHeader();
    s32 GeoScriptIndex();
    // EXGeoScript* GeoScript();
    // EXGeoCommonArray<EXGeoMapHeader>& MapList();
    // EXGeoMapHeader* GeoMapHeader();
    s32 GeoMapIndex();
    // EXGeoMap* GeoMap();
    // EXGeoCommonArray<EXGeoTextureHeader>& TextureList();
    // EXGeoTextureHeader* GeoTextureHeader();
    s32 GeoTextureIndex();
    // EXGeoTexture* GeoTexture();
    // EXGeoCommonArray<EXGeoParticleHeader>& ParticleList();
    // EXGeoParticleHeader* GeoParticleHeader();
    s32 GeoParticleIndex();
    // EXGeoParticle* GeoParticle();
    // EXGeoCommonArray<EXGeoSwooshHeader>& SwooshList();
    // EXGeoSwooshHeader* GeoSwooshHeader();
    s32 GeoSwooshIndex();
    // EXGeoSwoosh* GeoSwoosh();
    // EXGeoCommonArray<EXGeoAnimModeHeader>& AnimModeList();
    // EXGeoAnimModeHeader* GeoAnimModeHeader();
    s32 GeoAnimModeIndex();
    // EXGeoAnimMode* GeoAnimMode();
    // EXGeoCommonArray<EXGeoAnimSetHeader>& AnimSetList();
    // EXGeoAnimSetHeader* GeoAnimSetHeader();
    s32 GeoAnimSetIndex();
    // EXGeoAnimSet* GeoAnimSet();
    // EXGeoCommonArray<EXGeoSpreadSheetHeader>& SpreadSheetList();
    // EXGeoSpreadSheetHeader* GeoSpreadSheetHeader();
    s32 GeoSpreadSheetIndex();
    // EXGeoSpreadSheet* GeoSpreadSheet();
    // EXGeoCommonArray<EXGeoFontHeader>& FontList();
    // EXGeoFontHeader* GeoFontHeader();
    s32 GeoFontIndex();
    // EXGeoFont* GeoFont();
    // EXGeoCommonArray<EXGeoForceFeedbackHeader>& ForceFeedbackList();
    // EXGeoForceFeedbackHeader* GeoForceFeedbackHeader();
    s32 GeoForceFeedbackIndex();
    // EXGeoForceFeedback* GeoForceFeedback();
    u32 NumTextures();
    // EXTextureArray& TextureArray();
    // EXTexture* Texture();
    void InitialiseTextureArray();
    void DeloadTextureArray();
    void UpdateTextureArray();
    void AnimateTextureArray();
    // EXGeoFileDataBlock* GeoFileDataBlock();
    // EXGeoAnimLoadArray* GeoAnimLoadArray();
    float AnimTextureSpeedScale();
    void SetAnimTextureSpeedScale();
    static float GlobalAnimTextureSpeedScale(/* parameters unknown */);
    static void SetGlobalAnimTextureSpeedScale(/* parameters unknown */);
    u32* MapZoneSectionList();
    // EXBit128& ZoneFileSectionArray();
    Bool LoadSectionFile();
    Bool DeLoadSectionFile();
    Bool LoadTextSectionFile();
    Bool DeLoadTextSectionFile();
    Bool UpdateSectionFiles();
    Bool UpdateDeloadSectionFiles();
    void DeLoadSectionFiles();
    u32 IsSectionLoaded();
    void* SectionLoadAddr();
    Bool IsSectionGroupLoaded();
    void SectionGroupUsage();
    u32 Marker();
    u32 Version();
    u32 Time();
    u32 Flags();
    u32 FileSize();
    u32 BaseFileSize();
    // EXHashCode HashCode();
    u32 PlatformVersions();
    Bool ValidMarker();
    // EXGeoFile* GeoFile();
    void GetAnimMaxBoundsBox();
    void GetScriptMaxBoundsBox();
    // EXGeoTextItem* FindTextItem();
    void UpdatePtrs();
    void Initialise();
    void Deload();
    void OnDelete();
    void OnSectionDelete();
    Bool LoadDebugFile();
    void DeLoadDebugFile();
    char* DebugFileName();
    u32 DebugFileSize();
    // EXGeoDebugFile* DebugFile();
    // EXGeoDebugHeader* DebugHeader();
    // EXGeoBaseDebug* GetDebug();
    // EXGeoBaseDebug* GetDebug();
    // EXGeoBaseDebug* GetObjectDebug();
    void Debug_OnStats();

protected:
    void _DeLoadSectionFile();
    Bool _DeLoadSectionFiles();
};

struct EXGeoFile : /* 0x00 */ EXFile
{ // 0x2c
    static EXRuntimeClass classEXGeoFile;

protected:
    /* 0x20 */ s16 m_DeloadSubFiles;
    /* 0x22 */ s8 m_DeloadTime;
    /* 0x23 */ Bool m_fForceUpdatePtrs;
    /* 0x24 */ EXGeoHeader* m_pGeoHeader;
    /* 0x28 */ u32 m_CheckCode;
    static Bool m_AutoLoadGroupFiles;
    static Bool m_FailSafeLoadFiles;

public:
    // EXGeoFile& operator=();
    EXGeoFile();
    /* vtable[2] */ virtual ~EXGeoFile();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXGeoFile* CreateObject(/* parameters unknown */);
    // EXGeoFile();
    void Initialise();
    void UpdatePtrs();
    void OnDelete();
    /* vtable[3] */ virtual Bool OnLoad();
    /* vtable[4] */ virtual Bool OnLoaded();
    /* vtable[5] */ virtual Bool OnKill();
    u32 CheckCode();
    void UpdateCheckCode();
    Bool IsLoaded();
    void SetGeoHeader();
    EXGeoHeader* GeoHeader();
    static EXGeoFile* GetGeoFile(/* parameters unknown */);
    static EXGeoFile* LoadGeoFile(/* parameters unknown */);
    // static EXGeoFile* LoadGeoFile(/* parameters unknown */);
    static Bool LoadGeoObjectSectionFile(/* parameters unknown */);
    // static Bool LoadGeoObjectSectionFile(/* parameters unknown */);
    static Bool DeLoadGeoFile(/* parameters unknown */);
    // static Bool DeLoadGeoFile(/* parameters unknown */);
    static Bool AllocCallbackFunc(/* parameters unknown */);
    static void UpdateFiles(s8);
    static void DeloadAllGeoFiles(/* parameters unknown */);
    static void EnableAutoLoadGroupFiles(/* parameters unknown */);
    static Bool AutoLoadGroupFiles(/* parameters unknown */);
    static void EnableFailSafeLoadGeoFiles(/* parameters unknown */);

protected:
    static EXGeoFile* FailSafeLoadGeoFile(/* parameters unknown */);
    void SetDeloadTime();
    s8 DeloadTime();
    s16& DeloadSubFiles();
    void SetForceUpdatePtrs();
    Bool ForceUpdatePtrs();

private:
    Bool _LoadFile();
    Bool _DeLoadFile();
    void Update();
    void AddFileToUpdateList();
    static EXGeoFile* _GetGeoFile(/* parameters unknown */);
};

struct EXGeoBaseRefObject
{ // 0x8
protected:
    /* 0x0 */ EXGeoFile* m_pGeoFile;
    /* 0x4 */ EXHashCode m_HashRef;

public:
    // EXGeoBaseRefObject& operator=();
    EXGeoBaseRefObject();
    // EXGeoBaseRefObject();
    EXGeoFile* GeoFile();
    EXHashCode HashRef();
    char* DebugGeoName();
    char* DebugRefName();
};

struct EXGeoComplexRefObject : /* 0x0 */ EXGeoBaseRefObject
{ // 0x10
protected:
    /* 0x8 */ u32 m_CheckCode;
    /* 0xc */ void* m_pAddress;

public:
    // EXGeoComplexRefObject& operator=();
    EXGeoComplexRefObject();

protected:
    void Invalidate();

public:
    // EXGeoComplexRefObject();
    // EXGeoObjectHeader* GeoObjectHeader();
    // EXGeoObjectHeader* GeoObjectHeader();
    // EXGeoObjectHeader* GeoObjectHeader();
    // EXGeoObject* GeoObject();
    // EXGeoObject* GeoObject();
    // EXGeoAnimHeader* GeoAnimHeader();
    // EXGeoAnimHeader* GeoAnimHeader();
    // EXGeoAnimHeader* GeoAnimHeader();
    // EXGeoAnim* GeoAnim();
    // EXGeoAnim* GeoAnim();
    // EXGeoAnimSkinHeader* GeoAnimSkinHeader();
    // EXGeoAnimSkinHeader* GeoAnimSkinHeader();
    // EXGeoAnimSkinHeader* GeoAnimSkinHeader();
    // EXGeoAnimSkin* GeoAnimSkin();
    // EXGeoAnimSkin* GeoAnimSkin();
    // EXGeoEntityHeader* GeoEntityHeader();
    // EXGeoEntityHeader* GeoEntityHeader();
    // EXGeoEntityHeader* GeoEntityHeader();
    // EXGeoEntity* GeoEntity();
    // EXGeoEntity* GeoEntity();
    // EXGeoScriptHeader* GeoScriptHeader();
    // EXGeoScriptHeader* GeoScriptHeader();
    // EXGeoScriptHeader* GeoScriptHeader();
    // EXGeoScript* GeoScript();
    // EXGeoScript* GeoScript();
    // EXGeoSwooshHeader* GeoSwooshHeader();
    // EXGeoSwooshHeader* GeoSwooshHeader();
    // EXGeoSwooshHeader* GeoSwooshHeader();
    // EXGeoSwoosh* GeoSwoosh();
    // EXGeoSwoosh* GeoSwoosh();
    // EXGeoParticleHeader* GeoParticleHeader();
    // EXGeoParticleHeader* GeoParticleHeader();
    // EXGeoParticleHeader* GeoParticleHeader();
    // EXGeoParticle* GeoParticle();
    // EXGeoParticle* GeoParticle();
    // void Set();
    // void Set();
    // void Set();
    void SetGeoFile();
    void SetHashRef();
};

#endif // EXGEOFILE_H
