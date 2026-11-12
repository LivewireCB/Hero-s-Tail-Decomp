#include "EngineX/EXItemAnimator.h"

#include "EngineX/EXApp.h"
#include "EngineX/EXItemAnimator_Anim.h"
#include "EngineX/EXItemAnimator_DynLight.h"
#include "EngineX/EXItemAnimator_Entity.h"
#include "EngineX/EXItemAnimator_Particle.h"
#include "EngineX/EXItemAnimator_Script.h"
#include "EngineX/EXItemAnimator_Sound.h"
#include "EngineX/EXMemoryManager.h"

extern u8 g_ForceLod;
extern u8 g_ForceLod2;
extern AnimatorCFEntry AnimatorCFTable[7];

EXItemAnimatorQueue AnimatorAllocatorQueue;

EXItemAnimator* EXItemAnimator::CreateObject()
{
    return new EXItemAnimator();
}

EXItemAnimator::EXItemAnimator()
{
    m_Unk109 = 1;
    m_rFrameRateMult = 1.0f;
    m_rObjectFrame = 0.0f;
    m_AllocatorCreated = false;
}

EXItemAnimator::~EXItemAnimator()
{
    if (m_AllocatorCreated != 0)
    {
        do
        {
            // deadstripped
        } while (true);
    }
}

EXItemAnimator* EXItemAnimator::CreateFrom(EXGeoFile* pGeoFile, EXHashCode HashRef)
{
    if (pGeoFile->GeoHeader())
    {
        AnimatorCF CFType = CF_None;

        switch ((HashRef >> 24) & 0x7f)
        {
        case 4:
            CFType = CF_Script;
            break;
        case 3:
            CFType = CF_Anim;
            break;
        case 2:
            CFType = CF_Entity;
            break;
        case 5:
            CFType = CF_Map;
            break;
        case 0x11:
            CFType = CF_Particle;
            break;
        case 0x1a:
            CFType = CF_Sound;
            break;
        case 0x1b:
            CFType = CF_Sound;
            break;
        case 0x13:
            CFType = CF_Light;
            break;
        }

        if (CFType != CF_None)
        {
            EXCFCALL* pNewItemCall = AnimatorCFTable[CFType].pNewItemCall;

            if (pNewItemCall)
            {
                EXItemAnimator* pAnimator = pNewItemCall();

                if (pAnimator)
                {
                    if (pAnimator->Initialise(pGeoFile, HashRef))
                    {
                        if (g_ForceLod)
                        {
                            pAnimator->m_Unk109 = 0;
                        }

                        if (g_ForceLod2)
                        {
                            pAnimator->m_Unk109 = 0;
                        }

                        return pAnimator;
                    }

                    delete pAnimator;
                }
            }
        }
    }

    return 0;
}

EXItemHandler* EXItemAnimator::GetOwnerHandler() const
{
    EXItemHandler* pHandler = 0;
    EXItem* pOwnerItem = (EXItem*)GetOwner();

    while (pOwnerItem)
    {
        if (pOwnerItem->IsKindOf(&EXItem::classEXItem))
        {
            pHandler = pOwnerItem->ItemHandler();

            if (pHandler)
            {
                break;
            }
            else
            {
                pOwnerItem = (EXItem*)pOwnerItem->GetOwner();
            }
        }
        else
        {
            pOwnerItem = (EXItem*)pOwnerItem->GetOwner();
        }
    }

    return pHandler;
}

EXItem* EXItemAnimator::GetOwnerItem() const
{
    EXPlacementItem* pOwnerItem = (EXPlacementItem*)GetOwner();

    while (pOwnerItem)
    {
        if (pOwnerItem->IsKindOf(&EXItem::classEXItem))
        {
            break;
        }

        pOwnerItem = (EXPlacementItem*)pOwnerItem->GetOwner();
    }

    return (EXItem*)pOwnerItem;
}

void EXItemAnimator::AddAnimator(EXItemAnimator* p)
{
    if (p == this)
    {
        do
        {
            // deadstripped
        } while (true);
    }

    p->m_ValidMtx = false;
    p->m_pOwner = this;

    m_Nodes.AddTail(p);
}

void* EXItemAnimator::GetDatum(EXHashCode DatumHashRef, EXDatumTemp& Datum, u64 Flags, void*& pPrevPtr)
{
    if (Flags & 0x80)
    {
        GetDatum_ChildLink(DatumHashRef, Datum, Flags, pPrevPtr);
    }

    return 0;
}

void* EXItemAnimator::GetDatum_ChildLink(EXHashCode DatumHashRef, EXDatumTemp& Datum, u64 Flags, void*& pPrevPtr) const
{
    for (EXItemAnimator* pChild = (EXItemAnimator*)m_Nodes.Head(); pChild; pChild = (EXItemAnimator*)pChild->Next())
    {
        void* pRetPtr = pChild->GetDatum(DatumHashRef, Datum, Flags, pPrevPtr);

        if (pRetPtr)
        {
            return pRetPtr;
        }
    }

    return 0;
}

