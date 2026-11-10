#ifndef GCMALLOC_H
#define GCMALLOC_H

#include "types.h"

#include "EngineX/EXMalloc.h"

// no fucking way
// extern "C" changes the mangling. Maybe this is why my mangling is fucked.
extern "C" void _initalize_heap_memory();

enum EXMheap
{
    MemHeap0 = 0,
    MemHeap1 = 1,
    MemHeap2 = 2,
    MemHeap3 = 3
};

extern u32 _SDataHeapSize;
extern u32 _LDataHeapSize;

u32 _get_max_heap_size();

struct EXHeapSizes
{ // 0xc
private:
    /* 0x0 */ u32 m_MaxHeapSize;
    /* 0x4 */ u32 m_Heap0Size;
    /* 0x8 */ u32 m_Heap1Size;

public:
    // EXHeapSizes& operator=();
    EXHeapSizes(u32 MaxHeapSize, u32 Heap0Size, u32 Heap1Size)
    {
        SetMaxHeapSize(MaxHeapSize);
        m_Heap0Size = Heap0Size;
        m_Heap1Size = Heap1Size;
    }
    void SetHeap0Size(u32 Heap0Size)
    {
        m_Heap0Size = Heap0Size;
    }
    void SetHeap1Size(u32 Heap1Size)
    {
        m_Heap1Size = Heap1Size;
    }
    u32 MaxHeapSize()
    {
        return m_MaxHeapSize;
    }
    u32 Heap0Size()
    {
        return m_Heap0Size;
    }
    u32 Heap1Size()
    {
        return m_Heap1Size;
    }

private:
    void SetMaxHeapSize(unsigned long MaxHeapSize)
    {
        m_MaxHeapSize = MaxHeapSize;
    }
};

void* _malloc(unsigned int size);
void _free(void* ptr);
void _adjust_heap_sizes(EXHeapSizes& Sizes);
void _initalize_heap(EXMemHeap& Heap, EXMheap HeapId, unsigned char** ppMem, unsigned long Size,
                     char* Name);

#endif // GCMALLOC_H
