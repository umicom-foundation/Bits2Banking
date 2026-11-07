<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/26-calculate-a-candidate-before-publishing.md

PURPOSE:
Explain the lesson: Calculate a candidate before publishing.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Calculate a candidate before publishing

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

Credit and Debit use local balance and revision variables. The live account is assigned only after both calculations succeed. This protects against a valid amount combined with an exhausted revision counter.

## Work through the example

Set balance to 5000 and revision to UINT64_MAX. Trace a debit of one through balance calculation and revision increment.

## Check your reasoning

The candidate balance can be 4999, but revision overflow prevents publication. The live account remains 5000 at its original revision.

## If something differs

If the balance changes on failure, find assignments to account before the final status check. A local candidate is useful only when publication is deferred.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](25-reject-underflow-as-a-domain-result.md) · [Next lesson](27-validate-both-sides-of-a-transfer.md)

