#include "EngineX/EXItemAnimator.h"

// Guessing that EXItemAnimator is not the correct size.
// compiling as 0xf8 needs to be 0x110
EXItemAnimator* EXItemAnimator::CreateObject()
{
    return new EXItemAnimator();
}

EXItemAnimator::EXItemAnimator()
{
    // 0x109 doesnt exist????
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

void EXItemAnimator::AddAnimator(EXItemAnimator* p)
{
    if (p == this)
    {
        do
        {
            // deadstripped
        } while (true);
    }

    // offset wrong due to struct not being correct? See constructor and createobject above.
    p->m_ValidMtx = false;

    // this offset is correct so the issue should not be in EXBaseItem
    p->m_pOwner = this;

    m_Nodes.AddTail(p);
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
        m_ItemFlags.m_Flags |= 1;
        return;
    }

    m_ItemFlags.m_Flags &= ~0x1; // theres some fuckery here. Maybe a compiler flag?
}

// its only 56 bytes, how bad can it be?
// spoiler: fucking awful
void EXItemAnimator::SetFrameRate60(float f)
{
}

float EXItemAnimator::FrameRate60()
{
}

void EXItemAnimator::SetObjectTime(float rObjectTime)
{
}

float EXItemAnimator::ObjectTime()
{
}

void EXItemAnimator::UpdateObjectTime(float rObjectTime)
{
}

EXRuntimeClass* EXItemAnimator::GetRuntimeClass() const
{
    return &EXItemAnimator::classEXItemAnimator;
}

int EXItemAnimator::Size() const
{
    return sizeof(EXItemAnimator); // wont be correct until EXItemAnimator size is fixed.
    // could hardcode it, but thats not helpful
}

Bool EXItemAnimator::Initialise(EXGeoFile* pGeoFile, EXHashCode RefHash)
{
    return true;
}

void EXItemAnimator::EnableParticleSystems(Bool Enable) const
{
}

void EXItemAnimator::SetLodMin(u64 nMinLod)
{
}

void EXItemAnimator::SetLodMax(u64 nMaxLod)
{
}
