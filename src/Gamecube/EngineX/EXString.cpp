#include <EngineX/EXString.h>

#include "include/GC/libc/string.h"

#include "EngineX/EXMemoryManager.h"

// TODO: decompile lib functions and get headers for them
// goofy shit to make the compiler happy
#define __MWERKS__
#include "include/GC/libc/stdarg.h"
extern void __builtin_va_info(va_list*);
extern "C" int vsprintf(char* buffer, const char* format, va_list args);

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
    EXStringData* pNewSData;
    u16 nAlloc;
    char* pNewData;

    if (m_pData != NULL)
    {
        pSData = (EXStringData*)m_pData - 1;

        if (pSData->Refs <= 1 && nLength < pSData->Alloc)
        {
            pSData->Len = nLength;
        }

        nAlloc = (nLength + 1) & 0xffff;
        if (nAlloc <= 0x37)
        {
            nAlloc = 0x38;
        }
        else if (nAlloc <= 0x17)
        {
            nAlloc = 0x18;
        }
        else if (nAlloc <= 0x77)
        {
            nAlloc = 0x78;
        }
        else if (nAlloc <= 0xf7)
        {
            nAlloc = 0xf8;
        }
        else if (nAlloc <= 0x1f7)
        {
            nAlloc = 0x1f8;
        }

        pNewSData = (EXStringData*)_EXAlloc(nAlloc + 8, 0);
        pNewData = (char*)(pNewSData + 1);
        memcpy(pNewData, m_pData, pSData->Len + 1);
        pNewSData->Refs = 1;
        pNewSData->Len = nLength;
        pNewSData->Alloc = nAlloc;
        DeallocMem();

        m_pData = pNewData;
    }
    else
    {
        AllocMem(nLength);
    }
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

// why?
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