void EXItemAnimator::GetDatum(EXHashCode DatumHashRef, EXDatumTempArray& DatumArray, u64 Flags)
{
    EXDatumTemp Datum;
    EXDatumTemp* pDatum = &Datum;

    if (GetDatum(DatumHashRef, *pDatum, Flags, m_pNullDatumPtr))
    {
        DatumArray.Add(*pDatum, 1);
    }
}

void EXItemAnimator::GetDatum_ChildLink(EXHashCode DatumHashRef, EXDatumTempArray& DatumArray, u64 Flags) const
{
    for (EXItemAnimator* pChild = (EXItemAnimator*)m_Nodes.Head(); pChild; pChild = (EXItemAnimator*)pChild->Next())
    {
        pChild->GetDatum(DatumHashRef, DatumArray, Flags);
    }
}

void* EXItemAnimator::GetNearestDatum(EXVector& vctPos, EXDatumTemp& Datum, u64 Flags)
{
    if (Flags & 0x80)
    {
        GetNearestDatum_ChildLink(vctPos, Datum, Flags);
    }

    return 0;
}

void* EXItemAnimator::GetNearestDatum_ChildLink(EXVector& vctPos, EXDatumTemp& Datum, u64 Flags) const
{
    for (EXItemAnimator* pChild = (EXItemAnimator*)m_Nodes.Head(); pChild; pChild = (EXItemAnimator*)pChild->Next())
    {
        void* pRetPtr = pChild->GetNearestDatum(vctPos, Datum, Flags);

        if (pRetPtr)
        {
            return pRetPtr;
        }
    }

    return 0;
}

void EXItemAnimator::DoEntityScoop_ChildLink(EXMatrix& mtxIn, EXCollisionScoopTemp& cst, u64 CtrlFlags) const
{
    for (EXItemAnimator* pChild = (EXItemAnimator*)m_Nodes.Head(); pChild; pChild = (EXItemAnimator*)pChild->Next())
    {
        pChild->DoEntityScoop(mtxIn, cst, CtrlFlags);
    }
}

EXGeoCommonObject* EXItemAnimator::GetGeoObject() const
{
    EXGeoObjectHeader* pHeader = m_GeoRefObject.GeoObjectHeader();
    EXGeoCommonObject* pObject;

    if (pHeader)
    {
        pObject = pHeader->Object();
    }
    else
    {
        pObject = 0;
    }

    return pObject;
}

Bool EXItemAnimator::GetBoundsBox(EXBoundsBox& Bounds, u64 Flags)
{
    Bool RetFlags = _GetBoundsBox(Bounds, Flags);

    for (EXItemAnimator* pChild = (EXItemAnimator*)m_Nodes.Head(); pChild; pChild = (EXItemAnimator*)pChild->Next())
    {
        RetFlags |= pChild->GetBoundsBox(Bounds, 1);
    }

    return RetFlags;
}

void EXItemAnimator::UpdateBoundsBox(Bool fRebuild)
{
    EXMatrix mtxm;
    EXBoundsBox mtxBounds;

    _GetBoundsBox(m_BoundsBox, 2);

    for (EXItemAnimator* pChild = (EXItemAnimator*)m_Nodes.Head(); pChild; pChild = (EXItemAnimator*)pChild->Next())
    {
        if (fRebuild)
        {
            UpdateBoundsBox(fRebuild);
        }

        pChild->CalcMatrix(mtxm);
        mtxBounds = pChild->m_BoundsBox;
        mtxBounds._ApplyXForm(mtxm);
        m_BoundsBox.Accumulate(mtxBounds);
    }

    m_ValidBounds = 1;
}

void EXItemAnimator::ApplyMatrixBoundsBox(EXBoundsBox& InBounds, EXBoundsBox& Bounds, u64 Flags) const
{
    EXMatrix amtx;

    if (!(Flags & 2))
    {
        CalcMatrix(amtx);
        InBounds._ApplyXForm(amtx);
    }

    if (Flags & 1)
    {
        Bounds.Accumulate(InBounds);
    }
    else
    {
        Bounds.Set(InBounds);
    }
}

Bool EXItemAnimator::_GetBoundsBox(EXBoundsBox& Bounds, u64 Flags)
{
    if (!(Flags & 1))
    {
        Bounds.SetZero();
    }

    return false;
}

void EXItemAnimator::SetRenderState(EXHashCode HashRef, Bool State)
{
    if (HashRef != m_GeoRefObject.m_HashRef)
    {
        return;
    }

    if (State != false)
    {
        m_ValidMtx = 0;
        m_ItemFlags.BitSet(1);
        return;
    }

    m_ItemFlags.BitClr(1);
}

void EXItemAnimator::SetFrameRate60(float f)
{
    m_rFrameRateMult = f / (float)EXBaseApp::m_NominalEngineFrameRate;
}

float EXItemAnimator::FrameRate60() const
{
    return m_rFrameRateMult * (float)EXBaseApp::m_NominalEngineFrameRate;
}

