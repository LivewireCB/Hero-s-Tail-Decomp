#ifndef EXITEMRENDER_ANIM_H
#define EXITEMRENDER_ANIM_H

#include "types.h"

#include "EXList.h"
#include "EXMatrix.h"
#include "EXVector.h"
#include "EXItemRender.h"

// TODO: FIX ALL STRUCTS HERE

struct EXItemRender_SkinMorph
{ // 0x4
    /* 0x0 */ float Weight;
};

struct EXItemRender_SkinAnimSectionTemp
{ // 0x4
    // /* 0x0 */ EXItemRender_SkinAnimSection* pSection;
};

// struct EXFixedArray<EXGeoSkinAnimFrame*, 4>
// { // 0x10
//     /* 0x0 */ EXGeoSkinAnimFrame* m_Data[4];

//     EXFixedArray<EXGeoSkinAnimFrame*, 4>& operator=();
//     EXFixedArray();
//     EXFixedArray();
//     size_t Size();
//     size_t GetUpperBound();
//     EXGeoSkinAnimFrame*& ElementAt();
//     EXGeoSkinAnimFrame* GetAt();
//     void SetAt();
//     EXGeoSkinAnimFrame** GetData();
//     EXGeoSkinAnimFrame** GetData();
//     EXGeoSkinAnimFrame** operator EXGeoSkinAnimFrame**();
//     EXGeoSkinAnimFrame** operator EXGeoSkinAnimFrame**();
// };

// struct EXFixedArray<EXGeoAnim*, 4>
// { // 0x10
//     /* 0x0 */ EXGeoAnim* m_Data[4];

//     EXFixedArray<EXGeoAnim*, 4>& operator=();
//     EXFixedArray();
//     EXFixedArray();
//     size_t Size();
//     size_t GetUpperBound();
//     EXGeoAnim*& ElementAt();
//     EXGeoAnim* GetAt();
//     void SetAt();
//     EXGeoAnim** GetData();
//     EXGeoAnim** GetData();
//     EXGeoAnim** operator EXGeoAnim**();
//     EXGeoAnim** operator EXGeoAnim**();
// };

// struct EXItemRender_SkinAnimInfo
// { // 0x64
//     /* 0x00 */ EXFixedArray<EXGeoSkinAnimFrame*, 4> pMotionFrame;
//     /* 0x10 */ EXFixedArray<EXGeoAnim*, 4> pMotionGeoAnim;
//     /* 0x20 */ EXFixedArray<EXGeoSkinAnimFrame*, 4> pMorphFrame;
//     /* 0x30 */ EXFixedArray<EXGeoAnim*, 4> pMorphGeoAnim;
//     /* 0x40 */ EXFixedArray<float, 2> WeightTbl;
//     /* 0x48 */ EXFixedArray<float, 2> BlendToPrev;
//     /* 0x50 */ EXGeoComplexRefObject m_SkinRefObjectData;
//     /* 0x60 */ EXGeoComplexRefObject* m_pSkinRefObject;
// };

struct EXItemRender_SkinAnimSection : /* 0x00 */ EXDListItem
{ // 0x50
protected:
    /* 0x08 */ u16 m_SectionIndex;
    /* 0x0a */ u16 m_ParentIndex;
    /* 0x0c */ EXMatrix* m_pmtx;
    /* 0x10 */ EXDList m_Children;
    /* 0x20 */ MXVector m_Pos;
    // /* 0x30 */ EXQuaternion m_QRot;
    // /* 0x40 */ EXBit128 m_SkinBits;

public:
    // EXItemRender_SkinAnimSection& operator=();
    EXItemRender_SkinAnimSection();
    // EXItemRender_SkinAnimSection();
    void Initialise();
    EXVector Position();
    // EXQuaternion Rotation();
    void SetPosition();
    void SetRotation();
    EXMatrix& mtx();
    u32 SectionIndex();
    u32 ParentIndex();
    void SetParentIndex();
    EXItemRender_SkinAnimSection* ChildLinks();
};

struct EXItemRender_SkinInfo
{ // 0x60
    // /* 0x00 */ EXBit128 m_RenderStateBits;
    // /* 0x10 */ EXBit128 m_SkinBits;
    // /* 0x20 */ EXGDiSkinDataArray m_GDiArray;
    // /* 0x2c */ EXGeoComplexRefObject m_CalcSkinRefObject;
    // /* 0x3c */ EXGeoComplexRefObject m_DrawSkinRefObject;
    /* 0x4c */ u8* m_pSkinRemap;
    /* 0x50 */ u32 m_LodFrameCount;
    /* 0x54 */ u8 m_CurrentLod;

    // EXItemRender_SkinInfo& operator=();
    EXItemRender_SkinInfo();
    EXItemRender_SkinInfo(EXItemRender_SkinInfo*, int, void);
    // EXItemRender_SkinInfo();
    void Initialise();
    void RemoveSkin();
};

