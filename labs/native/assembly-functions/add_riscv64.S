/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/assembly-functions/add_riscv64.S
 * PURPOSE: Implement the same unsigned 32-bit addition for RV64 ELF ABI.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#if !defined(__riscv) || __riscv_xlen != 64
#error "Compile this file only for RV64."
#endif
    .text
    .globl AddTwoAssembly
    .type AddTwoAssembly, @function
AddTwoAssembly:
    /* a0/a1 carry argument registers; addw computes the low 32-bit sum.
     * Under the RV64 psABI, 32-bit scalar results are sign-extended in a0. */
    addw a0, a0, a1
    ret
    .size AddTwoAssembly, .-AddTwoAssembly
    .section .note.GNU-stack,"",@progbits
