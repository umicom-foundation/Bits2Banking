<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/23-check-addition-before-performing-it.md

PURPOSE:
Explain the lesson: Check addition before performing it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check addition before performing it

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

Unsigned addition wraps modulo its range. BtbCheckedAdd tests left > UINT64_MAX - right before adding. The subtraction is safe because right already fits the unsigned type.

## Work through the example

Use a paper maximum of fifteen. Trace 12+3 and 12+4 through the same inequality. Explain which result can be represented.

## Check your reasoning

Twelve plus three fits exactly. Twelve plus four is refused before assignment. The output value remains unchanged on refusal.

## If something differs

If a test checks overflow after addition, the wrapped value may already have lost the information needed for the intended decision.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](22-choose-a-unit-before-doing-arithmetic.md) · [Next lesson](24-guard-multiplication-with-division.md)

