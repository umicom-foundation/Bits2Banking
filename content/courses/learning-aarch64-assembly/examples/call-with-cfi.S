/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/call-with-cfi.S
 *
 * PURPOSE:
 *   Describe the saved frame and link register to an ELF stack unwinder.
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
    .globl btb_call_with_cfi
    .type btb_call_with_cfi, %function
btb_call_with_cfi:
    .cfi_startproc
    // Describe both machine stack storage and debugger frame metadata.
    stp x29, x30, [sp, #-16]!
    .cfi_def_cfa_offset 16
    .cfi_offset x29, -16
    .cfi_offset x30, -8
    mov x29, sp
    .cfi_def_cfa_register x29
    bl umc_constant_return
    ldp x29, x30, [sp], #16
    .cfi_def_cfa sp, 0
    .cfi_restore x29
    .cfi_restore x30
    ret
    .cfi_endproc
    .size btb_call_with_cfi, .-btb_call_with_cfi
