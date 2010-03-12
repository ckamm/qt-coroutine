#include <stdlib.h>

void initializeStack(void *data, int size, void (*entry)(), void **stackPointer)
{
    void* stackBottom = (char*)data + size;
    // align to 16 byte
    stackBottom = (void*)((size_t)stackBottom & ~0xF);
    
    void **p = (void**)stackBottom;

    *(--p) = 0; // align
    *(--p) = (void*)entry; // rip
    *(--p) = stackBottom; // ebp
    *(--p) = 0; // ebx
    *(--p) = 0; // esi
    *(--p) = 0; // edi
    *(--p) = (void*)0x00001f80; // SIMD floating point control default
    *(--p) = (void*)0x0000033f; // floating point control default
    
    *stackPointer = p;
}
