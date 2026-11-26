/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/call-an-external.S
 *
 * PURPOSE:
 *   Preserve the link register before invoking a separately compiled function.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

    .text
    .p2align 2
    .globl btb_call_external
    .type btb_call_external, %function
btb_call_external:
    // The nested BL overwrites X30. Save it with the previous frame pointer.
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    bl umc_constant_return
    ldp x29, x30, [sp], #16
    ret
    .size btb_call_external, .-btb_call_external
