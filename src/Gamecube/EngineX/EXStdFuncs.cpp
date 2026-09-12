#include "EngineX/EXStdFuncs.h"

// again, extremely dumb code block
#define __MWERKS__
#include "include/GC/libc/stdarg.h"
extern void __builtin_va_info(va_list*);
struct EXVaListTag
{
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
};

// I have to say that, I dont understand this code.
// all of this is my best interpretation of it, and to be clear, i suck at this style of code
// some of its gonna be wrong, maybe even be completely off but it is what it is.
// - Colin

u32 Wcslen(wchar* pString)
{
    wchar* pStringStart = pString;

    do
    {
    } while (*pStringStart++ != 0);

    return (u32)(pStringStart - (pString + 1));
}

wchar* Wcscpy(wchar* pDest, wchar* pSource)
{
    u32 StrOffset = (u8*)pSource - (u8*)pDest;
    wchar* pDestStart = pDest + 1;
    wchar Letter = *(wchar*)((u8*)pDest + StrOffset);

    *pDest = Letter;
    if (Letter == 0)
    {
        return pDest;
    }
    do
    {
        Letter = *(wchar*)((u8*)pDestStart + StrOffset);
        *pDestStart = Letter;
        pDestStart++;
    } while (Letter != 0);
    return pDest;
}

wchar* Wcscpy(wchar* pDest, u8* pSource)
{
    u32 i = 0;
    u8 Letter = pSource[0];

    if (Letter != 0)
    {
        wchar* pCurrent = pDest;
        do
        {
            *pCurrent++ = Letter;
            i++;
            Letter = pSource[i];
        } while (Letter != 0);
    }
    *(wchar*)((u8*)pDest + (i * 2)) = 0;
    return pDest;
}

u32 WriteWChar(wchar* pDest, wchar Letter, u64 NumCounted)
{
    *(pDest + NumCounted++) = Letter;
    return NumCounted;
}

u32 Write_Multi_Char(wchar* pStream, wchar Letter, u64 Padding, u64 NumCounted)
{
    u32 i = 0;
    u32 Offset = NumCounted;
    u8* pCurrent = (u8*)pStream + NumCounted;

    if (i < Padding)
    {
        pCurrent += NumCounted;
        do
        {
            *(wchar*)pCurrent = Letter;
            i++;
            pCurrent += 2;
            Offset++;
        } while (i < Padding);
    }
    return Offset;
}

u32 Write_String(wchar* pStream, wchar* pString, u64 Amount, u64 NumCounted)
{
    u32 i = 0;
    u32 Offset = NumCounted;
    u8* pCurrent = (u8*)pStream + NumCounted;

    if (i < Amount)
    {
        pCurrent += NumCounted;
        do
        {
            *(wchar*)pCurrent = *pString++;
            i++;
            pCurrent += 2;
            Offset++;
        } while (i < Amount);
    }
    return Offset;
}

// u32 WOutput(wchar* pStream, wchar* pFormat, va_list argptr)
// {
// }

u32 Wsprintf(wchar* pBuffer, wchar* FormatString)
{
}

// u32 WVsprintf(wchar* pBuffer, wchar* FormatString, va_list argList)
// {
// }
