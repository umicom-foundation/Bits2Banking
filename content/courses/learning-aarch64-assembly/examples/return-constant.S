/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/return-constant.S
 *
 * PURPOSE:
 *   Construct a signed 32-bit return value from two immediate fields.
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
    .globl umc_constant_return
umc_constant_return:
    // The low and high halfwords together represent -70000 as int32.
    movz w0, #0xee90
    movk w0, #0xfffe, lsl #16
    ret