struct EXItemRender_SkinAnim : /* 0x000 */ EXItemRender
{ // 0x160
    static EXRuntimeClass classEXItemRender_SkinAnim;

protected:
    /* 0x00c */ EXFlag8 m_fUpdateSkins;
    /* 0x00d */ EXFlag8 m_fUpdateNoRenders;
    /* 0x00e */ EXFlag8 m_fValidSkins;
    /* 0x00f */ EXFlag8 m_fActiveSkins;
    /* 0x010 */ s8 m_fValidMtxArray;
    /* 0x011 */ Bool m_fSkeletonOwner;
    /* 0x012 */ u8 m_MinLod;
    /* 0x013 */ u8 m_MaxLod;
    /* 0x014 */ unsigned char m_SkinRemapIndex[4];
    // /* 0x018 */ EXGeoComplexRefObject m_SkelRefObject;
    /* 0x028 */ void* m_pSectionData;
    /* 0x02c */ s32 m_NumSections;
    /* 0x030 */ EXDList m_SectionsList;
    /* 0x038 */ EXMatrix* m_pSectionMtxArray;
    // /* 0x03c */ EXAnimLodDetails* m_pActiveLodDetails;
    /* 0x040 */ s32 m_NumDeformers;
    /* 0x044 */ EXItemRender_SkinMorph* m_pMorphDeformers;
    /* 0x048 */ EXItemRender_SkinAnim* m_pCloneSkin;
    /* 0x04c */ u32 m_ActiveSkin;
    /* 0x050 */ EXItemRender_SkinInfo* m_pActiveSkinInfo;
    // /* 0x054 */ EXGeoComplexRefObject m_SkinRefObject[4];
    /* 0x094 */ EXItemRender_SkinInfo* m_pSkinInfo[4];
    /* 0x0b0 */ EXItemRender_SkinInfo m_RenderSkin;
    // /* 0x110 */ EXRenderInfo m_RenderInfo;
    // /* 0x140 */ EXu32Array m_RenderStateArray;
    // /* 0x150 */ EXBit128 m_SkinCalcBits;

public:
    // EXItemRender_SkinAnim& operator=();
    EXItemRender_SkinAnim();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXItemRender_SkinAnim* CreateObject(/* parameters unknown */);
    // EXItemRender_SkinAnim();
    // /* vtable[2] */ virtual EXItemRender_SkinAnim(EXItemRender_SkinAnim*, int, void);
    Bool Create();
    // EXGeoComplexRefObject& SkelRefObject();
    void SetSkinRefObject();
    // void SetSkinRefObject();
    // void SetSkinRefObject();
    void SetShadowRefObject();
    void SetCollisionRefObject();
    void SetReflectionRefObject();
    // EXGeoComplexRefObject& SkinRefObject();
    // EXGeoComplexRefObject& ShadowRefObject();
    // EXGeoComplexRefObject& CollisionRefObject();
    // EXGeoComplexRefObject& ReflectionRefObject();
    // EXGeoComplexRefObject& DrawSkinRefObject();
    EXItemRender_SkinAnim* AddCloneSkin();
    EXItemRender_SkinAnim* FindCloneSkin();
    void DeleteCloneSkin();
    // EXGeoAnimSkinHeader* UpdateSkinInfomation();
    void CalculateSkinUsageBits();
    // EXBit128& SkinCalcBits();
    // EXRenderInfo& RenderInfo();
    void SetUpdateSkin();
    void SetUpdateNoRender();
    void Invalidate();
    void SetRenderState();
    void BuildEntityInfoArray();
    int SectionCount();
    EXItemRender_SkinAnimSection* SectionArray();
    int DefomerCount();
    EXItemRender_SkinMorph* MorphDeformers();
    EXMatrix* MtxArray();
    EXMatrix* TempMtxArray();
    u8* RemapTable();
    void SetLodMin();
    void SetLodMax();
    // EXAnimLodDetails* ActiveLodDetails();
    void SetActiveLodDetails();
    void ApplyFunction();
    // EXGeoBaseEntity* FindAttachedEntity();
    void CalcChildMatrix();
    void CalcChildMatrixLimited();
    void RenderSkin();
    Bool BuildHierData_Motion();
    Bool BuildHierData2_Motion();
    void BuildHierData_Morph();
    void BuildHierData2_Morph();
    void BuildHierData_ModifyMorph();
    void InitBlendStack();
    void DoRender();
    void DoEntityScoop();
    void UpdateRenderEnd();
    EXItemRender_SkinAnimSection* GetAnimBoneSection();
    // EXItemRender_SkinAnimSection* GetAnimBoneSection();
    EXItemRender_SkinAnimSection* GetSectionParent();
    void ListSections();
    void* GetDatum_SkelDatum();
    // void GetDatum_SkelDatum();
    void* GetDatum_AnimBoneDatum();
    // void* GetDatum_AnimBoneDatum();

private:
    EXMatrix GetDatum_CalcMatrixSP();
    EXMatrix GetDatum_CalcMatrix();
    // EXMatrix GetDatum_CalcMatrix();
    Bool BuildSkin();
    Bool AssignSkin();
    void ApplySkin();
    void RemoveSkin();
    void UpdateSkinTables();
    Bool CreateClone();
    void CalcMatrix();
    void CalcSectionMatrix();
    // void CalcSectionMatrix();
    void CalcSectionMatrixLimited();
    void BuildSkinGDiArray();
    void BuildSkinRemapTable();
    void BuildSkinRenderStateFlags();
    void BuildRemapTable();
    EXItemRender_SkinInfo* SetActiveSkin();
};

#endif // EXITEMRENDER_ANIM_H
