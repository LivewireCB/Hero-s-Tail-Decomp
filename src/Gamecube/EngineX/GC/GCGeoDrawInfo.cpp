#include "EngineX/GC/GCGeoDrawInfo.h"

#include "libc/string.h"

void EXGDiData::Release()
{
    if (m_GDiBuf.m_Data[0].pDynLights != NULL)
    {
        EXAllocSetCacheDel(m_GDiBuf.m_Data[0].pDynLights, 0x2, NULL);
        m_GDiBuf.m_Data[0].pDynLights = 0;
    }

    if (m_GDiBuf.m_Data[0].pVert != NULL)
    {
        EXAllocSetCacheDel(m_GDiBuf.m_Data[0].pVert, 0x2, NULL);
        m_GDiBuf.m_Data[0].pVert = 0;
    }

    if (m_GDiBuf.m_Data[0].pMisc != NULL)
    {
        EXAllocSetCacheDel(m_GDiBuf.m_Data[0].pMisc, 0x2, NULL);
        m_GDiBuf.m_Data[0].pMisc = 0;
    }

    if (m_GDiBuf.m_Data[0].pShadowData != NULL)
    {
        EXFree(m_GDiBuf.m_Data[0].pShadowData);
    }
}

EXGDiDataArray::~EXGDiDataArray()
{
    RemoveAll();
}

void EXGDiDataArray::Init(int iSize)
{
    m_pData = (EXGDiData*)_EXAlloc(iSize * 28, 1);

    if (m_pData != NULL)
    {
        memset(m_pData, 0, iSize * 28);
    }

    m_iSize = iSize;
}

void EXGDiDataArray::RemoveAll()
{
    if (m_pData != NULL)
    {
        for (int i = 0; i < m_iSize; i++)
        {
            m_pData[i].Release();
        }

        if (m_pData != NULL)
        {
            EXFree(m_pData);
            m_pData = NULL;
        }

        m_iSize = 0;
    }
}

EXGDiInstanceData::~EXGDiInstanceData()
{
}
