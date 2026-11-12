#include "EngineX/EXItemAnimator_Collision.h"

#include "libc/string.h"

EXItemAnimator_Collision* EXItemAnimator_Collision::CreateObject()
{
    return new EXItemAnimator_Collision();
}

EXItemAnimator_Collision::EXItemAnimator_Collision()
{
    memset(&m_Collision, 0, sizeof(EXDatumTemp));
    m_CollisionRef = -1;
}

void EXItemAnimator_Collision::SetFromScriptCmd(GEOSCRIPT_COLLISION* pCmd)
{
    m_Collision.vctPos.SetZero();
    m_Collision.vctDir.SetIdentity();
    m_Collision.Flags = m_Collision.FrameFlags = 0;
    m_Collision.Type = pCmd->Type;
    m_Collision.Extents.data[0] = pCmd->Extents[0];
    m_Collision.Extents.data[1] = pCmd->Extents[1];
    m_Collision.Extents.data[2] = pCmd->Extents[2];
    m_CollisionRef = pCmd->Reference;
}

void* EXItemAnimator_Collision::GetDatum(EXHashCode DatumHashRef, EXDatumTemp& Datum, u64 Flags, void*& pPrevPtr)
{
    void* pRetPtr = 0;

    if (pPrevPtr != &m_Collision)
    {
        pRetPtr = &m_Collision;
        Datum = m_Collision;
    }

    if (pRetPtr == 0 && (Flags & 0x80))
    {
        pRetPtr = GetDatum_ChildLink(DatumHashRef, Datum, Flags, pPrevPtr);
    }

    return pRetPtr;
}

void EXItemAnimator_Collision::GetDatum(EXHashCode DatumHashRef, EXDatumTempArray& DatumArray, u64 Flags)
{
    DatumArray.Add(m_Collision, 1);

    if (Flags & 0x80)
    {
        GetDatum_ChildLink(DatumHashRef, DatumArray, Flags);
    }
}

void EXItemAnimator_Collision::SetObjectTime(float rObjectTime)
{
    m_RenderFlags.BitClr(2);
    m_Collision.Extents.data[0] = m_Scale.x;
    m_Collision.Extents.data[1] = m_Scale.y;
    m_Collision.Extents.data[2] = m_Scale.z;
    CalcMatrix_InPlaceParent();
}

EXRuntimeClass* EXItemAnimator_Collision::GetRuntimeClass() const
{
    return &EXItemAnimator_Collision::classEXItemAnimator_Collision;
}

char* EXItemAnimator_Collision::TypeName() const
{
    return "EXItemAnimator_Collision";
}

int EXItemAnimator_Collision::Size() const
{
    return sizeof(EXItemAnimator_Collision);
}
