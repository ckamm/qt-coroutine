.global _switchStackInternal
.section .text 
.def _switchStackInternal ; .scl 2 ; .type 32 ; .endef 

_switchStackInternal:
    // save callee-saved registers
    push %rbp
    movq %rsp, %rbp
    push %rbx
    push %r12
    push %r13
    push %r14
    push %r15

    push %rsi
    push %rdi

    sub $0x10, %rsp
    movupd %xmm6, (%rsp)
    sub $0x10, %rsp
    movupd %xmm7, (%rsp)
    sub $0x10, %rsp
    movupd %xmm8, (%rsp)
    sub $0x10, %rsp
    movupd %xmm9, (%rsp)
    sub $0x10, %rsp
    movupd %xmm10, (%rsp)
    sub $0x10, %rsp
    movupd %xmm11, (%rsp)
    sub $0x10, %rsp
    movupd %xmm12, (%rsp)
    sub $0x10, %rsp
    movupd %xmm13, (%rsp)
    sub $0x10, %rsp
    movupd %xmm14, (%rsp)
    sub $0x10, %rsp
    movupd %xmm15, (%rsp)

    // store SIMD floating point control word
    sub $4, %rsp
    stmxcsr (%rsp)

    // store floating point control bytes
    sub $4, %rsp
    fstcw (%rsp)

    // save the old stack pointer (second arg in rsi)
    movq %rsp, (%rsi)
    // set the new stack pointer (first arg in rdi)
    movq %rdi, %rsp

    // restore floating point control bytes
    fnclex
    fldcw (%rsp)
    add $4, %rsp

    // restore SIMD floating point control word
    ldmxcsr (%rsp)
    add $4, %rsp

    // pop callee-saved registers
    movupd (%rsp), %xmm15
    add $0x10, %rsp
    movupd (%rsp), %xmm14
    add $0x10, %rsp
    movupd (%rsp), %xmm13
    add $0x10, %rsp
    movupd (%rsp), %xmm12
    add $0x10, %rsp
    movupd (%rsp), %xmm11
    add $0x10, %rsp
    movupd (%rsp), %xmm10
    add $0x10, %rsp
    movupd (%rsp), %xmm9
    add $0x10, %rsp
    movupd (%rsp), %xmm8
    add $0x10, %rsp
    movupd (%rsp), %xmm7
    add $0x10, %rsp
    movupd (%rsp), %xmm6
    add $0x10, %rsp

    pop %rdi
    pop %rsi

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    pop %rbp

    retq
