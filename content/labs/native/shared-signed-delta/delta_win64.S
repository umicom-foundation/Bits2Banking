/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/shared-signed-delta/delta_win64.S
 *
 * PURPOSE:
 *   Compute a caller-validated 32-bit difference using the Windows x64 C ABI.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#if !defined(_WIN32) || !defined(__x86_64__)
#error This teaching leaf expects the Windows x64 calling convention.
#endif

    .text
    .p2align 4
    .globl UmiLessonBalanceDelta

/* The caller verifies that the mathematical result fits int32_t. The first
 * two integer arguments occupy the low halves of RCX and RDX. The leaf uses
 * only the destination return register and needs no stack frame. */
UmiLessonBalanceDelta:
    movl %ecx, %eax
    subl %edx, %eax
    ret
