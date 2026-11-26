/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/write-word.S
 *
 * PURPOSE:
 *   Return the low 32 bits of a native addition.
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
    .globl btb_word_step
btb_word_step:
    // A W-register destination clears the upper half of X0.
    add w0, w0, #1
    ret
