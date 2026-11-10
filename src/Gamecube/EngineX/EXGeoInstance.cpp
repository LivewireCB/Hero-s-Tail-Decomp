#include "EngineX/EXGeoInstance.h"

EXInstanceManager::EXInstanceManager()
{
    AllocateManager();
}

EXInstanceManager::~EXInstanceManager()
{
    DeleteManager();
}

Bool EXInstanceManager::AllocateManager()
{
    u32 i;

    m_UsedInstanceLists = 0;
    m_UsedCustomLists = 0;
    m_TotalInstanceLists = 0x40;
    m_TotalCustomLists = 0x40;

    m_Pool.SetSize(0x40, -1);
    m_CustomPool.SetSize(m_TotalCustomLists, -1);

    for (i = 0; i < m_TotalCustomLists; i++)
    {
        m_Pool.ElementAt(i).m_pGeoHeader = NULL;
        m_Pool.ElementAt(i).m_pDrawInfo = NULL;
        m_Pool.ElementAt(i).m_pData = NULL;
        m_Pool.ElementAt(i).m_Age = 0;
    }

    for (i = 0; i < m_TotalInstanceLists; i++)
    {
        m_CustomPool.ElementAt(i) = NULL;
    }

    m_pLastUsedPool = NULL;
    return true;
}

void EXInstanceManager::DeleteManager()
{
    for (int i = 0; i < m_Pool.m_iSize; i++)
    {
        if (m_Pool.ElementAt(i).m_pDrawInfo != NULL)
        {
            EXFree(m_Pool.ElementAt(i).m_pDrawInfo);
            m_Pool.ElementAt(i).m_pDrawInfo = NULL;
        }

        if (m_Pool.ElementAt(i).m_pData != NULL)
        {
            delete m_Pool.ElementAt(i).m_pData;
            m_Pool.ElementAt(i).m_pData = NULL;
        }
    }

    m_Pool.Empty(true);
    m_CustomPool.Empty(true);

    m_UsedInstanceLists = 0;
    m_UsedCustomLists = 0;
    m_TotalInstanceLists = 0;
    m_TotalCustomLists = 0;
    m_pLastUsedPool = NULL;
}

void EXInstanceManager::ResetInstanceManager()
{
    for (u32 i = 0; i < m_UsedInstanceLists; i++)
    {
        m_Pool.ElementAt(i).m_NumInstances = 0;
    }

    for (u32 i = 0; i < m_UsedCustomLists; i++)
    {
        m_CustomPool.ElementAt(i) = NULL;
    }

    m_UsedInstanceLists = 0;
    m_UsedCustomLists = 0;
    m_pLastUsedPool = NULL;
}