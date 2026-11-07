<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/29-address-overflow-and-pool-boundaries.md

PURPOSE:
Explain the lesson: Keep the modeled address range inside its integer type.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep the modeled address range inside its integer type

## Prepare
Read `BtbFramePoolInit` and the constants in frame_pool.h. The lab uses uint64_t, an unsigned integer type with exactly 64 bits. Its largest value is UINT64_MAX.

The inventory spans 128 × 4,096 = 524,288 bytes. Before accepting a base, initialization checks whether adding that span would exceed the representable address range.

## Rearrange the inequality
Instead of first computing a potentially overflowing sum, the guard checks:
```c
startAddress > UINT64_MAX - BTB_FRAME_SIZE * BTB_FRAME_COUNT
```
The fixed product fits in uint64_t. Subtracting it from the maximum creates a safe limit for the base.

This implementation conservatively requires the modeled end calculation to fit. Preserve that contract when predicting boundary results.

## Exercise
1. Calculate the span in decimal and hexadecimal.
2. Choose an aligned base well below the limit.
3. Choose an aligned base near UINT64_MAX.
4. Predict which guard handles each input: alignment, overflow or neither.

Expected span is 524,288, or 0x80000. A near-maximum input must also be aligned before it can reach the overflow branch; a misaligned value may return INVALID earlier.

## Write a meaningful regression
Begin with a valid initialized pool. Save its bytes. Pass an aligned base above the safe limit. Expect OVERFLOW and unchanged prior state. Checking a misaligned UINT64_MAX value alone does not specifically exercise the overflow path.

## Connect to real systems
Physical addresses, buffer sizes and file offsets frequently combine a start with a length. Check the arithmetic before creating pointers or indexing memory. This host model teaches the reasoning; hardware address-width and memory-map rules still belong to the target Kernel platform.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](28-snapshots-and-padding.md)


[Next: Model ready, running and waiting tasks](30-model-ready-running-and-waiting.md)
