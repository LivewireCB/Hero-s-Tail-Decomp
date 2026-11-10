#include "EngineX/GC/GCMalloc.h"

extern "C" void* memset(void*, int, size_t);

extern EXMemHeap* _SystemHeap;
extern EXMemHeap* _SystemHeapList[4];
extern EXMemHeap _SDataHeap;
extern EXMemHeap _LDataHeap;
extern unsigned char* _SDataHeapMemory;
extern unsigned char* _LDataHeapMemory;
extern void* (*_register_malloc)(unsigned int);
extern void (*_register_free)(void*);

extern u8 GC_Initialised_Heaps_Count;
extern void* GC_Heap0_Debug_Ptr;
extern u32 GC_Heap0_Debug_Size;
extern void* GC_Heap1_Debug_Ptr;
extern u32 GC_Heap1_Debug_Size;
extern u32 GC_MapFile_Size;

void GC_Init();
void GC_Die(char* Msg);
void* MyOSAlloc(unsigned long Size, char* Name);

void* _malloc(unsigned int size)
{
    return _SystemHeap->_EXAlloc(size, 0);
}

void _free(void* ptr)
{
    EXFree(ptr);
}

u32 _get_max_heap_size()
{
    return 0x4000000;
}

extern "C" void _initalize_heap_memory()
{
    GC_Init();

    EXHeapSizes Sizes(_get_max_heap_size(), _SDataHeapSize, _LDataHeapSize);
    _adjust_heap_sizes(Sizes);

    memset(_SystemHeapList, 0, sizeof(_SystemHeapList));

    _initalize_heap(_SDataHeap, MemHeap0, &_SDataHeapMemory, Sizes.Heap0Size() - GC_MapFile_Size,
                    "Default Heap");
    _initalize_heap(_LDataHeap, MemHeap1, &_LDataHeapMemory, Sizes.Heap1Size(), "Large Data Heap");

    _SystemHeap = _SystemHeapList[0];
    _register_malloc = _malloc;
    _register_free = _free;
}

void _initalize_heap(EXMemHeap& Heap, EXMheap HeapId, unsigned char** ppMem, unsigned long Size,
                     char* Name)
{
    void* pMem = MyOSAlloc(Size, "GameHeap");

    if (GC_Initialised_Heaps_Count == 0)
    {
        GC_Heap0_Debug_Ptr = pMem;
        GC_Initialised_Heaps_Count++;
        GC_Heap0_Debug_Size = Size;
    }
    else if (GC_Initialised_Heaps_Count == 1)
    {
        GC_Heap1_Debug_Ptr = pMem;
        GC_Initialised_Heaps_Count++;
        GC_Heap1_Debug_Size = Size;
    }

    if (pMem == 0)
    {
        GC_Die("Can't allocate memory\n");
    }

    *ppMem = (unsigned char*)pMem;
    Heap.Init(pMem, Size, HeapId, Name);
}
