<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/25-first-fit-and-reuse.md

PURPOSE:
Explain the lesson: Follow first-fit allocation and reuse.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow first-fit allocation and reuse

## Prepare
Open `BtbFramePoolAllocate` and `BtbFramePoolRelease`. The physical-frame-pool README explains how to compile the independent host lab. You do not need to boot a kernel for this exercise.

First-fit here means scanning from index zero and selecting the first FREE entry. Reserved and owned entries are skipped. This makes the result deterministic for a given inventory.

## Walk an allocation
Starting with only frames 0–7 reserved:
1. The scan skips eight entries.
2. It changes frame 8 to OWNED.
3. It increments ownedCount.
4. It writes base + 8 × 4096 into the caller's output.

The output is written only on success. It identifies a modeled physical range; never cast it to a host pointer and dereference it.

## Reuse exercise
Allocate three frames and record their addresses: base + 0x8000, +0x9000 and +0xA000. Release the middle address. Allocate again.

Expected: the new allocation reuses the middle address because it is now the lowest free entry. The pool does not remember that higher entries were visited in a previous scan.

## Discuss the cost
In the worst case the loop inspects all 128 entries. This is acceptable for a small teaching inventory. A larger allocator may use bitmaps or other structures, but the choice must preserve the ownership rules.

## Troubleshoot
If an address repeats while the earlier allocation is still owned, inspect state transitions and accidental pool reinitialization. A repeated address after a valid release is expected. Keep these two situations separate in tests: “same number” alone does not prove either correctness or a double allocation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](24-reserve-a-range-before-allocation.md) · [Next lesson](26-release-and-double-release.md)