void EXItemAnimator::SetObjectTime(float rObjectTime)
{
    m_rObjectFrame = rObjectTime * (float)EXBaseApp::m_NominalEngineFrameRate;
}

float EXItemAnimator::ObjectTime() const
{
    return m_rObjectFrame / (float)EXBaseApp::m_NominalEngineFrameRate;
}

void EXItemAnimator::UpdateObjectTime(float rObjectTime)
{
    SetObjectTime(rObjectTime);
}

void EXItemAnimator::BuildEntityInfoArray(EXMatrix& mtxIn, EXGeoEntity_InfoArray& InfoArray, Bool fFlag)
{
}

u32 EXItemAnimator::DoRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo, u64 CtrlFlags)
{
    if (EXBaseRenderEnv::RenderState() & 1)
    {
        CalcMatrix_InPlace(mtxIn, CtrlFlags);
    }

    return 0;
}

void EXItemAnimator::DoItemUpdate()
{
    if (m_ItemFlags.BitTest(2))
    {
        DoUpdate();
        m_ItemFlags.BitClr(8);
        UpdateBoundsBox(false);
    }
}

u32 EXItemAnimator::DoItemRender(EXMatrix& mtxIn, EXRenderInfo& InRenderInfo)
{
    if (m_ItemFlags.BitTest(1))
    {
        u32 dwReturn = DoRender(mtxIn, InRenderInfo, 0);

        if (m_ItemFlags.BitTest(8))
        {
            m_ItemFlags.BitClr(8);
        }

        return dwReturn;
    }

    return 0;
}

void EXItemAnimator::ApplyFunction(EXANIMATORCALLBACK* pApplyFunc, void* pData)
{
    pApplyFunc(this, pData);

    for (EXItemAnimator* pDListItem = (EXItemAnimator*)m_Nodes.Head(); pDListItem; pDListItem = (EXItemAnimator*)pDListItem->Next())
    {
        pDListItem->ApplyFunction(pApplyFunc, pData);
    }
}

EXItemAnimator* EXItemAnimatorQueue::Allocate(EXHashCode HashRef, EXItemAnimator* pAnimator)
{
    if (pAnimator == 0)
    {
        pAnimator = (EXItemAnimator*)AnimatorAllocatorQueue.Get();
    }

    switch ((HashRef >> 24) & 0x7f)
    {
    case 4:
        ::new (pAnimator) EXItemAnimator_Script();
        break;
    case 3:
        ::new (pAnimator) EXItemAnimator_Anim();
        break;
    case 2:
        ::new (pAnimator) EXItemAnimator_Entity();
        break;
    case 0x11:
        ::new (pAnimator) EXItemAnimator_Particle();
        break;
    case 0x1a:
        ::new (pAnimator) EXItemAnimator_Sound();
        break;
    case 0x1b:
        ::new (pAnimator) EXItemAnimator_Sound();
        break;
    case 0x13:
        ::new (pAnimator) EXItemAnimator_DynLight();
        break;
    default:
        if (HashRef != 0xffffffff)
        {
            do
            {
                // deadstripped
            } while (true);
        }

        ::new (pAnimator) EXItemAnimator();
        break;
    }

    pAnimator->m_AllocatorCreated = true;
    return pAnimator;
}

void EXItemAnimatorQueue::Release(EXItemAnimator* pAnimator)
{
    if (pAnimator->m_AllocatorCreated)
    {
        pAnimator->m_AllocatorCreated = false;
        pAnimator->~EXItemAnimator();
        AnimatorAllocatorQueue.Remove((_EXItemAnimatorAllocator*)pAnimator);
    }
    else if (pAnimator)
    {
        delete pAnimator;
    }
}

EXRuntimeClass* EXItemAnimator::GetRuntimeClass() const
{
    return &EXItemAnimator::classEXItemAnimator;
}

char* EXItemAnimator::TypeName() const
{
    return "EXItemAnimator";
}

int EXItemAnimator::Size() const
{
    return sizeof(EXItemAnimator);
}

Bool EXItemAnimator::Initialise(EXGeoFile* pGeoFile, EXHashCode RefHash)
{
    return true;
}

void EXItemAnimator::EnableParticleSystems(Bool Enable) const
{
}

Bool EXItemAnimator::DoGrabPoint(EXMatrix& mtxIn, EXGrabPointTemp& gpt, u64 CtrlFlags)
{
    return false;
}

Bool EXItemAnimator::DoGrabPoint(EXMatrix& mtxIn, EXGrabPointArrayTemp& gpat, u64 CtrlFlags)
{
    return false;
}

void EXItemAnimator::DoRayCast(EXMatrix& mtxIn, EXRayCastTemp& rct, u64 CtrlFlags)
{
}

void EXItemAnimator::DoShadowCast(EXShadowTemp& st)
{
}

void EXItemAnimator::DoEntityScoop(EXMatrix& mtxIn, EXCollisionScoopTemp& cst, u64 CtrlFlags)
{
}

void EXItemAnimator::SetLodMin(u64 nMinLod)
{
}

void EXItemAnimator::SetLodMax(u64 nMaxLod)
{
}
