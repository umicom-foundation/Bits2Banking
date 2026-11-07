<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/27-validate-both-sides-of-a-transfer.md

PURPOSE:
Explain the lesson: Validate both sides of a transfer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate both sides of a transfer

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

A transfer calculates sender balance, recipient balance and both next revisions before changing either account. Four successful checks are required, not just sufficient sender funds.

## Work through the example

Use a sender with ten pence and a recipient already at UINT64_MAX. Attempt to transfer one. Trace each check in order.

## Check your reasoning

The recipient addition fails. The sender is not debited, and neither revision advances. The test checks this absence of partial posting.

## If something differs

If one side changes, review every early return and assignment. This process-local guarantee does not provide crash recovery or concurrent transaction isolation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](26-calculate-a-candidate-before-publishing.md) · [Next lesson](28-refuse-aliasing-accounts-explicitly.md)

