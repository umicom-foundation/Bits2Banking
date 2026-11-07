<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/10-give-a-hash-input-a-domain.md

PURPOSE:
Explain the lesson: Give a hash input a domain.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Give a hash input a domain

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

A domain label identifies the purpose of a byte sequence. The lab prefixes a fixed label before the previous digest and record. This reduces ambiguity between unrelated uses of the same hash service.

## Work through the example

1. Find the literal domain label.
2. Check whether its terminating C zero byte is included.
3. Draw label, previous digest and record as separate input regions.

## Check your reasoning

The code hashes the label's visible bytes without its C terminator. Every implementation replaying this format must make the same choice.

## If something differs

Do not casually rename the label in an established stored format. That changes the digest of every record and requires an explicit format migration.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-detect-an-edited-record.md) · [Next lesson](11-separate-integrity-from-approval.md)

