<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/07-connect-a-record-to-the-previous-digest.md

PURPOSE:
Explain the lesson: Connect a record to the previous digest.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect a record to the previous digest

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

A hash link includes the previous digest as input. Changing an earlier record changes the digest used by later links, allowing comparison against a separately retained final digest.

## Work through the example

1. Draw an initial all-zero digest.
2. Connect record 1 to it.
3. Feed that result into record 2.
4. Label the bytes belonging to each step.

## Check your reasoning

The second digest depends on both records through the first digest. It cannot be reproduced from record 2 alone without also supplying the previous digest.

## If something differs

This dependency does not establish who created the records. An attacker able to replace all records and the trusted final digest can create a consistent replacement chain.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-turn-record-fields-into-defined-bytes.md) · [Next lesson](08-replay-a-chain-to-check-determinism.md)

