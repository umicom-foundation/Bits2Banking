<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/17-digests-and-meaning.md

PURPOSE:
Explain the lesson: Understand what a diagnostic digest proves.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand what a diagnostic digest proves

## Prepare
Open BtbDiagnosticDigest and the receipt definition in the work-dispatch lab. The README includes build instructions and explicitly describes this as a deterministic teaching operation.

A digest reduces a byte sequence to a smaller value. This example uses FNV-1a with a 64-bit unsigned accumulator: each byte is XORed into the value, then the result is multiplied by a fixed constant.

## Trace the input boundary
Submission copies the requested bytes and records their length. Step reads that copy. The digest therefore describes the bytes accepted by the dispatcher, even if the original caller buffer changes afterwards.

It does not establish that a banking request is valid, that a trade was executed, or that an adversary did not alter data elsewhere. This algorithm is for diagnostics, not cryptographic proof.

## Lab
1. Submit a mutable buffer containing ABC with length three.
2. Change the original buffer to XYZ after submission.
3. Process and receive the first request.
4. Compare it with a separate request that submitted ABC unchanged.

Expected diagnostic digests match because submission copied ABC. The receipt length should be three in both cases.

## Check a limit
Different inputs can share a finite digest: there are more possible messages than 64-bit results. A matching digest alone is not universal equality proof. When exact equality matters in a small test, compare the original bytes as well.

## Connect to Framework
For cryptographic hashing, inspect Framework's documented hash APIs and their tests. For financial validity, inspect domain rules and execution acknowledgements. Naming a field “integrity” would not make this diagnostic operation provide either guarantee. Accurate terminology helps a learner choose the correct service.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](16-count-invariants.md)


[Next: Store recent events in a fixed ring](18-store-recent-events-in-a-ring.md)
