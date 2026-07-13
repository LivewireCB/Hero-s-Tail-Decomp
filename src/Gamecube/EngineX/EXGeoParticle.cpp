#include <include/EngineX/EXGeoParticle.h>

EXBoundsBox& EXGeoParticle::GetBoundsBox()
{
    if (((u32)this & 0xf) != 0)
    {
        do
        {
        } while (true);
    }

    return m_BoundsBox;
}

EXRuntimeClass* EXGeoParticle::GetRuntimeClass() const
{
    return &classEXGeoParticle;
}
