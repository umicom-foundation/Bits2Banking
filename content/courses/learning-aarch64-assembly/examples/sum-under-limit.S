/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/sum-under-limit.S
 *
 * PURPOSE:
 *   Trace a bounded descending loop and its zero-iteration case.
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
    .globl btb_sum_under_limit
btb_sum_under_limit:
    // Admit at most 16 iterations. A larger unsigned input yields zero.
    mov w1, wzr
    cmp w0, #16
    b.hi .Lsum_done
    cbz w0, .Lsum_done
.Lsum_loop:
    add w1, w1, w0
    subs w0, w0, #1
    b.ne .Lsum_loop
.Lsum_done:
    mov w0, w1
    ret
