/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/assembly-functions/add_x86_64.S
 * PURPOSE: Implement one unsigned C-callable function under Windows and SysV ABIs.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#if !defined(__x86_64__)
#error "Compile this file only for x86-64."
#endif
    .text
    .globl AddTwoAssembly
#if defined(__ELF__)
    .type AddTwoAssembly, @function
#endif
AddTwoAssembly:
#if defined(_WIN32)
    /* Windows x64: first integer arguments in ECX and EDX. */
    movl %ecx, %eax
    addl %edx, %eax
#else
    /* System V x86-64: first integer arguments in EDI and ESI. */
    movl %edi, %eax
    addl %esi, %eax
#endif
    /* EAX is the return-value register. ret returns to the C caller. */
    ret
#if defined(__ELF__)
    .size AddTwoAssembly, .-AddTwoAssembly
    .section .note.GNU-stack,"",@progbits
#endif
