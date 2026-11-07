/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/riscv-sequences/sum.S
 *
 * PURPOSE:
 *   Walk a borrowed array using RV64 loads and a counted loop.
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
    .globl BtbSum64
    .type BtbSum64, @function
BtbSum64:
    mv t0, a0
    li a0, 0
    beqz a1, .Lsum_done
.Lsum_loop:
    ld t1, 0(t0)
    add a0, a0, t1
    addi t0, t0, 8
    addi a1, a1, -1
    bnez a1, .Lsum_loop
.Lsum_done:
    ret
    .size BtbSum64, .-BtbSum64
    .section .note.GNU-stack,"",@progbits
