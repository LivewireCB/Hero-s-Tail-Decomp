#ifndef EXITEMANIMATOR_H
#define EXITEMANIMATOR_H

#include "types.h"

#include "EXGeoCommon.h"
#include "EXItem.h"
#include "EXRuntimeClass.h"

struct EXItemAnimator : /* 0x000 */ EXPlacementItem
{ // 0x110
    static EXRuntimeClass classEXItemAnimator;
    static void* m_pNullDatumPtr;

protected:
    /* 0x100 */ float m_rFrameRateMult;
    /* 0x104 */ float m_rObjectFrame;
    /* 0x108 */ Bool m_AllocatorCreated;

public:
    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

    EXItemAnimator();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[2] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXItemAnimator* CreateObject(/* parameters unknown */);
    /* vtable[3] */ virtual char* TypeName();
    /* vtable[4] */ virtual int Size();
    static EXItemAnimator* NewItem(/* parameters unknown */);
    // EXItemAnimator();
    /* vtable[1] */ virtual ~EXItemAnimator();
    // EXItemHandler* GetOwnerHandler();
    EXItem* GetOwnerItem();
    EXPlacementItem* GetPositionItem();
    static EXItemAnimator* CreateFrom(/* parameters unknown */);
    static Bool SetCreateFrom(/* parameters unknown */);
    static EXRuntimeClass* RuntimeClassFrom(/* parameters unknown */);
    // static AnimatorCF GetAnimatorCF(/* parameters unknown */);
    /* vtable[7] */ virtual Bool Initialise();
    void SetFrameRateMult();
    float FrameRateMult();
    void SetFrameRate60();
    float FrameRate60();
    /* vtable[8] */ virtual float ObjectTime();
    /* vtable[9] */ virtual void SetObjectTime();
    /* vtable[10] */ virtual void UpdateObjectTime();
    EXItemAnimator* GetAnimator();
    // EXItemAnimator* GetAnimator();
    // EXItemAnimator* GetAnimator();
    void AddAnimator();
    void RemoveAnimator();
    void DeleteAnimator();
    /* vtable[11] */ virtual void EnableParticleSystems();
    /* vtable[12] */ virtual void* GetDatum();
    /* vtable[13] */ virtual void GetDatum(s64 /* grab correct params from release_functions */);
    /* vtable[14] */ virtual void* GetNearestDatum();
    void* GetDatum_ChildLink();
    // void GetDatum_ChildLink();
    void* GetNearestDatum_ChildLink();
    /* vtable[15] */ virtual Bool DoGrabPoint();
    /* vtable[16] */ virtual Bool DoGrabPoint(s64 /* grab correct params from release_functions */);
    /* vtable[17] */ virtual void DoRayCast();
    /* vtable[18] */ virtual void DoShadowCast();
    /* vtable[19] */ virtual void DoEntityScoop();
    Bool DoGrabPoint_ChildLink();
    void DoRayCast_ChildLink();
    void DoShadowCast_ChildLink();
    void DoEntityScoop_ChildLink();
    Bool GetBoundsBox();
    void UpdateBoundsBox();
    /* vtable[20] */ virtual void SetRenderState();
    /* vtable[21] */ virtual void SetLodMin();
    /* vtable[22] */ virtual void SetLodMax();
    /* vtable[23] */ virtual void ApplyFunction();
    /* vtable[24] */ virtual void BuildEntityInfoArray();
    /* vtable[6] */ virtual u32 DoRender();
    u32 DoItemRender();
    void DoItemUpdate();
    /* vtable[25] */ virtual EXGeoCommonObject* GetGeoObject();

protected:
    void EnableAllocatorCreated();
    Bool AllocatorCreated();
    /* vtable[26] */ virtual Bool _GetBoundsBox();
    void ApplyMatrixBoundsBox();
};

#endif // EXITEMANIMATOR_H
