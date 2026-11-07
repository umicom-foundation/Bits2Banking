<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/24-guard-multiplication-with-division.md

PURPOSE:
Explain the lesson: Guard multiplication with division.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Guard multiplication with division

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

Multiplication uses left > UINT64_MAX / right when right is nonzero. The nonzero condition prevents division by zero. Multiplication by zero is representable and produces zero.

## Work through the example

With a paper maximum of fifteen, trace 5×3, 6×3 and 6×0. Evaluate the guard before the multiplication.

## Check your reasoning

Fifteen and zero succeed; eighteen is refused. Short-circuit evaluation avoids the division when right is zero.

## If something differs

If a zero test crashes, inspect the order of && operands. The nonzero check must protect the division.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](23-check-addition-before-performing-it.md) · [Next lesson](25-reject-underflow-as-a-domain-result.md)

