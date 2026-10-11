/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/http-header-scanner/scan_riscv64.S
 * PURPOSE: Bounded CRLF scan for RISC-V 64-bit ELF calling convention.
 *---------------------------------------------------------------------------*/
#if !defined(__riscv) || __riscv_xlen != 64
#error "This lesson requires RISC-V 64-bit."
#endif
    .text
    .globl BitsHttpContainsCrlfAsm
    .type BitsHttpContainsCrlfAsm, @function
BitsHttpContainsCrlfAsm:
    /* a0: borrowed byte address; a1: count. Result in a0. */
    beqz a0, .Lscan_none
    li t0, 2
    bltu a1, t0, .Lscan_none
    addi a1, a1, -1
.Lscan_pair:
    lbu t0, 0(a0)
    li t1, 13
    bne t0, t1, .Lscan_next
    lbu t0, 1(a0)
    li t1, 10
    beq t0, t1, .Lscan_yes
.Lscan_next:
    addi a0, a0, 1
    addi a1, a1, -1
    bnez a1, .Lscan_pair
.Lscan_none:
    li a0, 0
    ret
.Lscan_yes:
    li a0, 1
    ret
    .size BitsHttpContainsCrlfAsm, .-BitsHttpContainsCrlfAsm
    .section .note.GNU-stack,"",@progbits
