#include <EngineX/EXString.h>

int EXString::IncRefCount()
{
    if (m_pData != 0)
    {
        return ++((EXStringData*)m_pData - 1)->Refs;
    }
    return 0;
}

void EXString::SetLength(u16 aNewLength)
{
    if (m_pData != 0)
    {
        ((EXStringData*)m_pData - 1)->Len = aNewLength;
    }
}

u16 EXString::Length() const
{
    if (m_pData != 0)
    {
        return ((EXStringData*)m_pData - 1)->Len;
    }
    return 0;
}

u16 EXString::Capacity() const
{
    if (m_pData != 0)
    {
        return ((EXStringData*)m_pData - 1)->Alloc;
    }
    return 0;
}

Bool EXString::IsEmpty() const
{
    if (m_pData != 0)
    {
        return ((EXStringData*)m_pData - 1)->Len == 0;
    }
    return 1;
}
