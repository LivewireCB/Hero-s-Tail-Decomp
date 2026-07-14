#include "EngineX/EXGeoScript.h"

EXBoundsBox& EXGeoScript::GetBoundsBox()
{
    return m_BoundsBox;
}

EXRuntimeClass* EXGeoScript::GetRuntimeClass() const
{
    return &classEXGeoScript;
}
