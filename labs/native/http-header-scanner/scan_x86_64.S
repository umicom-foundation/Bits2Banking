/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/http-header-scanner/scan_x86_64.S
 * PURPOSE: Bounded CRLF scan for x86-64 Windows and System V ABIs.
 *---------------------------------------------------------------------------*/
#if !defined(__x86_64__)
#error "This lesson requires an x86-64 target."
#endif
    .text
    .globl BitsHttpContainsCrlfAsm
#if defined(__ELF__)
    .type BitsHttpContainsCrlfAsm, @function
#endif
BitsHttpContainsCrlfAsm:
#if defined(_WIN32)
    /* Windows x64: RCX is the borrowed byte address; RDX is its count. */
    movq %rcx, %r8
    movq %rdx, %r9
#else
    /* System V: RDI and RSI contain the same two arguments. */
    movq %rdi, %r8
    movq %rsi, %r9
#endif
    xorl %eax, %eax
    testq %r8, %r8
    je .Lscan_done
    cmpq $2, %r9
    jb .Lscan_done
    /* For count N there are exactly N-1 safe adjacent byte pairs. */
    decq %r9
.Lscan_pair:
    cmpb $13, (%r8)
    jne .Lscan_next
    cmpb $10, 1(%r8)
    je .Lscan_yes
.Lscan_next:
    incq %r8
    decq %r9
    jnz .Lscan_pair
.Lscan_done:
    ret
.Lscan_yes:
    movl $1, %eax
    ret
#if defined(__ELF__)
    .size BitsHttpContainsCrlfAsm, .-BitsHttpContainsCrlfAsm
    .section .note.GNU-stack,"",@progbits
#endif
