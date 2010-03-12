#include <stdlib.h>

void initializeStack(void *data, int size, void (*entry)(), void **stackPointer)
{
    void* stackBottom = (char*)data + size;
    // align to 16 byte
    stackBottom = (void*)((size_t)stackBottom & ~0xF);
    
    void **p = (void**)stackBottom;

    *(--p) = 0; // align
    *(--p) = (void*)entry; // rip
    *(--p) = stackBottom; // rbp
    *(--p) = 0; // rbx
    *(--p) = 0; // r12
    *(--p) = 0; // r13
    *(--p) = 0; // r14
    *(--p) = 0; // r15
    *(--p) = (void*)0x00001f800000033f; // SIMD and regular floating point control defaults
    
    *stackPointer = p;
}
