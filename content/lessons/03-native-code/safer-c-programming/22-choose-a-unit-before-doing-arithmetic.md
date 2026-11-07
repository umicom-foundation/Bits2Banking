<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/22-choose-a-unit-before-doing-arithmetic.md

PURPOSE:
Explain the lesson: Choose a unit before doing arithmetic.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Choose a unit before doing arithmetic

## Prepare

Open account.h, account.c and test_account.c in labs/native/checked-money. Its README supplies C23 build commands. The amounts are fictional integer pence in an in-memory exercise; no bank account or payment service is contacted.

## Understand the idea

balancePence stores an integer count of pence. Naming the unit avoids interpreting 2500 as either pounds or pence. A numeric type alone does not express currency or unit.

## Work through the example

Trace the test transfer of 2500 from balances 15000 and 4000. Write both integer balances and their pound equivalents before and after.

## Check your reasoning

The new balances are 12500 and 6500 pence. Their sum remains 19000 pence. This example has one currency and no conversion or fees.

## If something differs

If totals disagree by a factor of one hundred, inspect units at the input boundary before changing arithmetic.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/checked-money/account.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](21-review-the-arena-contract.md) · [Next lesson](23-check-addition-before-performing-it.md)

