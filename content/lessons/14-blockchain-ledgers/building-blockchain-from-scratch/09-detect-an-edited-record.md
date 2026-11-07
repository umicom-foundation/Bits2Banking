<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/09-detect-an-edited-record.md

PURPOSE:
Explain the lesson: Detect an edited record.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Detect an edited record

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

An integrity check asks whether the bytes match the retained reference. It does not judge whether a transaction was economically correct or authorised.

## Work through the example

1. Locate the lab's two alternatives for the first amount.
2. Compare amount 25 with amount 26.
3. Trace which later link receives a changed previous digest.
4. Explain the final comparison.

## Check your reasoning

The changed record should produce a different chain head. The test detects a modification relative to the original retained head.

## If something differs

A wrong amount recorded consistently from the beginning can still pass a hash check. Validation, authorisation and reconciliation are additional responsibilities.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-replay-a-chain-to-check-determinism.md) · [Next lesson](10-give-a-hash-input-a-domain.md)

