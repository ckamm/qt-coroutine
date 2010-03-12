.text
.globl _switchStackInternal

_switchStackInternal:
    // save callee-saved registers
    push %ebp
    movl %esp, %ebp
    push %ebx
    push %esi
    push %edi

    // store SIMD floating point control word
    sub $4, %esp
    stmxcsr (%esp)

    // store floating point control bytes
    sub $4, %esp
    fstcw (%esp)

    // save the old stack pointer
    movl 0xc(%ebp), %edx
    movl %esp, (%edx)
    // set the new stack pointer
    movl 0x8(%ebp), %esp

    // restore floating point control bytes
    fnclex
    fldcw (%esp)
    add $4, %esp

    // restore SIMD floating point control word
    ldmxcsr (%esp)
    add $4, %esp

    // pop callee-saved registers
    pop %edi
    pop %esi
    pop %ebx
    pop %ebp

    ret
