<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/22-treat-sequence-exhaustion-explicitly.md

PURPOSE:
Explain the lesson: Treat sequence exhaustion explicitly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Treat sequence exhaustion explicitly

## Prepare
Read the nextSequence update in ring.c. uint64_t represents a finite range of nonnegative integers. A sequence must not silently wrap and reuse an earlier identity.

The ring issues UINT64_MAX once, then stores zero as an exhausted marker.

## Trace the last two requests
The existing test sets nextSequence to the maximum in a controlled test fixture. The next push succeeds with that exact sequence. The following push returns SEQUENCE_EXHAUSTED.

Production callers should not modify this field to restart numbering.

## Lab
Draw a three-row trace: maximum minus one, maximum, exhausted. Record the accepted sequence and nextSequence after each operation.

Expected: zero is never issued as a record sequence.

## Exercise and explanation
Why not simply restart at one? A client retaining an older snapshot could confuse a new event with an old event. Restart requires a separate epoch or session identity and a specified policy.

## Troubleshoot
This boundary is impractical to reach by looping through every integer. Constructing a controlled near-limit fixture is appropriate for a regression check, provided the rest of the object remains valid.

A successful boundary test establishes this model's behaviour. It does not establish persistence across process restarts. If a future service needs globally unique event identities, design the additional identity and storage contract explicitly.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](21-distinguish-sequence-from-time.md) · [Next lesson](23-preserve-address-stable-owners.md)

