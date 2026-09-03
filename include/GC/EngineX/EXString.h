#ifndef EXSTRING_H
#define EXSTRING_H

#include "types.h"

struct EXStringData
{
    u32 Refs;
    u16 Len;
    u16 Alloc;
};

struct EXString
{
    char* m_pData;

    EXString(char* pString);
    EXString();
    // EXString();
    // EXString();
    // EXString(EXString*, int, void);
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
    EXString Token();
    // EXString Token();
    int Tokenise();
    s16 Format();

    void AllocMem(u16 nLength);
    void ReallocMem(u16 nLength);
    void DeallocMem();
    int IncRefCount();
    void SetLength(u16 aNewLength);
};

struct EXStringArray
{
    int m_iAlloc;
    int m_iGrowBy;
    int m_iSize;
    EXString* m_pData;

    // EXStringArray& operator=();
    EXStringArray();
    ~EXStringArray();
    EXStringArray(s32, s32);
    // EXStringArray(EXStringArray*, int, void);
    int Size();
    int GetUpperBound();
    void SetSize();
    // void SetGrowBy(EXStringArray*, int, void);
    void FreeExtra();
    void RemoveAll();
    EXString& GetAt();
    void SetAt();
    EXString* GetData();
    // EXString* GetData();
    void SetAtGrow();
    int Add();
    int Append();
    void Copy();
    // EXString& operator[]();
    // EXString& operator[]();
    void InsertAt();
    void RemoveAt();
    // void InsertAt();
};

#endif // EXSTRING_H
