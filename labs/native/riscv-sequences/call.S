/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/riscv-sequences/call.S
 *
 * PURPOSE:
 *   Preserve caller state across a nested RV64 function call.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

    .text
    .align 2
    .globl BtbSumAndBias64
    .type BtbSumAndBias64, @function
BtbSumAndBias64:
    /* A nested call overwrites ra and may overwrite a2. Retain the bias in
       s0, preserving the caller's s0 and the 16-byte stack alignment. */
    addi sp, sp, -16
    sd ra, 8(sp)
    sd s0, 0(sp)
    mv s0, a2
    call BtbSum64
    add a0, a0, s0
    ld s0, 0(sp)
    ld ra, 8(sp)
    addi sp, sp, 16
    ret
    .size BtbSumAndBias64, .-BtbSumAndBias64
    .section .note.GNU-stack,"",@progbits
