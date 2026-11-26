/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/load-byte-views.S
 *
 * PURPOSE:
 *   Show sign extension and zero extension from the same stored byte.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

    .text
    .p2align 2
    .globl btb_load_byte_as_unsigned
btb_load_byte_as_unsigned:
    // The load takes one byte and fills the upper result bits with zeros.
    ldrb w0, [x0]
    ret

    .globl btb_load_byte_as_signed
btb_load_byte_as_signed:
    // Extend the sign bit into the 32-bit C integer return value.
    ldrsb w0, [x0]
    ret
