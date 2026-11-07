<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/11-separate-integrity-from-approval.md

PURPOSE:
Explain the lesson: Separate integrity from approval.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate integrity from approval

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

Integrity means correspondence with an expected representation. Approval means a person or policy allowed an action. A digest has no built-in knowledge of account owners or permissions.

## Work through the example

1. Write a record with an intentionally incorrect fictional amount.
2. Explain whether it could still be hashed.
3. List checks needed before a financial system could accept it.

## Check your reasoning

The hash service can summarize any supplied bytes. Account existence, limits, signatures and business rules are separate checks; hashing alone supplies none of them.

## If something differs

Keep the example synthetic. Do not connect these teaching records to real balances or assume a passing chain test qualifies a payment or trading system.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-give-a-hash-input-a-domain.md) · [Next lesson](12-choose-a-trusted-reference-for-verification.md)

