#include "EngineX/EXItemRender.h"

#include "EngineX/EXMalloc.h"

EXItemRender* EXItemRender::CreateObject()
{
    return new EXItemRender();
}

EXItemRender::EXItemRender()
{
    m_pUserCallback = 0;
}

EXBaseItem* EXItemRender::GetBaseOwner() const
{
    if (m_pOwner != 0)
    {
        return m_pOwner->GetBaseOwner();
    }

    return 0;
}
