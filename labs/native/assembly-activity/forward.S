/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/assembly-activity/forward.S
 *
 * PURPOSE:
 *   Demonstrate an x86-64 C ABI tail call without duplicating the checked C implementation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#if !defined(__x86_64__)
#error This lesson requires an x86-64 target; use the C client on other architectures.
#endif
#if !defined(_WIN32) && !defined(__linux__)
#error This lesson covers Windows x64 and Linux x86-64, not every object format.
#endif
.text
.globl BtbAssemblyActivityNext
#ifndef _WIN32
.type BtbAssemblyActivityNext, @function
#endif
BtbAssemblyActivityNext:
    /* Both functions use the same ABI. Preserve the argument register (ECX on
     * Windows, EDI on Linux), stack and caller return address. The C function
     * writes EAX and returns to the original caller. No additional frame exists. */
    jmp BtbActivityNext
#ifndef _WIN32
.size BtbAssemblyActivityNext, .-BtbAssemblyActivityNext
.section .note.GNU-stack,"",@progbits
#endif
