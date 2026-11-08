<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/29-test-refusal-with-preserved-state.md

PURPOSE:
Explain the lesson: Test refusal with preserved state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test refusal with preserved state

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

A refusal test must inspect state as well as the status. test_account.c checks balances, revisions and output sentinels after overflow or insufficient funds. This catches a function that reports failure after making a partial change.

## Work through the example

Choose the full-recipient test. List all fields that must remain unchanged, then compare that list with the assertions. Add a paper case for recipient revision exhaustion.

## Check your reasoning

The sender and recipient balances and revisions must all remain unchanged. A correct error label alone is insufficient evidence.

## If something differs

If expanding tests, compare defined fields rather than assuming structure padding has a stable byte representation. Record executed results separately from authored expectations.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](28-refuse-aliasing-accounts-explicitly.md)


<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Next lesson](30-count-capacity-and-index.md)
