<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/08-replay-a-chain-to-check-determinism.md

PURPOSE:
Explain the lesson: Replay a chain to check determinism.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Replay a chain to check determinism

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

Deterministic means the same defined inputs produce the same result. Replaying records is a useful check of serialization and ordering.

## Work through the example

1. Copy the two synthetic records from the lab into a table.
2. Start two paper replays from the same zero digest.
3. List every hash input in order.
4. Compare the expected final identities.

## Check your reasoning

Both replays should produce equal final digests because their inputs match. The existing chain contract checks equality rather than requiring a hand-computed digest.

## If something differs

If replay differs, compare field bytes, record order and initial digest before blaming the hash function. A different byte sequence is a different input.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-connect-a-record-to-the-previous-digest.md) · [Next lesson](09-detect-an-edited-record.md)

