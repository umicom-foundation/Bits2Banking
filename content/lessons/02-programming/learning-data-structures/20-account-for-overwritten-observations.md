<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/20-account-for-overwritten-observations.md

PURPOSE:
Explain the lesson: Account for overwritten observations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Account for overwritten observations

## Prepare
Read the full-ring branch in BtbDiagnosticPush. A bounded structure needs an explicit policy for the ninth event when only eight slots exist.

This ring keeps the newest events and counts how many older records were overwritten.

## Trace the policy
At capacity, the insertion offset points to the oldest record. The implementation advances head, increments dropped and replaces that slot. Count remains eight.

The dropped value is evidence that the retained view is incomplete.

## Lab
Insert thirteen valid events on paper. Record count, dropped and first retained sequence.

Expected: count is eight, dropped is five and the first retained sequence is six. The existing test checks this boundary.

## Exercise and explanation
Should a user interface label this view “all events”? No. It should describe recent retained events and expose the lost count where completeness matters.

## Troubleshoot
Do not increase the capacity merely to conceal sustained loss. Decide whether the consumer should read faster, whether old events can be discarded, or whether the application requires durable storage.

The source refuses an insertion if the dropped counter itself cannot be represented. This prevents loss accounting from silently wrapping to a misleading small number.

A larger array changes the capacity, not the fundamental retention policy. Document that policy before using a similar structure in a Framework diagnostic panel.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](19-separate-storage-order-from-reading-order.md) · [Next lesson](21-distinguish-sequence-from-time.md)

