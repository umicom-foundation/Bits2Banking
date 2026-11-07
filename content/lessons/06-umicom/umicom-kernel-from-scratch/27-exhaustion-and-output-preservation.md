<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/27-exhaustion-and-output-preservation.md

PURPOSE:
Explain the lesson: Test exhaustion without losing the caller's output.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test exhaustion without losing the caller's output

## Prepare
Read the test file and the physical-frame-pool README. A test oracle is the rule used to decide whether an observed result is correct. Here the oracle can be calculated from the number of reserved frames.

After initialization there are 128 - 8 = 120 free entries. Reserving four more leaves 116. Every successful allocation consumes one free entry until none remain.

## Follow the loop
The regression stores successful addresses in an array. It stops when allocation refuses or the array capacity is reached. The successful count should equal total frames minus reserved frames.

The next call supplies an output initialized to 0xBEEF. This is a sentinel: a recognizable value chosen to expose unintended writes. On exhaustion, the function returns NOT_AVAILABLE and leaves that output untouched.

## Exercise
Write a table containing:
1. reserved count before the loop;
2. successful allocation count;
3. owned count after the loop;
4. refused-call status;
5. sentinel after refusal.

With twelve reserved entries, expected values are 12, 116, 116, NOT_AVAILABLE and 0xBEEF.

## Why both checks matter
Checking only the return value would miss an implementation that also overwrote the output with an unusable address. Checking only the output would miss an implementation reporting success without allocating anything.

Release one owned frame and allocate again. Exactly one additional allocation should now succeed, restoring the exhausted state.

## Troubleshoot
A test loop must itself be bounded. Never keep allocating until “something eventually fails” without limiting the result array index. The library's capacity contract and the test's own storage bound should both be visible in the code.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/test_frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](26-release-and-double-release.md) · [Next lesson](28-snapshots-and-padding.md)

