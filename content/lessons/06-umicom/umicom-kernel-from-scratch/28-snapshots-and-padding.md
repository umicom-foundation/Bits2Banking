<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/28-snapshots-and-padding.md

PURPOSE:
Explain the lesson: Compare unchanged storage with a reliable snapshot.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare unchanged storage with a reliable snapshot

## Prepare
Open the physical-frame-pool regression. This lesson uses only standard C byte copying and comparison. Build and test commands are in the lab README.

A C structure contains named members and may also contain padding bytes inserted for alignment. A structure assignment copies the member values, but it is not the best basis for a requirement that every storage byte remain unchanged.

## Make the observation precise
For a refusal-atomic test, save the original representation:
```c
unsigned char before[sizeof pool];
memcpy(before, &pool, sizeof pool);
/* Perform a call that must refuse without modifying pool. */
CHECK(memcmp(before, &pool, sizeof pool) == 0);
```
`sizeof pool` is the complete storage size. memcpy copies that many bytes; memcmp compares them. The test does not interpret padding as a field.

## Distinguish two questions
“Do these independently created pools have equal member values?” is a semantic comparison. Compare their named fields and states.

“Did this call modify any byte in this one existing object?” is a representation-preservation check. A direct byte snapshot is suitable.

Do not use memcmp as a universal equality operation for arbitrary structures.

## Lab
Take a snapshot of a valid pool, attempt the documented invalid zero-base initialization, and compare afterwards. Expected: INVALID and unchanged bytes. Then allocate successfully and observe that the same preservation condition should no longer hold.

## Troubleshoot
If a test changes from a value snapshot to a byte snapshot, document why. The old version may look simpler but can include padding assumptions unrelated to the contract being tested. Keep the assertion active in release builds rather than relying solely on assert, which may be disabled by NDEBUG.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/test_frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](27-exhaustion-and-output-preservation.md) · [Next lesson](29-address-overflow-and-pool-boundaries.md)

