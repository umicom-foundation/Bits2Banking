/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/riscv-sequences/minimum.S
 *
 * PURPOSE:
 *   Contrast signed and unsigned ordering through callable RV64 functions.
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
    .globl BtbMinSigned64
    .type BtbMinSigned64, @function
BtbMinSigned64:
    bge a1, a0, .Lsigned_done
    mv a0, a1
.Lsigned_done:
    ret
    .size BtbMinSigned64, .-BtbMinSigned64

    .globl BtbMinUnsigned64
    .type BtbMinUnsigned64, @function
BtbMinUnsigned64:
    bgeu a1, a0, .Lunsigned_done
    mv a0, a1
.Lunsigned_done:
    ret
    .size BtbMinUnsigned64, .-BtbMinUnsigned64
    .section .note.GNU-stack,"",@progbits
