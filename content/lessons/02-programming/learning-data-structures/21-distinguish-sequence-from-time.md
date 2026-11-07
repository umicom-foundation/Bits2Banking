<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/21-distinguish-sequence-from-time.md

PURPOSE:
Explain the lesson: Distinguish event sequence from event time.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish event sequence from event time

## Prepare
Look at the sequence and logicalTick fields in ring.h. Sequence counts accepted records. logicalTick describes the caller's observed logical time.

They answer different questions: which record was accepted first, and what time value accompanied it.

## Follow equal timestamps
The implementation permits two records with the same logical tick. Their sequence numbers remain different. It rejects a tick lower than the last accepted tick.

This is useful when several observations happen within one clock resolution.

## Lab
Trace pushes at ticks five, five and four. Use nonzero source and code values.

Expected: the first two succeed and receive successive sequences. The third is refused with TIME_REVERSED; it does not become a retained event.

## Exercise and explanation
Can sequence numbers be used as elapsed seconds? No. They count events, not time. Likewise, equal timestamps do not establish that two events are the same event.

## Troubleshoot
If time moves backwards, inspect the clock source and conversion before changing the ring. Wall-clock adjustments and monotonic elapsed time have different meanings.

The laboratory uses caller-supplied integer ticks. It does not read an operating-system clock or define a tick as a millisecond. State the unit when connecting a real clock, and preserve the monotonic requirement at that boundary.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](20-account-for-overwritten-observations.md) · [Next lesson](22-treat-sequence-exhaustion-explicitly.md)

