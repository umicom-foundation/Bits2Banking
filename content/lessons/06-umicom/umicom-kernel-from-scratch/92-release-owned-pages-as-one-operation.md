<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/92-release-owned-pages-as-one-operation.md

PURPOSE:
Teach release owned pages as one operation through the real Kernel allocator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Release owned pages as one operation

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Release is also a transaction

A memory transaction here means an operation whose refusal leaves ownership unchanged. It does not mean a database or CPU transactional-memory instruction. Releasing a run must first prove that every requested page is currently allocated. Clearing early pages before discovering a problem in the last page would leave a partial result that is difficult to recover.

Run the release scenario after studying the first two lessons. It allocates four pages, then deliberately frees the third page through the existing single-page interface. A request to free all four pages must now return NOT_ALLOCATED. The other three pages remain allocated.

## Separate admission from mutation

This excerpt describes the deliberate-hole fixture; the complete lab checks every return value. The allocator first validates the aligned starting address and checks count against the remaining managed frames. It then inspects the entire range before clearing any allocated bits. A reserved page produces RESERVED_FRAME instead of being released.

~~~c
/* first identifies an owned four-page run. */
UmicomKernelPhysicalMemoryFreeFrame(first + 2U * UMICOM_KERNEL_PAGE_SIZE);
UmicomKernelMemoryStatus status =
    UmicomKernelPhysicalMemoryFreeFrames(first, 4U);
/* The third page is already free: status is NOT_ALLOCATED.
 * Pages one, two and four retain their allocation state. */
~~~

## Recover using the ownership you still hold

After the refused whole-run release, the lab releases the first two pages as one operation and the fourth page as a single frame. It does not try to free the third page again. The expected final snapshot is allocated=0, reserved=0 and free=16.

The allocator records state per frame, not an allocation identifier. It permits releasing a subrange, and it cannot prove that two allocated neighbouring pages belong to the same caller. Keep the address, count and remaining ownership in the consumer. A stale address that has been freed and allocated to somebody else cannot be recognized by these bitmaps.

## Avoid arithmetic that can wrap

The free operation compares frameCount with totalFrames - firstIndex. It does not first compute frameCount * 4096 from unchecked input. This makes a huge count an ordinary refused range instead of allowing multiplication to wrap into a deceptively small number.

A zero count is invalid. A misaligned starting address is INVALID_ALIGNMENT. A range extending beyond managed RAM is OUTSIDE_RAM. These checks occur before any ownership bit is cleared. Error ordering is useful for diagnosis, but a caller should normally correct the complete request rather than depending on one invalid field hiding another.

## Exercise and answer

Expected answer: RESERVED_FRAME, with the first three allocations unchanged. The existing free-reserved-tail regression expresses this case. The free-hole-tail and free-hole-middle cases cover missing allocation bits at different positions.

Failure atomicity assumes serialized access. Another CPU or interrupt modifying the global allocator between validation and commit would violate that assumption. Do not present these routines as an SMP-safe allocator; locking and interrupt ownership remain a separate design task.

1. Change the lab so the fourth page is reserved instead of allocated, while the first three are allocated.
2. Predict the result of releasing all four pages.
3. Capture per-frame state and counters before and after the refused operation.
4. Release only the pages and reservation that the synthetic fixture owns.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/README.md) · [Complete C example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/main.c)

[Course contents](index.md) · [Previous lesson](91-explain-fragmentation-before-retrying.md) · [Next lesson](93-qualify-contiguous-memory-without-device-claims.md)
