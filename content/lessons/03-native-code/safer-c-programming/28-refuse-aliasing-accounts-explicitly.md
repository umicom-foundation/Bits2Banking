<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/28-refuse-aliasing-accounts-explicitly.md

PURPOSE:
Explain the lesson: Refuse aliasing accounts explicitly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refuse aliasing accounts explicitly

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

from == to detects two pointers naming the same account object. Treating that as an ordinary two-account transfer would make publication order confusing and increment the same revision twice or inconsistently.

## Work through the example

Draw two pointers to one box, then pointers to two separate boxes with equal balances. Identify which situation the comparison rejects.

## Check your reasoning

Only the shared-object case is rejected. Equal values in separate accounts do not make their addresses equal.

## If something differs

If a self-transfer slips through a higher-level identifier lookup, verify that both identifiers resolve to their actual owner objects before calling the operation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](27-validate-both-sides-of-a-transfer.md) · [Next lesson](29-test-refusal-with-preserved-state.md)

