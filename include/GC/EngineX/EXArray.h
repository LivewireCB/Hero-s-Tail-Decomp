#ifndef EXARRAY_H
#define EXARRAY_H

#include "types.h"

// Member functions that are not defined inline are instantiated in EXTemplates.
template <class T, class ARG_T> struct EXArray
{
protected:
    /* 0x00 */ int m_iAlloc;
    /* 0x04 */ int m_iGrowBy;
    /* 0x08 */ int m_iSize;
    /* 0x0c */ T* m_pData;

public:
    EXArray();
    virtual ~EXArray();

    int Size()
    {
        return m_iSize;
    }

    void SetSize(int nNewSize, int nGrowBy = -1);

    T& ElementAt(int nIndex)
    {
        return m_pData[nIndex];
    }

    T* GetData()
    {
        return m_pData;
    }

    T& operator[](int nIndex)
    {
        return m_pData[nIndex];
    }
};

#endif // EXARRAY_H
