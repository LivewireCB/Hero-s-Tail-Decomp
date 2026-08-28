#include "EngineX/EXItemPhysics.h"

EXItemPhysics* EXItemPhysics::CreateObject()
{
    return new EXItemPhysics();
}

EXItemPhysicsExt* EXItemPhysicsExt::CreateObject()
{
    return new EXItemPhysicsExt();
}

EXItemPhysics::EXItemPhysics()
{
    m_PhysicsFlags = 0;
    m_CollisionFlags = 0;
    m_pItem = 0;
}

Bool EXItemPhysics::Initialise()
{
    return true;
}

Bool EXItemPhysics::DoUpdate()
{
    return true;
}

EXRuntimeClass* EXItemPhysics::GetRuntimeClass() const
{
    return &EXItemPhysics::classEXItemPhysics;
}

EXItemPhysics::~EXItemPhysics()
{
}

void EXItemPhysics::DoCollisions()
{
}
