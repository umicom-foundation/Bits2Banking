<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/18-store-recent-events-in-a-ring.md

PURPOSE:
Explain the lesson: Store recent events in a fixed ring.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Store recent events in a fixed ring

## Prepare
Read labs/native/diagnostic-ring/ring.h and ring.c. The README gives the compiler setup. A diagnostic is a small record describing an event; this example stores numeric source and event codes rather than message text.

A ring uses an array repeatedly. When an index reaches the end, it wraps to the beginning. This ring has eight record slots.

## Follow one insertion
On an empty ring, head is zero and count is zero. The insertion offset is (head + count) modulo eight. After storing the first record, count becomes one.

Modulo gives the remainder after division. It converts an advancing logical position into a valid array position.

## Lab
Draw eight numbered cells. Insert records one through five, recording head, count and next insertion offset after each operation.

Expected: head stays zero; count becomes five; the next offset is five.

## Exercise and explanation
Why keep count separately from head? The same head position can describe an empty or full ring. Count distinguishes how many records are available.

## Troubleshoot
The live ring must be zero-initialised and initialised through BtbDiagnosticRingInit. Do not populate public structure fields as a substitute for the API. The self pointer also gives this particular model an address-stability requirement.

This structure supports recent local observations. It has no persistence or cryptographic integrity and is not a replacement for a financial audit ledger.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](17-digests-and-meaning.md) · [Next lesson](19-separate-storage-order-from-reading-order.md)

