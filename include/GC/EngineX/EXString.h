#ifndef EXSTRING_H
#define EXSTRING_H

#include "types.h"
#include "EXMalloc.h"

struct EXStringData
{
    u32 Refs;
    u16 Len;
    u16 Alloc;
};

struct EXStringArray;

struct EXString
{
    char* m_pData;

    EXString(char* pString);
    EXString(char* pString, u16 len);
    EXString(EXString& Str);
    EXString()
    {
        m_pData = NULL;
    }
    // ~EXString();
    void Empty();
    EXString& operator=(char* pString);
    EXString& operator=(EXString& Str);
    EXString& operator+=(EXString& Str);
    EXString& operator+=(char* pStr);
    EXString& operator+=(char ch);
    void MakeUnique();
    void ToUpper();
    void ToLower();
    u16 Length() const;
    u16 Capacity() const;
    s32 Find(char ch, long pos) const;
    Bool IsEmpty() const;
    char* GetBuffer(u16 MinLen);
    void ReleaseBuffer();
    s8 Compare();
    s8 CompareNoCase(EXString& Str) const;
    // char* operator char *();
    char* c_str();
    char* data();
    // char* data();
    EXString Token(int nTok, char chSep, Bool fNullTokensOK) const;
    // EXString Token();
    int Tokenise(EXStringArray& Tokens, EXString& Sep, Bool fNullTokensOK) const;
    s16 Format(char* FmtString, ...);

    void AllocMem(u16 nLength);
    void ReallocMem(u16 nLength);
    void DeallocMem();
    int IncRefCount();
    void SetLength(u16 aNewLength);
};

Bool operator==(EXString& Str1, EXString& Str2);

struct EXStringArray
{
    int m_iAlloc;
    int m_iGrowBy;
    int m_iSize;
    EXString* m_pData;

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXStringArray& operator=();
    EXStringArray(int nSize = 0, int iGrowBy = -1);
    ~EXStringArray();
    // ~EXStringArray();
    int Size();
    int GetUpperBound();
    void SetSize(int nNewSize, int nGrowBy);
    // void SetGrowBy(EXStringArray*, int, void);
    void FreeExtra();
    void RemoveAll();
    EXString& GetAt();
    void SetAt();
    EXString* GetData();
    // EXString* GetData();
    void SetAtGrow(int nIndex, EXString& newElement);
    int Add(EXString& newElement);
    int Append();
    void Copy();
    // EXString& operator[]();
    // EXString& operator[]();
    void InsertAt();
    void RemoveAt(int nIndex, int nCount);
    // void InsertAt();
};

#endif // EXSTRING_H
