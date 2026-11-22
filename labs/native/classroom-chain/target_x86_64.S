/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/classroom-chain/target_x86_64.S
 *
 * PURPOSE:
 *   Compare a classroom target with the same C ABI on Linux and Windows x86-64.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

.text
.globl classroom_meets_target_asm
#if !defined(_WIN32)
.type classroom_meets_target_asm, @function
#endif
classroom_meets_target_asm:
    /* Windows x64 passes the first pointer in RCX. System V passes it in
       RDI. Only caller-saved registers are written here. */
#if defined(_WIN32)
    movq %rcx, %rdx
#else
    movq %rdi, %rdx
#endif
    /* Return C int zero for an absent pointer. A present buffer needs only
       its first byte under this lab's fixed-target rule. */
    xorl %eax, %eax
    testq %rdx, %rdx
    jz .Lreturn
    cmpb $0, (%rdx)
    sete %al
.Lreturn:
    ret
#if !defined(_WIN32)
.size classroom_meets_target_asm, .-classroom_meets_target_asm
.section .note.GNU-stack,"",@progbits
#endif
