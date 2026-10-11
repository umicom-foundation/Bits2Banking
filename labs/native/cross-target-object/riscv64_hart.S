/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/cross-target-object/riscv64_hart.S
 * PURPOSE: Show one RV64 machine-mode CSR read in a relocatable object.
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
    .section .text,"ax",@progbits
    .align 2
    .globl BtbRiscvReadHartId
    .type BtbRiscvReadHartId,@function
BtbRiscvReadHartId:
    /* mhartid is a privileged CSR. This code is for machine-mode study only.
     * It cannot be called safely from an ordinary user-mode application. */
    csrr a0, mhartid
    ret
    .size BtbRiscvReadHartId, .-BtbRiscvReadHartId
    .section .note.GNU-stack,"",@progbits
