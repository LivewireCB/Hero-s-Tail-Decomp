#include "EngineX/GC/GCCluster.h"

#include "EngineX/EXMemoryManager.h"

EXCluster::EXCluster()
{
    m_ClusterBuff.m_Data[0].pPkt = 0;
}

EXCluster::~EXCluster()
{
    if (m_ClusterBuff.m_Data[0].pPkt != 0)
    {
        EXAllocSetCacheDel(m_ClusterBuff.m_Data[0].pPkt, 2, 0);
    }
}

// gxp might mean GXParse, but im not sure yet bunch of EngineX symbols with it
struct gxp_entity;
void GC_Cluster_Render(gxp_entity* entity)
{
}

EXClusterArray::~EXClusterArray()
{
    RemoveAll();
}

void EXClusterArray::Init(unsigned long Size)
{
    m_pClusters = new EXCluster[Size];
    m_Size = Size;
}

void EXClusterArray::RemoveAll()
{
    if (m_pClusters != 0)
    {
        delete[] m_pClusters;
        m_pClusters = 0;
        m_Size = 0;
    }
}
