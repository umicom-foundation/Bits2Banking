<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/13-plan-a-small-chain-verification-project.md

PURPOSE:
Explain the lesson: Plan a small chain-verification project.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan a small chain-verification project

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

A complete learning project states inputs, checks, outputs and limits. The existing chain lab supplies a tested-shape API consumer to study before adding storage or networking.

## Work through the example

1. Specify two fixed records and one expected final digest.
2. Include replay, changed amount and changed order checks.
3. Define failure output without printing private records.
4. Use the README for optional SDK build steps.

## Check your reasoning

The project can establish whether these synthetic inputs reproduce a retained head. It cannot establish decentralisation, mining fairness or transaction settlement.

## If something differs

Keep new persistence work separate until short reads, malformed records and interrupted writes have explicit handling. Reuse Framework services instead of copying their implementations.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-choose-a-trusted-reference-for-verification.md)

