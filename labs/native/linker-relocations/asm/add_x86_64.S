/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: asm/add_x86_64.S
 * PURPOSE: C ABI leaf function for Windows x64 and ELF System V x86-64.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#if !defined(__x86_64__)
#error "This Assembly example requires an x86-64 target."
#endif
    .text
    .globl BtbAssemblyAddU32
#if defined(__ELF__)
    .type BtbAssemblyAddU32, @function
#endif
BtbAssemblyAddU32:
#if defined(_WIN32)
    /* Windows x64 uses ECX and EDX for the first two integer parameters. */
    movl %ecx, %eax
    addl %edx, %eax
#else
    /* Linux System V x86-64 uses EDI and ESI. */
    movl %edi, %eax
    addl %esi, %eax
#endif
    ret
#if defined(__ELF__)
    .size BtbAssemblyAddU32, .-BtbAssemblyAddU32
    .section .note.GNU-stack,"",@progbits
#endif
