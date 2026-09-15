#ifndef GCMALLOC_H
#define GCMALLOC_H

// no fucking way
// extern "C" changes the mangling. Maybe this is why my mangling is fucked.
extern "C" void _initalize_heap_memory();

#endif // GCMALLOC_H
