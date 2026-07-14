#ifndef EXFLAGTEMPLATE_H
#define EXFLAGTEMPLATE_H

#include "types.h"

template <typename T> struct EXFlag
{
    T data;
};

template <> struct EXFlag<unsigned int>
{ // 0x4
protected:
    /* 0x0 */ u32 m_Flags;

public:
    // EXFlag<unsigned int>& operator=();
    EXFlag();
    // EXFlag();
    // u32 operator=();
    void Set();
    void BitSet();
    void BitClr();
    void BitXor();
    void BitModify();
    u32 BitTest();
    Bool BitTestBool();
    void SetBits();
    u32 GetBits();
    // u32 operator unsigned int();
};

template <> struct EXFlag<short unsigned int>
{ // 0x2
protected:
    /* 0x0 */ u16 m_Flags;

public:
    // EXFlag<short unsigned int>& operator=();
    EXFlag();
    // EXFlag();
    // u16 operator=();
    void Set();
    void BitSet();
    void BitClr();
    void BitXor();
    void BitModify();
    u16 BitTest();
    Bool BitTestBool();
    void SetBits();
    u16 GetBits();
    // u16 operator unsigned short();
};

template <> struct EXFlag<unsigned char>
{ // 0x1
protected:
    /* 0x0 */ u8 m_Flags;

public:
    // EXFlag<unsigned char>& operator=();
    EXFlag();
    // EXFlag();
    // u8 operator=();
    void Set();
    void BitSet();
    void BitClr();
    void BitXor();
    void BitModify();
    u8 BitTest();
    Bool BitTestBool();
    void SetBits();
    u8 GetBits();
    // u8 operator unsigned char();
};

typedef EXFlag<unsigned int> EXFlag32;
typedef EXFlag<short unsigned int> EXFlag16;
typedef EXFlag<unsigned char> EXFlag8;

#endif // EXFLAGTEMPLATE_H
