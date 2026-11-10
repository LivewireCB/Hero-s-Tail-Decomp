#include "EngineX/EXWString.h"

#include "include/GC/libc/stdarg.h"
#include "include/GC/libc/string.h"

#include "EngineX/EXMemoryManager.h"
#include "EngineX/EXStdFuncs.h"

extern "C" void* EXWStringMemcpy(void* dest, const void* src, size_t num) asm("memcpy");

u32 WVsprintf(wchar* pBuffer, wchar* FormatString, va_list argList);

template <class T> inline const T& Max(const T& n1, const T& n2)
{
    if (n1 >= n2)
        return n1;
    return n2;
}

template <class T> inline const T& Min(const T& n1, const T& n2)
{
    if (n1 <= n2)
        return n1;
    return n2;
}

EXWString::EXWString(wchar* pString)
{
    m_pData = NULL;
    if (pString != NULL)
    {
        AllocMem((u16)Wcslen(pString));
        Wcscpy(m_pData, pString);
    }
}

EXWString::EXWString(char* pString)
{
    u16 nNewLen;
    u32 i;

    m_pData = NULL;
    if (pString != NULL && *pString != 0)
    {
        nNewLen = strlen(pString) + 1;
        AllocMem(nNewLen);
        for (i = 0; i < nNewLen; i++)
        {
            m_pData[i] = ((u8*)pString)[i];
        }
        m_pData[i] = 0;
    }
}

u16 EXWString::Length() const
{
    u32 Counter;

    if (m_pData != NULL)
    {
        Counter = 0;
        while (m_pData[Counter] != 0)
        {
            Counter++;
        }
        return Counter;
    }
    return 0;
}

u16 EXWString::Capacity() const
{
    if (m_pData != NULL)
    {
        return ((EXStringData*)(m_pData - 8))->Alloc;
    }
    return 0;
}

wchar* EXWString::GetBuffer(u16 MinLen)
{
    u16 nLen = MinLen;
    if (m_pData != NULL)
    {
        nLen = Max(MinLen, ((EXStringData*)(m_pData - 8))->Len);
    }
    ReallocMem(nLen);
    return m_pData;
}

void EXWString::ReleaseBuffer()
{
    EXStringData* pSData;

    if (m_pData != NULL)
    {
        pSData = (EXStringData*)(m_pData - 8);
        pSData->Len = Wcslen(m_pData);
    }
}

EXWString& EXWString::operator=(wchar* pString)
{
    AllocMem((u16)Wcslen(pString));
    Wcscpy(m_pData, pString);
    return *this;
}

EXWString& EXWString::operator=(char* pString)
{
    s32 Length;

    Length = strlen(pString) + 1;
    AllocMem(Length);
    Wcscpy(m_pData, (u8*)pString);
    return *this;
}

EXWString& EXWString::operator=(EXWString& Str)
{
    if (&Str != this)
    {
        DeallocMem();
        m_pData = Str.m_pData;
        IncRefCount();
    }
    return *this;
}

EXWString& EXWString::operator+=(EXWString& Str)
{
    u16 nLength = Length();
    ReallocMem(nLength + Str.Length());
    if (nLength != 0)
    {
        Wcscpy(m_pData + nLength, Str.m_pData != NULL ? Str.m_pData : (wchar*)L"");
    }
    else
    {
        Wcscpy(m_pData, Str.m_pData != NULL ? Str.m_pData : (wchar*)L"");
    }
    return *this;
}

EXWString& EXWString::operator+=(wchar* pStr)
{
    size_t nlen1;
    u16 nLength;

    if (pStr == NULL)
    {
        return *this;
    }
    nlen1 = Wcslen(pStr);
    nLength = Length();
    ReallocMem(nLength + nlen1);
    if (nLength != 0)
    {
        Wcscpy(m_pData + nLength, pStr);
    }
    else
    {
        Wcscpy(m_pData, pStr);
    }
    return *this;
}

EXWString operator+(EXWString& aLStr, wchar* apRStr)
{
    EXWString Result(aLStr);
    Result += apRStr;
    return Result;
}

