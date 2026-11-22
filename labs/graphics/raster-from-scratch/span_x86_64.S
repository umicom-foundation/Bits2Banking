/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/span_x86_64.S
 *
 * PURPOSE:
 *   Fill a verified RGB pixel span using the Windows and SysV x86-64 ABIs.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

.text
.globl umicom_raster_fill_span_asm
#ifndef _WIN32
.type umicom_raster_fill_span_asm, @function
#endif
umicom_raster_fill_span_asm:
    /* Map incoming C ABI arguments into the same volatile working registers. */
#ifdef _WIN32
    movq %rcx, %r10
    movq %rdx, %r11
    movl %r8d, %eax
#else
    movq %rdi, %r10
    movq %rsi, %r11
    movl %edx, %eax
#endif
    testq %r11, %r11
    jz .Ldone

    /* Split 0xRRGGBB without relying on the in-memory order of a C integer. */
    movl %eax, %r8d
    shrl $16, %r8d
    movl %eax, %r9d
    shrl $8, %r9d
.Lstore:
    movb %r8b, 0(%r10)
    movb %r9b, 1(%r10)
    movb %al, 2(%r10)
    addq $3, %r10
    decq %r11
    jnz .Lstore
.Ldone:
    ret
#ifndef _WIN32
.size umicom_raster_fill_span_asm, .-umicom_raster_fill_span_asm
.section .note.GNU-stack, "", @progbits
#endif
