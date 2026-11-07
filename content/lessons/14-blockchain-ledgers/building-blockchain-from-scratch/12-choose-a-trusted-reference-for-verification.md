<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/12-choose-a-trusted-reference-for-verification.md

PURPOSE:
Explain the lesson: Choose a trusted reference for verification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Choose a trusted reference for verification

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

A reference is useful only when its origin is known. Comparing a file with a digest stored beside it can detect accidental change, but both may be replaceable by the same writer.

## Work through the example

1. Draw the record file and retained head.
2. Mark who may modify each.
3. Consider a writer who can replace both.
4. Propose a separately controlled reference for a review exercise.

## Check your reasoning

Independent control of the expected digest strengthens the comparison. It still needs an identity and update policy; a digest value is not automatically trusted.

## If something differs

Do not describe a locally stored head as network consensus. Document exactly which source supplied the reference and which threat the comparison addresses.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-separate-integrity-from-approval.md) · [Next lesson](13-plan-a-small-chain-verification-project.md)

