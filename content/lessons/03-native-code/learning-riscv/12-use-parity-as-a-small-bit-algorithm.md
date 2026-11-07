<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/12-use-parity-as-a-small-bit-algorithm.md

PURPOSE:
Explain the lesson: Use parity as a small bit algorithm.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use parity as a small bit algorithm

Parity reports whether a bit pattern contains an even or odd number of set bits. It returns zero for even and one for odd.

## Prepare

Read BtbParity64 in bits.S. Then read the C Parity function in check.c. Both compute the same property using different steps.

A set bit has value one. A clear bit has value zero.

## Trace the Assembly loop

The function copies the input into t0 and starts the result at zero.

1. If t0 is zero, return.
2. Extract the low bit using AND with 1.
3. Combine that bit with the result using XOR.
4. Shift t0 right by one.
5. Repeat.

XOR toggles the result when the extracted bit is one. A zero leaves it unchanged.

## Try three inputs

Zero has no set bits, so its parity is zero. The value one has one set bit, so parity is one. The value three is binary 11 and has parity zero.

For the highest bit alone, the loop shifts many times before reaching it. The result is still one.

## Exercise

Trace binary 10110. Record extracted bits from right to left and the running result. There are three set bits, so the final parity is one.

Compare this trace with the C reference, which counts all 64 bit positions and takes the remainder after division by two.

## Understand the limit

Parity can detect a single changed bit, but two changed bits may leave parity unchanged. It cannot identify where damage occurred or establish authenticity.

Use the example to learn loops and bit operations. For production integrity or authentication, use the appropriate reviewed Framework service and its documented threat model.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/bits.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-explain-bit-rotation.md)


[Next: Split an address into a page and an offset](13-split-an-address-into-page-and-offset.md)
