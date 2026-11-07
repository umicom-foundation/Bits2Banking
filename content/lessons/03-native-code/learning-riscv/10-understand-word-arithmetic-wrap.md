<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/10-understand-word-arithmetic-wrap.md

PURPOSE:
Explain the lesson: Understand fixed-width arithmetic wrap.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand fixed-width arithmetic wrap

A fixed-width unsigned value has a finite range. Arithmetic in that range can wrap back to zero.

## Prepare

Read the data array in check.c: 1, 2, 3 and UINT64_MAX. The expected sum is 5.

UINT64_MAX is the largest unsigned 64-bit integer. Adding one to it produces zero under modulo-2^64 arithmetic.

## Work through the expectation

The first three elements sum to 6. Adding the largest value is equivalent to subtracting one modulo 2^64, giving 5.

BtbSum64 documents this wrap behavior. It does not return an overflow error.

## Use a smaller drawing

Draw a four-bit counter with values zero through fifteen. Starting at fourteen, add three steps: fifteen, zero, one.

The small drawing illustrates the same finite-range idea. The implementation still uses 64-bit values.

## Exercise

Predict BtbSum64 for UINT64_MAX followed by 1, then for UINT64_MAX followed by 2. Keep the count consistent with the number of readable elements.

Add these cases to a local copy of the harness and record the expected zero and one before running it.

## Choose the right contract

Wrap is useful for some counters and bit algorithms. It is usually not an acceptable hidden policy for an amount owed or an allocation size.

A checked arithmetic API should detect overflow before publishing a result. This lesson's interface instead makes wrap explicit.

Do not transfer unsigned wrap expectations to signed C overflow. The language contracts differ. When connecting C and Assembly, document the chosen arithmetic policy in the shared interface rather than relying on a reader to guess it.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/check.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-understand-signed-and-unsigned-order.md) · [Next lesson](11-explain-bit-rotation.md)

