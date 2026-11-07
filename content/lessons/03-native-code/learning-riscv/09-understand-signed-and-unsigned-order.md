<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/09-understand-signed-and-unsigned-order.md

PURPOSE:
Explain the lesson: Understand signed and unsigned order.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand signed and unsigned order

Ordering asks which value comes first. Signed integers include negative values; unsigned integers start at zero. A processor needs an instruction that matches the intended interpretation.

## Prepare

Open minimum.S and sequences.h. Two functions have similar bodies but different declared types.

BtbMinSigned64 uses bge. BtbMinUnsigned64 uses bgeu. The u marks unsigned comparison.

## Read the branch

Both functions begin with the left value in a0 and right value in a1. If the right value is greater than or equal to the left, a0 already contains the minimum.

Otherwise the function copies a1 into a0 before returning.

## Use a revealing example

Compare -1 and 1 with signed ordering: -1 is smaller.

Now compare UINT64_MAX and 1 with unsigned ordering: 1 is smaller. The all-one pattern must not be treated as a negative number in this interface.

check.c includes these cases so an accidental branch substitution can be detected.

## Exercise

Trace equal inputs, then reverse the argument order of unequal inputs. Explain why the returned minimum is unchanged when the arguments swap.

Write down the expected result before reading the test condition.

## Apply the idea

An account balance might require signed values because it can be negative. A byte count or array length usually needs a nonnegative range. Choosing an unsigned type does not remove the need to check bounds.

When reading Umicom source, inspect declarations and conversions alongside instructions. A comparison that looks correct locally may still receive a value converted under a different rule.

The example computes a minimum only. It does not validate a financial model or authorize a transaction.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/minimum.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-distinguish-register-width-and-data-width.md) · [Next lesson](10-understand-word-arithmetic-wrap.md)

