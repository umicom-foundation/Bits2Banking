/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/sum-checked-bytes.S
 *
 * PURPOSE:
 *   Admit a bounded byte span before loading its first byte.
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
    .globl btb_sum_checked_bytes
btb_sum_checked_bytes:
    // X1 is the supplied byte count. Reject an oversized span immediately.
    cmp x1, #4
    b.hi .Lrefuse
    mov w2, wzr
    cbz x1, .Lsuccess
    cbz x0, .Lrefuse
.Lread:
    ldrb w3, [x0], #1
    add w2, w2, w3
    subs x1, x1, #1
    b.ne .Lread
.Lsuccess:
    mov w0, w2
    ret
.Lrefuse:
    // UINT32_MAX cannot be produced by summing four bytes.
    mov w0, #-1
    ret
