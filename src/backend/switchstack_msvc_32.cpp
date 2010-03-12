extern "C" {
void __declspec(naked) _switchStackInternal(void* to, void** from)
{
    __asm {
    // save callee-saved registers
    PUSH EBP
    MOV EBP, ESP
    PUSH EBX
    PUSH ESI
    PUSH EDI

    // store SIMD floating point control word
    SUB ESP, 4
    STMXCSR [ESP]

    // store floating point control bytes
    SUB ESP, 4
    FSTCW [ESP]

    // save the old stack pointer
    MOV EDX, dword ptr 12[EBP]
    MOV [EDX], ESP
    // set the new stack pointer
    MOV ESP, dword ptr 8[EBP]

    // restore floating point control bytes
    FNCLEX
    FLDCW [ESP]
    ADD ESP, 4

    // restore SIMD floating point control word
    LDMXCSR [ESP]
    ADD ESP, 4

    // pop callee-saved registers
    POP EDI
    POP ESI
    POP EBX
    POP EBP        
    
    RET
    }
}
}