EXString::EXString(char* pString, u16 len)
{
    u16 nLength;
    u16* pLength;

    m_pData = NULL;
    if (pString != NULL && *pString != NULL)
    {
        pLength = &len;
        nLength = strlen(pString);
        pLength = &nLength;
        if (len <= nLength)
        {
            pLength = &len;
        }
        nLength = *pLength;
        AllocMem(nLength);
        strncpy(m_pData, pString, nLength);
        m_pData[nLength] = 0;
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
    u16 Len = MinLen;

    if (m_pData != 0)
    {
        if (MinLen < ((EXStringData*)m_pData - 1)->Len)
        {
            Len = ((EXStringData*)m_pData - 1)->Len;
        }
    }
    ReallocMem(Len);
    return m_pData;
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

    if (m_pData != NULL)
    {
        pSData = (EXStringData*)m_pData - 1;

        // TODO: Check that this is the best way to write it.
        // Not really a fan but it matches so it could be right
        if (pos < 0 || pos >= pSData->Len)
        {
            return -1;
        }
        for (; pos < pSData->Len; pos++)
        {
            if (m_pData[pos] == ch)
            {
                return pos;
            }
        }
    }
    return -1;
}

// This is also super dumb and i havent figure it out
// this is close enough for now
s8 EXString::CompareNoCase(EXString& Str) const
{
    u16 nLen;
    u16 nStrLen;
    u16 nNumChars;
    u16* pNumChars;
    u16 c;
    char left;
    char right;

    if (m_pData == Str.m_pData)
    {
        return 0;
    }

    nLen = Length();
    nStrLen = Str.Length();
    pNumChars = &nLen;

    if (nLen > nStrLen)
    {
        pNumChars = &nStrLen;
    }

    nNumChars = *pNumChars;

    for (c = 0; c < nNumChars; c++)
    {
        left = m_pData[c];
        right = Str.m_pData[c];
        if (left >= 'A' && left <= 'Z')
        {
            left += 'a' - 'A';
        }
        if (right >= 'A' && right <= 'Z')
        {
            right += 'a' - 'A';
        }
        if (left < right)
        {
            return -1;
        }
        if (left > right)
        {
            return 1;
        }
    }

    if (nLen > nStrLen)
    {
        return 1;
    }

    if (nLen < nStrLen)
    {
        return -1;
    }

    return 0;
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

EXString& EXString::operator+=(EXString& Str)
{
    u16 nLength = Length();
    ReallocMem(nLength + Str.Length());
    strcpy(m_pData + nLength, Str.m_pData != NULL ? Str.m_pData : (char*)"");
    return *this;
}

EXString& EXString::operator+=(char* pStr)
{
    char* pString;
    int nLength;
    int nStringLength;

    pString = pStr;
    if (pString != NULL)
    {
        nStringLength = strlen(pString);
        nLength = Length();
        nStringLength += nLength;
        ReallocMem(nStringLength);
        strcpy(m_pData + nLength, pString);
    }
    return *this;
}

EXString operator+(char* apStr1, EXString& aStr2)
{
    EXString Result(apStr1);
    Result += aStr2;
    return Result;
}

EXString operator+(EXString& aLStr, char* apRStr)
{
    EXString Result(aLStr);
    Result.IncRefCount();
    Result += apRStr;
    return Result;
}

Bool operator==(EXString& Str1, EXString& Str2)
{
    int nLen;
    int c;

    if (Str1.m_pData == Str2.m_pData)
    {
        return 1;
    }
    nLen = Str1.Length();
    if (nLen != Str2.Length())
    {
        return 0;
    }
    for (c = 0; c < nLen; c++)
    {
        if (Str1.m_pData[c] != Str2.m_pData[c])
        {
            return 0;
        }
    }
    return 1;
}

// register moment
void EXString::ToUpper()
{
    u16 nLen;
    u16 c;

    MakeUnique();
    nLen = Length();
    for (c = 0; c < nLen; c++)
    {
        if (m_pData[c] >= 'a' && m_pData[c] <= 'z')
        {
            m_pData[c] -= 'a' - 'A';
        }
    }
}

EXString EXString::Token(int nTok, char chSep, Bool fNullTokensOK) const
{
}

int EXString::Tokenise(EXStringArray& Tokens, EXString& Sep, Bool fNullTokensOK) const
{
}

s16 EXString::Format(char* FmtString, ...)
{
    va_list argList;
    char* pBuffer;
    s16 strLen;

    va_start(argList, FmtString);
    pBuffer = GetBuffer(0x400);
    strLen = vsprintf(pBuffer, FmtString, argList);
    va_end(argList);
    ReleaseBuffer();
    return strLen;
}

void fn_802FDE74(EXString* pElements, int nCount)
{
    for (s32 i = nCount - 1; i != -1; i--)
    {
        pElements->m_pData = NULL;
        pElements++;
    }
}

void fn_802FDE9C(EXString* pElements, int nCount)
{
    for (s32 i = nCount - 1; i != -1; i--)
    {
        pElements->DeallocMem();
        pElements++;
    }
}

EXStringArray::EXStringArray(int nSize, int iGrowBy)
{
    m_pData = NULL;
    m_iAlloc = 0;
    m_iSize = 0;
    if (iGrowBy < 8)
    {
        iGrowBy = 8;
    }
    m_iGrowBy = iGrowBy;
    if (nSize > 0)
    {
        SetSize(nSize, -1);
    }
}

EXStringArray::~EXStringArray()
{
    RemoveAll();
}

void EXStringArray::SetSize(int nNewSize, int nGrowBy)
{
    int nNewMax;

    if (nGrowBy != -1)
    {
        m_iGrowBy = nGrowBy;
    }
    if (nNewSize == 0)
    {
        RemoveAll();
        return;
    }
    if (m_pData == NULL)
    {
        m_pData = (EXString*)_EXAlloc(nNewSize * sizeof(EXString), 0);
        fn_802FDE74(m_pData, nNewSize);
        m_iSize = nNewSize;
        m_iAlloc = nNewSize;
        return;
    }
    if (nNewSize <= m_iAlloc)
    {
        if (nNewSize > m_iSize)
        {
            fn_802FDE74(m_pData + m_iSize, nNewSize - m_iSize);
        }
        else if (m_iSize > nNewSize)
        {
            fn_802FDE9C(m_pData + nNewSize, m_iSize - nNewSize);
        }
    }
    else
    {
        nNewMax = m_iAlloc;
        if (m_iGrowBy == 0)
        {
            nNewMax = m_iSize / 8;
            if (nNewMax < 4)
            {
                nNewMax = 4;
            }
            else if (nNewMax > 0x400)
            {
                nNewMax = 0x400;
            }
        }
        nNewMax += m_iAlloc;
        if (nNewSize > nNewMax)
        {
            nNewMax = nNewSize;
        }
        m_pData = (EXString*)_EXRealloc(m_pData, nNewMax * sizeof(EXString));
        fn_802FDE74(m_pData + m_iAlloc, nNewSize - m_iSize);
        m_iAlloc = nNewMax;
    }
    m_iSize = nNewSize;
}

void EXStringArray::RemoveAll()
{
    if (m_pData != NULL)
    {
        fn_802FDE9C(m_pData, m_iSize);
        EXFree(m_pData);
        m_pData = NULL;
    }
    m_iAlloc = 0;
    m_iSize = 0;
}

void EXStringArray::SetAtGrow(int nIndex, EXString& newElement)
{
    if (nIndex >= m_iSize)
    {
        SetSize(nIndex + 1, -1);
    }
    m_pData[nIndex] = newElement;
}

int EXStringArray::Add(EXString& newElement)
{
    int nIndex = m_iSize;

    SetAtGrow(m_iSize, newElement);
    return nIndex;
}

void EXStringArray::RemoveAt(int nIndex, int nCount)
{
    int nEnd = nIndex + nCount;
    int nMoveCount = m_iSize - nEnd;

    fn_802FDE9C(nIndex + m_pData, nCount);

    if (nMoveCount != 0)
    {
        memmove(nIndex + m_pData, m_pData + nEnd, nMoveCount * sizeof(EXString));
    }

    m_iSize -= nCount;
}
