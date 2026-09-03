#ifndef EXITEM_H
#define EXITEM_H

#include "types.h"

#include "EXBounds.h"
#include "EXFlagTemplate.h"
#include "EXList.h"
#include "EXRenderEnv.h"
#include "EXRuntimeClass.h"
#include "EXMatrix.h"
#include "EXVector.h"
#include "EXGeoFile.h"

struct EXItemPhysics;

struct EXBaseItem : /* 0x00 */ EXDListItem
{ // 0x1c

    /* 0x08 */ EXBaseItem* m_pOwner;
    /* 0x0c */ EXFlag16 m_ItemFlags;
    /* 0x0e */ s16 m_pad0;
    /* 0x10 */ EXDList m_Nodes;

    // /* 0x18 */ __vtbl_ptr_type* vf8249;

    // EXBaseItem& operator=();
    EXBaseItem();
    // EXBaseItem();
    /* vtable[1] */ virtual ~EXBaseItem();
    EXDList& Nodes();
    void SetOwner();
    EXBaseItem* GetOwner();
    EXBaseItem* GetBaseOwner() const;
};

struct EXPlacementItem : /* 0x00 */ EXBaseItem
{ // 0x100
    static EXRuntimeClass classEXPlacementItem;

protected:
    /* 0x1c */ EXGeoComplexRefObject m_GeoRefObject;
    /* 0x30 */ EXBoundsBox m_BoundsBox;
    /* 0x50 */ EXRenderInfo m_RenderInfo;
    /* 0x80 */ EXFlag8 m_RenderFlags;
    /* 0x81 */ EXFlag8 m_RenderInfoFlags;
    /* 0x82 */ Bool m_ValidMtx;
    /* 0x83:0 */ u8 m_ItemLock : 1;
    /* 0x83:1 */ u8 m_ValidBounds : 1;
    /* 0x83:2 */ u8 m_HasMtx : 1;
    /* 0x83:3 */ u8 m_bitpad : 5;
    /* 0x84 */ EXRotOrder m_RotOrder;
    /* 0x88 */ EXMatrix* m_pmtx;
    /* 0x90 */ EXMatrix m_mtx;
    /* 0xd0 */ EXVector m_Position;
    /* 0xe0 */ EXVector m_Rotation;
    /* 0xf0 */ EXVector m_Scale;

public:
    // EXPlacementItem& operator=();
    EXPlacementItem();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXPlacementItem* CreateObject(/* parameters unknown */);
    /* vtable[3] */ virtual char* TypeName();
    /* vtable[4] */ virtual int Size();
    static EXPlacementItem* NewItem(/* parameters unknown */);
    // EXPlacementItem();
    /* vtable[1] */ virtual ~EXPlacementItem();
    void Invalidate();
    // void Invalidate();
    Bool ValidMtx();
    u8 ValidBounds();
    Bool HasMtx();
    EXMatrix& mtx();
    void SetRemoteMatrix();
    // void SetRemoteMatrix();
    EXMatrix* RemoteMatrix();
    void SetPosition();
    void SetRotation();
    void SetScale();
    void SetMatrix();
    EXVector& Position();
    EXVector& Rotation();
    EXVector& Scale();
    void SetBoundsBox();
    // EXBoundsBox& BoundsBox();
    void SetRotOrder();
    // EXRotOrder RotOrder();
    EXFlag8& RenderFlags();
    // EXFlag8& RenderFlags();
    EXFlag16& ItemFlags();
    // EXFlag16& ItemFlags();
    void SetHasRender();
    void ClrHasRender();
    void SetGeoFile();
    void SetRefObject();
    // EXGeoFile* GeoFile();
    // EXHashCode RefObject();
    // EXGeoComplexRefObject& GeoRefObject();
    // EXRenderInfo& RenderInfo();
    // EXRenderInfo& RenderInfo();
    // EXExtRenderInfo* GetExtRenderInfo();
    // EXTexSwapInfo* SetTexSwapInfo();
    void CalcMatrix();
    // EXMatrix& CalcMatrix_InPlace();
    // EXMatrix& CalcMatrix_InPlaceParent();
    void UpdateNodes();
    u32 RenderNodes();
    /* vtable[5] */ virtual void DoUpdate();
    /* vtable[6] */ virtual u32 DoRender();

protected:
    void _UpdateNodes();
    static u32 _RenderNodes(/* parameters unknown */);
    void CalcMatrix_Vap();

private:
    void CalcMatrix_Remote();
    void CalcMatrix_Scale();
};

