#include <stdlib.h>

void initializeStack(void *data, int size, void (*entry)(), void **stackPointer)
{
    void* stackBottom = (char*)data + size;
    // align to 16 byte
    stackBottom = (void*)((size_t)stackBottom & ~0xF);
    
    void **p = (void**)stackBottom;

    //*(--p) = 0; // align to 16 bytes
    *(--p) = (void*)fn; // rip
    *(--p) = entry; // rbp
    *(--p) = 0; // rbx
    *(--p) = 0; // r12
    *(--p) = 0; // r13
    *(--p) = 0; // r14
    *(--p) = 0; // r15
    *(--p) = 0; // rsi
    *(--p) = 0; // rdi
    *(--p) = 0; // xmm6
    *(--p) = 0; // xmm6
    *(--p) = 0; // xmm7
    *(--p) = 0; // xmm7
    *(--p) = 0; // xmm8
    *(--p) = 0; // xmm8
    *(--p) = 0; // xmm9
    *(--p) = 0; // xmm9
    *(--p) = 0; // xmm10
    *(--p) = 0; // xmm10
    *(--p) = 0; // xmm11
    *(--p) = 0; // xmm11
    *(--p) = 0; // xmm12
    *(--p) = 0; // xmm12
    *(--p) = 0; // xmm13
    *(--p) = 0; // xmm13
    *(--p) = 0; // xmm14
    *(--p) = 0; // xmm14
    *(--p) = 0; // xmm15
    *(--p) = 0; // xmm15
    *(--p) = (void*)0x00001f800000033f; // SIMD and regular floating point control defaults
    
    *stackPointer = p;
}
