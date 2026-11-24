/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/checked-integers/inspect_add_flags.S
 *
 * PURPOSE:
 *   Inspect separate carry and signed overflow condition codes in an x86-64 object.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

    .text
    .globl btb_inspect_add_flags
btb_inspect_add_flags:
    /* Signed maximum plus one sets OF. The unsigned sum has no carry. */
    movl $0x7fffffff, %eax
    addl $1, %eax
    seto %dl
    setc %cl
    /* This lesson assembles and inspects the object without running it. */
    ret
