<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/15-define-cancellation-at-a-deadline.md

PURPOSE:
Explain the lesson: Define who wins at a deadline.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Define who wins at a deadline

## Prepare
Open BtbDeadlineCancel. The function asks Status and cancels only when the result is NOT_DUE.

The policy is explicit: once a finite deadline is due, cancellation no longer wins. A due timer remains pending until the caller fires it or handles the result.

## Lab
At tick ten, arm interval five. Test cancellation at fourteen in one fresh scenario and at fifteen in another.

Expected: cancellation succeeds at fourteen and leaves CANCELLED. At fifteen it returns DUE and leaves PENDING.

## Explain the choice
This teaching model gives the deadline priority at the boundary. Other systems may choose different rules. Correctness requires callers and tests to agree with the chosen contract.

A function called Cancel does not guarantee success merely because it was invoked.

## Record both outcomes
Write the requested operation, returned result and resulting state. A test that checks only the state can miss a misleading return code; a test that checks only the code can miss an unintended mutation.

## Troubleshoot
If a caller retries cancellation indefinitely after DUE, it may never resolve the timer. Handle the returned condition explicitly instead of assuming every refusal is temporary.

## Production boundary
This model has one owner and no concurrent threads. Real cancellation can race with execution and needs an ownership protocol. Do not infer thread safety from a deterministic single-threaded example.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-give-zero-an-explicit-meaning.md) · [Next lesson](16-use-an-oracle-for-a-small-model.md)

