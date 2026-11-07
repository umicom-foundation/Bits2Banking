<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/24-publish-a-snapshot-after-validation.md

PURPOSE:
Explain the lesson: Publish a snapshot after validation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a snapshot after validation

## Prepare
Open BtbDiagnosticRead. A snapshot is a copy of the retained observation values at one point in this single-threaded model.

The function validates the owner, builds a local candidate and assigns the caller's output only after the candidate is complete.

## Trace publication
The candidate starts zero-initialised. It receives count, dropped and each retained record in reading order. One final assignment publishes it.

This arrangement keeps unused candidate fields predictable and avoids partially replacing the caller's result.

## Lab
Choose an invalid copied owner and a previously populated output snapshot. Trace the return path without executing undefined memory access.

Expected: validation returns BAD_STATE before the output assignment. The previous snapshot remains available to the caller.

## Exercise and explanation
Should the interface show the previous snapshot as freshly collected after refusal? No. Preserved data must retain its old status and age. A failed refresh is not a new observation.

## Troubleshoot
When testing byte preservation of a structure, remember that C structures may contain padding. Capture bytes with memcpy if the intended assertion concerns the exact object representation; compare fields when the contract concerns values.

The model does not lock a concurrently changing ring. A multithreaded implementation would need synchronisation or an explicitly designed snapshot protocol before claiming a consistent view.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](23-preserve-address-stable-owners.md) · [Next lesson](25-design-a-diagnostic-view-contract.md)

