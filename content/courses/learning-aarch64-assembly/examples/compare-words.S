/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/compare-words.S
 *
 * PURPOSE:
 *   Use the same flag-setting instruction for signed and unsigned comparisons.
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
    .globl btb_signed_less
btb_signed_less:
    // The signed condition considers the sign and overflow flags.
    cmp w0, w1
    cset w0, lt
    ret

    .globl btb_unsigned_less
btb_unsigned_less:
    // The unsigned condition compares the magnitudes of the same bits.
    cmp w0, w1
    cset w0, lo
    ret
