/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/riscv-sequences/bits.S
 *
 * PURPOSE:
 *   Demonstrate shifts, bit composition and parity with base RV64 instructions.
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
    .globl BtbRotateLeft64
    .type BtbRotateLeft64, @function
BtbRotateLeft64:
    andi a1, a1, 63
    beqz a1, .Lrotate_done
    li t0, 64
    sub t0, t0, a1
    sll t1, a0, a1
    srl a0, a0, t0
    or a0, a0, t1
.Lrotate_done:
    ret
    .size BtbRotateLeft64, .-BtbRotateLeft64

    .globl BtbParity64
    .type BtbParity64, @function
BtbParity64:
    mv t0, a0
    li a0, 0
.Lparity_loop:
    beqz t0, .Lparity_done
    andi t1, t0, 1
    xor a0, a0, t1
    srli t0, t0, 1
    j .Lparity_loop
.Lparity_done:
    ret
    .size BtbParity64, .-BtbParity64
    .section .note.GNU-stack,"",@progbits
