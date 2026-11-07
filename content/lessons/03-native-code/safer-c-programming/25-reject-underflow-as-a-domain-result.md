<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/25-reject-underflow-as-a-domain-result.md

PURPOSE:
Explain the lesson: Reject underflow as a domain result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject underflow as a domain result

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

Subtracting a larger unsigned value would wrap. BtbCheckedSubtract checks left < right and reports INSUFFICIENT_FUNDS. This gives the caller a meaningful reason rather than a huge wrapped balance.

## Work through the example

Trace 5−6, 5−5 and 5−0. Keep a sentinel in the output and predict whether each call overwrites it.

## Check your reasoning

The first refuses and retains the sentinel; the other results are zero and five. The higher-level debit API separately rejects an amount of zero.

## If something differs

If tests disagree about zero, distinguish the arithmetic helper's contract from the account operation's contract.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](24-guard-multiplication-with-division.md) · [Next lesson](26-calculate-a-candidate-before-publishing.md)

