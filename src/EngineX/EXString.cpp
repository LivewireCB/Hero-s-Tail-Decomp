#include <EngineX/EXString.h>

#include <include\libc\string.h>

#include "EngineX/EXMemoryManager.h"

void EXString::AllocMem(u16 nLength)
{
    EXStringData* pSData;
    u16 nCapacity;
    u16 nAlloc;

    nAlloc = (nLength + 1) & 0xffff;

    if (m_pData != 0)
    {
        nCapacity = EXString::Capacity();

        if (nAlloc > nCapacity)
        {
            EXString::DeallocMem();
        }

        if (!(nAlloc > nCapacity))
        {
            EXString::SetLength(nLength);
            return;
        }
    }

    if (nAlloc < 0x18)
    {
        nAlloc = 0x18;
    }
    else if (nAlloc < 0x38)
    {
        nAlloc = 0x38;
    }
    else if (nAlloc < 0x78)
    {
        nAlloc = 0x78;
    }
    else if (nAlloc < 0xf8)
    {
        nAlloc = 0xf8;
    }
    else if (nAlloc < 0x1f8)
    {
        nAlloc = 0x1f8;
    }

    pSData = (EXStringData*)_EXAlloc(nAlloc + 8, 0);
    this->m_pData = (char*)(pSData + 1);
    pSData->Refs = 1;
    pSData->Len = nLength;
    pSData->Alloc = nAlloc;
}

void EXString::ReallocMem(u16 nLength)
{
    EXStringData* pSData;
    u16 nAlloc;
    char* pNewData;
}

void EXString::DeallocMem()
{
    EXStringData* pSData;
    if (m_pData != 0)
    {
        pSData = (EXStringData*)m_pData - 1;
        if (--pSData->Refs == 0)
        {
            EXFree(pSData);
        }
    }
    m_pData = 0;
}

int EXString::IncRefCount()
{
    if (m_pData != 0)
    {
        return ++((EXStringData*)m_pData - 1)->Refs;
    }
    return 0;
}

void EXString::MakeUnique()
{
    EXStringData* pSData;
    char* pNewData;
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

char* EXString::GetBuffer(u16 MinLen)
{
    u16 Len;
    // u16& n2; ????
}

void EXString::ReleaseBuffer()
{
    EXStringData* pSData;
}

s32 EXString::Find(char ch, long pos) const
{
    EXStringData* pSData;
    s32 i;
}

s8 EXString::CompareNoCase(EXString& Str) const
{
    u16 nLen;
    u16 nStrLen;
    u16 nNumChars;
    u16 c;
    char left;
    char right;
}
