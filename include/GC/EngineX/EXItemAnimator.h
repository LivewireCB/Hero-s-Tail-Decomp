#ifndef EXITEMANIMATOR_H
#define EXITEMANIMATOR_H

#include "types.h"

#include "EXAllocator.h"
#include "EXBounds.h"
#include "EXDatumTemp.h"
#include "EXGeoCommon.h"
#include "EXItem.h"
#include "EXMatrix.h"
#include "EXRuntimeClass.h"

struct EXItemAnimator;
struct EXGrabPointTemp;
struct EXGrabPointArrayTemp;
struct EXRayCastTemp;
struct EXShadowTemp;
struct EXCollisionScoopTemp;
struct EXGeoEntity_InfoArray;
struct _EXItemAnimatorAllocator;

typedef EXItemAnimator* EXCFCALL();
typedef u64 EXANIMATORCALLBACK(EXItemAnimator* pAnimator, void* pData);

enum AnimatorCF
{
    CF_None = -1,
    CF_Script = 0,
    CF_Anim = 1,
    CF_Entity = 2,
    CF_Map = 3,
    CF_Particle = 4,
    CF_Sound = 5,
    CF_Light = 6
};

struct AnimatorCFEntry
{
    /* 0x0 */ EXRuntimeClass* pRunTime;
    /* 0x4 */ EXCFCALL* pNewItemCall;
};

struct EXItemAnimator : /* 0x000 */ EXPlacementItem
{ // 0x110
    static EXRuntimeClass classEXItemAnimator;
    static void* m_pNullDatumPtr;

protected:
    /* 0x100 */ float m_rFrameRateMult;
    /* 0x104 */ float m_rObjectFrame;
    /* 0x108 */ Bool m_AllocatorCreated;
    /* 0x109 */ u8 m_Unk109;

    friend struct EXItemAnimatorQueue;

public:
    EXItemAnimator();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    static EXItemAnimator* CreateObject(/* parameters unknown */);
    /* vtable[3] */ virtual char* TypeName() const;
    /* vtable[4] */ virtual int Size() const;
    static EXItemAnimator* NewItem(/* parameters unknown */);
    // EXItemAnimator();
    /* vtable[1] */ virtual ~EXItemAnimator();
    EXItemHandler* GetOwnerHandler() const;
    EXItem* GetOwnerItem() const;
    EXPlacementItem* GetPositionItem();
    static EXItemAnimator* CreateFrom(EXGeoFile* pGeoFile, EXHashCode HashRef);
    static Bool SetCreateFrom(/* parameters unknown */);
    static EXRuntimeClass* RuntimeClassFrom(/* parameters unknown */);
    // static AnimatorCF GetAnimatorCF(/* parameters unknown */);
    /* vtable[7] */ virtual Bool Initialise(EXGeoFile* pGeoFile, EXHashCode RefHash);
    void SetFrameRateMult();
    float FrameRateMult();
    void SetFrameRate60(float f);
    float FrameRate60() const;
    /* vtable[8] */ virtual float ObjectTime() const;
    /* vtable[9] */ virtual void SetObjectTime(float rObjectTime);
    /* vtable[10] */ virtual void UpdateObjectTime(float rObjectTime);
    EXItemAnimator* GetAnimator();
    // EXItemAnimator* GetAnimator();
    // EXItemAnimator* GetAnimator();
    void AddAnimator(EXItemAnimator* p);
    void RemoveAnimator();
    void DeleteAnimator();
    /* vtable[11] */ virtual void EnableParticleSystems(Bool Enable) const;
    /* vtable[12] */ virtual void* GetDatum(EXHashCode DatumHashRef, EXDatumTemp& Datum, u64 Flags, void*& pPrevPtr);
    /* vtable[13] */ virtual void GetDatum(EXHashCode DatumHashRef, EXDatumTempArray& DatumArray, u64 Flags);
    /* vtable[14] */ virtual void* GetNearestDatum(EXVector& vctPos, EXDatumTemp& Datum, u64 Flags);
    void* GetDatum_ChildLink(EXHashCode DatumHashRef, EXDatumTemp& Datum, u64 Flags, void*& pPrevPtr) const;
    void GetDatum_ChildLink(EXHashCode DatumHashRef, EXDatumTempArray& DatumArray, u64 Flags) const;
    void* GetNearestDatum_ChildLink(EXVector& vctPos, EXDatumTemp& Datum, u64 Flags) const;
    /* vtable[15] */ virtual Bool DoGrabPoint(EXMatrix& mtxIn, EXGrabPointTemp& gpt, u64 CtrlFlags);
    /* vtable[16] */ virtual Bool DoGrabPoint(EXMatrix& mtxIn, EXGrabPointArrayTemp& gpat, u64 CtrlFlags);
    /* vtable[17] */ virtual void DoRayCast(EXMatrix& mtxIn, EXRayCastTemp& rct, u64 CtrlFlags);
    /* vtable[18] */ virtual void DoShadowCast(EXShadowTemp& st);
    /* vtable[19] */ virtual void DoEntityScoop(EXMatrix& mtxIn, EXCollisionScoopTemp& cst, u64 CtrlFlags);
    Bool DoGrabPoint_ChildLink();
    void DoRayCast_ChildLink();
    void DoShadowCast_ChildLink();
    void DoEntityScoop_ChildLink(EXMatrix& mtxIn, EXCollisionScoopTemp& cst, u64 CtrlFlags) const;
    Bool GetBoundsBox(EXBoundsBox& Bounds, u64 Flags);
    void UpdateBoundsBox(Bool fRebuild);
    /* vtable[20] */ virtual void SetRenderState(EXHashCode HashRef, Bool State);
    /* vtable[21] */ virtual void SetLodMin(u64 nMinLod);
    /* vtable[22] */ virtual void SetLodMax(u64 nMaxLod);
    /* vtable[23] */ virtual void ApplyFunction(EXANIMATORCALLBACK* pApplyFunc, void* pData);
    /* vtable[24] */ virtual void BuildEntityInfoArray(EXMatrix& mtxIn, EXGeoEntity_InfoArray& InfoArray, Bool fFlag);
    /* vtable[6] */ virtual u32 DoRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo, u64 CtrlFlags);
    u32 DoItemRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo);
    void DoItemUpdate();
    /* vtable[25] */ virtual EXGeoCommonObject* GetGeoObject() const;

protected:
    void EnableAllocatorCreated();
    Bool AllocatorCreated();
    /* vtable[26] */ virtual Bool _GetBoundsBox(EXBoundsBox& Bounds, u64 Flags);
    void ApplyMatrixBoundsBox(EXBoundsBox& InBounds, EXBoundsBox& Bounds, u64 Flags) const;
};

struct EXItemAnimatorQueue : /* 0x00 */ EXAllocator<_EXItemAnimatorAllocator>
{ // 0x14
    EXItemAnimatorQueue()
        : EXAllocator<_EXItemAnimatorAllocator>(16)
    {
    }
    static EXItemAnimator* Allocate(EXHashCode HashRef, EXItemAnimator* pAnimator);
    static void Release(EXItemAnimator* pAnimator);
};

#endif // EXITEMANIMATOR_H
