#include <EngineX/EXString.h>

#include "include/GC/libc/string.h"

#include "EngineX/EXMemoryManager.h"

// This file should show that i have no fucking clue what im doing
// Sincerely, Colin aka Livewire

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

// Below function is nonmatching due to crclr caused by memcpy
// Using the forward declaration below fixes the problem,
// for some reason the function isn't reaching the memcpy in the header?

// void* memcpy(void* dest, const void* src, size_t num);
void EXString::MakeUnique()
{
    EXStringData* pSData;
    char* pNewData;

    if (m_pData != 0)
    {
        pSData = (EXStringData*)m_pData - 1;
        if (pSData->Refs > 1)
        {
            EXStringData* pNewSData = (EXStringData*)_EXAlloc(pSData->Alloc + 8, 0);
            pNewData = (char*)(pNewSData + 1);

            memcpy(pNewData, m_pData, pSData->Alloc);

            pNewSData->Refs = 1;
            pNewSData->Len = pSData->Len;
            pNewSData->Alloc = pSData->Alloc;

            --pSData->Refs;
            m_pData = pNewData;
        }
    }
}

void EXString::SetLength(u16 aNewLength)
{
    if (m_pData != 0)
    {
        ((EXStringData*)m_pData - 1)->Len = aNewLength;
    }
}

EXString::EXString(char* pString)
{
    m_pData = NULL;
    if (pString != NULL && (*pString) != NULL)
    {
        AllocMem((u16)strlen(pString));
        strcpy(m_pData, pString);
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

    if (m_pData != 0)
    {
        if (MinLen >= ((EXStringData*)m_pData - 1)->Len)
        {
        }
    }
    ReallocMem(MinLen);
}

void EXString::ReleaseBuffer()
{
    EXStringData* pSData;

    if (m_pData != 0)
    {
        pSData = (EXStringData*)m_pData - 1;
        pSData->Len = strlen(m_pData);
    }
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

EXString& EXString::operator=(char* pString)
{
    AllocMem((u16)strlen(pString));
    strcpy(m_pData, pString);
    return *this;
}

EXString& EXString::operator=(EXString& Str)
{
    if (&Str != this)
    {
        DeallocMem();
        m_pData = Str.m_pData;
        IncRefCount();
    }
    return *this;
}

// weird codegen moment. The return result somehow needs to be moved up
// above the two function calls
EXString operator+(char* apStr1, EXString& aStr2)
{
    EXString Result(apStr1);
    aStr2 += Result;
    Result.IncRefCount();
    Result.DeallocMem();
    // return Result;
}

EXString operator+(EXString& aLStr, char* apRStr)
{
    // /* 0x0(sp) */ EXString Result;
}

Bool operator==(EXString& Str1, EXString& Str2)
{
    /* s0 16 */ int nLen;
    /* a1 5 */ int c;
}
