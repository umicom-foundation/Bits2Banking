<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/24-reserve-a-range-before-allocation.md

PURPOSE:
Explain the lesson: Reserve a whole frame range or leave it unchanged.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reserve a whole frame range or leave it unchanged

## Prepare
Open `BtbFramePoolReserve` and the lab's test file. Build commands remain in the physical-frame-pool README. A range is a starting index plus a count; it does not mean the index of the last item.

The pool contains indices 0 through 127. Reserving first 12, count 4 covers 12, 13, 14 and 15. Index 16 is outside that request.

## Two separate passes
The first loop checks that every requested frame is FREE. The second loop changes them all to RESERVED. If a conflict occurs during the first loop, no frame has changed.

This separation is called failure atomicity: an operation either completes its requested state change or leaves the old state intact. It is not a statement about multiple processor threads; this lab has a single owner.

## Trace a conflict
1. Initialize the pool: 0–7 are reserved.
2. Reserve 12–15 successfully.
3. Request first 10, count 4.
4. The checker sees free entries 10 and 11, then reserved entry 12.
5. It returns NOT_AVAILABLE. Entries 10 and 11 remain free.

A one-pass “check then immediately mark each item” loop would reserve 10 and 11 before discovering the conflict.

## Exercise
Draw the state before and after both requests. Count reserved frames. Expected count after step 2 is twelve; after the refused request it is still twelve.

## Boundary review
The guard uses `count > BTB_FRAME_COUNT - first` after verifying that first is in range. This avoids adding an unchecked large count to first. Try first 127 with count 1, then count 2, on suitable free entries and predict why only the first range is valid.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](23-alignment-and-address-validation.md) · [Next lesson](25-first-fit-and-reuse.md)

