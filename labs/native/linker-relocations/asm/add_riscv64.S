/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: asm/add_riscv64.S
 * PURPOSE: Same C ABI leaf operation using RISC-V 64 argument registers.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#if !defined(__riscv) || __riscv_xlen != 64
#error "This Assembly example requires an RV64 target."
#endif
    .text
    .globl BtbAssemblyAddU32
    .type BtbAssemblyAddU32, @function
BtbAssemblyAddU32:
    /* a0 and a1 hold the first two arguments. The low 32 result is returned
     * in a0; unsigned 32-bit return values use the RV64 ABI's width rule. */
    addw a0, a0, a1
    ret
    .size BtbAssemblyAddU32, .-BtbAssemblyAddU32
    .section .note.GNU-stack,"",@progbits
