#ifndef EXSTDFUNCS_H
#define EXSTDFUNCS_H

#include "types.h"

u32 Wcslen(wchar* pString);
wchar* Wcscpy(wchar* pDest, wchar* pSource);
wchar* Wcscpy(wchar* pDest, u8* pSource);
u32 WriteWChar(wchar* pDest, wchar Letter, u64 NumCounted);
u32 Write_Multi_Char(wchar* pStream, wchar Letter, u64 Padding, u64 NumCounted);
u32 Write_String(wchar* pStream, wchar* pString, u64 Amount, u64 NumCounted);
// u32 WOutput(wchar* pStream, wchar* pFormat, va_list argptr);
u32 Wsprintf(wchar* pBuffer, wchar* FormatString);
// u32 WVsprintf(wchar* pBuffer, wchar* FormatString, va_list argList);

#endif // EXSTDFUNCS_H
