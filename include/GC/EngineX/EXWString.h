#ifndef EXWSTRING_H
#define EXWSTRING_H

#include "types.h"

#include "EXMalloc.h"
#include "EXString.h"

struct EXWStringArray;

struct EXWString
{ // 0x4
protected:
    /* 0x0 */ wchar* m_pData;

public:
    EXWString()
    {
        m_pData = NULL;
    }
    EXWString(wchar* pString);
    EXWString(wchar* pString, u16 len);
    EXWString(char* pString);
    EXWString(EXWString& Str)
    {
        m_pData = Str.m_pData;
        IncRefCount();
    }
    ~EXWString()
    {
        DeallocMem();
    }
    void Empty();
    EXWString& operator=(wchar* pString);
    EXWString& operator=(char* pString);
    EXWString& operator=(EXWString& Str);
    EXWString& operator+=(EXWString& Str);
    EXWString& operator+=(wchar* pStr);
    EXWString& operator+=(char* pStr);
    EXWString& operator+=(char ch);
    wchar operator[](int ID);
    void MakeUnique();
    void ToUpper();
    void ToLower();
    u16 Length() const;
    u16 Capacity() const;
    s32 Find(wchar ch, s32 pos) const;
    Bool IsEmpty() const;
    wchar* GetBuffer(u16 MinLen);
    void ReleaseBuffer();
    s8 Compare(EXWString& Str) const;
    s8 CompareNoCase(EXWString& Str) const;
    wchar* c_str();
    wchar* data();
    EXWString Token(int nTok, wchar chSep, Bool fNullTokensOK) const;
    EXWString Token(int nTok, EXWString& Sep, Bool fNullTokensOK) const;
    int Tokenise(EXWStringArray& Tokens, EXWString& Sep, Bool fNullTokensOK) const;
    s16 Format(wchar* FmtString, ...);

protected:
    void AllocMem(u16 nLength);
    void ReallocMem(u16 nLength);
    void DeallocMem();
    int IncRefCount();
    void SetLength(u16 aNewLength);
};

EXWString operator+(EXWString& aLStr, wchar* apRStr);

struct EXWStringArray
{ // 0x10
protected:
    /* 0x0 */ int m_iAlloc;
    /* 0x4 */ int m_iGrowBy;
    /* 0x8 */ int m_iSize;
    /* 0xc */ EXWString* m_pData;

public:
    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXWStringArray& operator=();
    EXWStringArray(int nSize = 0, int iGrowBy = -1);
    ~EXWStringArray();
    int Size();
    int GetUpperBound();
    void SetSize(int nNewSize, int nGrowBy);
    void FreeExtra();
    void RemoveAll();
    EXWString& GetAt();
    void SetAt();
    EXWString* GetData();
    void SetAtGrow(int nIndex, EXWString& newElement);
    int Add(EXWString& newElement);
    int Append();
    void Copy();
    void InsertAt();
    void RemoveAt();
};

#endif // EXWSTRING_H
