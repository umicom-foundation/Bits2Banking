/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/read-record.S
 *
 * PURPOSE:
 *   Read a field at the offset verified by an independent C declaration.
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
    .globl btb_record_units
btb_record_units:
    // The matching C fixture verifies this native record offset at build time.
    ldr w0, [x0, #4]
    ret