void EXWString::AllocMem(u16 nLength)
{
    EXStringData* pSData;
    int nAlloc;

    nAlloc = (u16)(nLength + 1);

    if (m_pData != NULL)
    {
        if (nAlloc > Capacity())
        {
            DeallocMem();
        }
        else
        {
            SetLength(nLength);
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

    pSData = (EXStringData*)_EXAlloc((nAlloc + 8) * 2, 0);
    pSData->Refs = 1;
    pSData->Len = nLength;
    pSData->Alloc = nAlloc;
    m_pData = (wchar*)pSData + 8;
}

void EXWString::ReallocMem(u16 nLength)
{
    EXStringData* pSData;
    int nAlloc;
    wchar* pNewData;

    if (m_pData != NULL)
    {
        pSData = (EXStringData*)(m_pData - 8);

        if (pSData->Refs > 1 || nLength >= pSData->Alloc)
        {
            nAlloc = (u16)(nLength + 1);
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

            EXStringData* pNewSData = (EXStringData*)_EXAlloc((nAlloc + 8) * 2, 0);
            pNewData = (wchar*)pNewSData + 8;
            EXWStringMemcpy(pNewData, m_pData, pSData->Len * 2 + 2);
            pNewSData->Alloc = nAlloc;
            pNewSData->Len = nLength;
            pNewSData->Refs = 1;
            DeallocMem();
            m_pData = pNewData;
        }
        else
        {
            pSData->Len = nLength;
        }
    }
    else
    {
        AllocMem(nLength);
    }
}

void EXWString::DeallocMem()
{
    EXStringData* pSData;

    if (m_pData != NULL)
    {
        pSData = (EXStringData*)(m_pData - 8);
        if (--pSData->Refs == 0)
        {
            EXFree(pSData);
        }
    }
    m_pData = NULL;
}

int EXWString::IncRefCount()
{
    if (m_pData != NULL)
    {
        return ++((EXStringData*)(m_pData - 8))->Refs;
    }
    return 0;
}

void EXWString::SetLength(u16 aNewLength)
{
    if (m_pData != NULL)
    {
        ((EXStringData*)(m_pData - 8))->Len = aNewLength;
    }
}

s16 EXWString::Format(wchar* FmtString, ...)
{
    va_list argList;
    va_list argListSave;
    int nMaxLen;
    wchar* lpsz;
    int nItemLen;
    int nWidth;
    int nPrecision;

    va_start(argList, FmtString);
    va_start(argListSave, FmtString);

    nMaxLen = 0;
    for (lpsz = FmtString; *lpsz != 0; lpsz++)
    {
        if (*lpsz != '%' || *(++lpsz) == '%')
        {
            nMaxLen += 1;
            continue;
        }

        nItemLen = 0;
        nWidth = 0;
        for (; *lpsz != 0; lpsz++)
        {
            if (*lpsz == '#')
            {
                nMaxLen += 2;
            }
            else if (*lpsz == '*')
            {
                nWidth = va_arg(argList, int);
            }
            else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' || *lpsz == ' ')
            {
            }
            else
            {
                break;
            }
        }

        if (nWidth == 0)
        {
            int total = 0;
            wchar* p = lpsz;
            for (; *p != 0 && (unsigned)(*p - '0') <= 9; p++)
            {
                total = total * 10 + (*p - '0');
            }
            nWidth = total;
            for (; *lpsz != 0 && (unsigned)(*lpsz - '0') <= 9; lpsz++)
            {
            }
        }

        nPrecision = 0;
        if (*lpsz == '.')
        {
            lpsz++;
            if (*lpsz == '*')
            {
                nPrecision = va_arg(argList, int);
                lpsz++;
            }
            else
            {
                int total = 0;
                wchar* p = lpsz;
                for (; *p != 0 && (unsigned)(*p - '0') <= 9; p++)
                {
                    total = total * 10 + (*p - '0');
                }
                nPrecision = total;
                for (; *lpsz != 0 && (unsigned)(*lpsz - '0') <= 9; lpsz++)
                {
                }
            }
        }

        switch (*lpsz)
        {
        case 'h':
        case 'l':
        case 'F':
        case 'N':
        case 'L':
            lpsz++;
            break;
        }

        switch (*lpsz)
        {
        case 'c':
        case 'C':
            nItemLen = 2;
            va_arg(argList, int);
            break;
        case 's':
        case 'S':
        {
            wchar* str = va_arg(argList, wchar*);
            nItemLen = Max(1, (int)Wcslen(str));
            break;
        }
        }

        if (nItemLen != 0)
        {
            nItemLen = Max(nItemLen, nWidth);
            if (nPrecision != 0)
            {
                nItemLen = Min(nItemLen, nPrecision);
            }
        }
        else
        {
            switch (*lpsz)
            {
            case 'd':
            case 'i':
            case 'u':
            case 'x':
            case 'X':
            case 'o':
                va_arg(argList, int);
                nItemLen = 32;
                nItemLen = Max(nItemLen, nWidth + nPrecision);
                break;
            case 'e':
            case 'f':
            case 'g':
            case 'G':
                va_arg(argList, double);
                nItemLen = 128;
                nItemLen = Max(nItemLen, nWidth + nPrecision);
                break;
            case 'p':
                va_arg(argList, int);
                nItemLen = 32;
                nItemLen = Max(nItemLen, nWidth + nPrecision);
                break;
            case 'n':
                va_arg(argList, int);
                break;
            }
        }

        nMaxLen += nItemLen;
    }

    GetBuffer((u16)(nMaxLen + 1));
    s16 strLen = WVsprintf(m_pData, FmtString, argListSave);
    ReleaseBuffer();
    return strLen;
}

static void ConstructElements(EXWString* pElements, int nCount)
{
    for (s32 i = nCount - 1; i != -1; i--)
    {
        *(wchar**)pElements = NULL;
        pElements++;
    }
}

static void DestructElements(EXWString* pElements, int nCount)
{
    for (s32 i = nCount - 1; i != -1; i--)
    {
        pElements->~EXWString();
        pElements++;
    }
}

EXWStringArray::EXWStringArray(int nSize, int iGrowBy)
{
    m_pData = NULL;
    m_iAlloc = 0;
    m_iSize = 0;
    m_iGrowBy = Max(iGrowBy, 8);
    if (nSize > 0)
    {
        SetSize(nSize, -1);
    }
}

EXWStringArray::~EXWStringArray()
{
    RemoveAll();
}

void EXWStringArray::SetSize(int nNewSize, int nGrowBy)
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
        m_pData = (EXWString*)_EXAlloc(nNewSize * sizeof(EXWString), 0);
        ConstructElements(m_pData, nNewSize);
        m_iAlloc = nNewSize;
        m_iSize = nNewSize;
        return;
    }
    if (nNewSize <= m_iAlloc)
    {
        if (nNewSize > m_iSize)
        {
            ConstructElements(m_pData + m_iSize, nNewSize - m_iSize);
        }
        else if (m_iSize > nNewSize)
        {
            DestructElements(m_pData + nNewSize, m_iSize - nNewSize);
        }
    }
    else
    {
        int nGrowBy = m_iGrowBy;
        if (nGrowBy == 0)
        {
            nGrowBy = m_iSize / 8;
            nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 0x400) ? 0x400 : nGrowBy);
        }
        if (nNewSize < m_iAlloc + nGrowBy)
        {
            nNewMax = m_iAlloc + nGrowBy;
        }
        else
        {
            nNewMax = nNewSize;
        }
        m_pData = (EXWString*)_EXRealloc(m_pData, nNewMax * sizeof(EXWString));
        ConstructElements(m_pData + m_iSize, nNewSize - m_iSize);
        m_iAlloc = nNewMax;
    }
    m_iSize = nNewSize;
}

void EXWStringArray::RemoveAll()
{
    if (m_pData != NULL)
    {
        DestructElements(m_pData, m_iSize);
        EXFree(m_pData);
        m_pData = NULL;
    }
    m_iAlloc = 0;
    m_iSize = 0;
}

void EXWStringArray::SetAtGrow(int nIndex, EXWString& newElement)
{
    if (nIndex >= m_iSize)
    {
        SetSize(nIndex + 1, -1);
    }
    m_pData[nIndex] = newElement;
}

int EXWStringArray::Add(EXWString& newElement)
{
    int nIndex = m_iSize;

    SetAtGrow(m_iSize, newElement);
    return nIndex;
}