struct EXItem : /* 0x000 */ EXPlacementItem
{ // 0x170
    static EXRuntimeClass classEXItem;

protected:
    /* 0x100 */ u32 m_GroupFlags;
    /* 0x104 */ EXODListItem m_ItemGroups[5];
    /* 0x140 */ EXODListItem* m_UserItemGroups;
    /* 0x144 */ EXDList m_Animator;
    // /* 0x14c */ EXItemHandler* m_pItemHandler;
    /* 0x150 */ EXItemPhysics* m_pItemPhysics;
    // /* 0x154 */ EXBaseTrigger* m_pTrigger;
    /* 0x158 */ EXItem* m_pXItemOwner;
    // /* 0x15c */ EXMapOn m_MapOn;
    /* 0x15e */ u16 m_PortalOn;
    /* 0x160 */ u8 m_ClipType;
    /* 0x161 */ u8 m_ClipFlags;
    /* 0x162 */ u8 m_ListSortValue;
    /* 0x164 */ u32 m_UserValue;

public:
    // EXItem& operator=();
    EXItem();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXItem* CreateObject(/* parameters unknown */);
    /* vtable[3] */ virtual char* TypeName();
    /* vtable[4] */ virtual int Size();
    static EXItem* NewItem(/* parameters unknown */);
    /* vtable[1] */ virtual ~EXItem();
    EXODListItem& ItemGroup();
    void UpdateGroups();
    void UpdateGroupsTail();
    u32 GroupFlags();
    EXDList& AnimatorList();
    // EXItemAnimator* GetAnimator();
    // EXItemAnimator* GetAnimator();
    // EXItemAnimator* GetAnimator();
    void AddAnimator();
    void RemoveAnimator();
    void DeleteAnimator();
    void SetItemHandler();
    // EXItemHandler* ItemHandler();
    void SetItemPhysics();
    // EXItemPhysics* ItemPhysics();
    void SetTrigger();
    // EXBaseTrigger* Trigger();
    void SetXItemOwner();
    EXItem* GetXItemOwner();
    void EnableParticleSystems();
    void SetMapOn();
    // EXMapOn MapOn();
    void SetPortalOn();
    s16 PortalOn();
    void SetClipType();
    u8 ClipType();
    void SetClipFlags();
    u8 ClipFlags();
    void SetUserValue();
    u32 UserValue();
    void SetListSortValue();
    u32 ListSortValue();
    void DoItemPreRender();
    void DoItemUpdate_Animators();
    void* GetAnimatorDatum();
    // void GetAnimatorDatum();
    Bool GetAnimatorBoundsBox();
    // Bool GetAnimatorBoundsBox();
    void SetAnimatorRenderState();
    void SetAnimatorLodRange();
    void SetAnimatorMinLod();
    void SetAnimatorMaxLod();
    /* vtable[7] */ virtual void AnimatorApplyFunction();
    /* vtable[8] */ virtual void DoItemUpdate();
    /* vtable[9] */ virtual void DoItemPhysics();
    /* vtable[10] */ virtual u32 DoItemRender();
    /* vtable[11] */ virtual void DoItemCollisionScoop(s64 /* grab from release functions */);
    /* vtable[12] */ virtual void DoItemCollisionScoop();
    /* vtable[13] */ virtual void DoItemGrabPoint();
    /* vtable[14] */ virtual void DoItemGrabPoint(s64 /* grab from release functions */);
    /* vtable[15] */ virtual void DoItemRayCast();
    /* vtable[16] */ virtual void DoItemShadowCast();
};

#endif // EXITEM_H
