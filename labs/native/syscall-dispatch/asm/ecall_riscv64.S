/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/syscall-dispatch/asm/ecall_riscv64.S
 * PURPOSE: Show the RISC-V environment-call instruction at its ABI boundary.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
/*
 * Source-reading exercise ONLY. This file is intentionally NOT part of the
 * hosted CMake programme and does not claim a specific Umicom Kernel syscall
 * number or ABI. An actual user-space wrapper must first be derived from the
 * corresponding Kernel message ABI headers and trap/return contracts.
 * The assembler can examine ecall without running the instruction.
 */
    .text
    .globl BtbIllustrateEnvironmentCall
    .type BtbIllustrateEnvironmentCall, @function
BtbIllustrateEnvironmentCall:
    /* A caller would place an ABI-defined operation in a7 and arguments in
     * a0..a5 BEFORE reaching this instruction. Neither is established here. */
    ecall
    ret
    .size BtbIllustrateEnvironmentCall, .-BtbIllustrateEnvironmentCall
    .section .note.GNU-stack,"",@progbits
