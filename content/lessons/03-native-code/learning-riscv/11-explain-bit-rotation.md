<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/11-explain-bit-rotation.md

PURPOSE:
Explain the lesson: Explain bit rotation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain bit rotation

A shift moves bits toward one end of a register. A rotation also moves bits, but the bits leaving one end reappear at the other.

## Prepare

Open BtbRotateLeft64 in bits.S and the Rotate reference in check.c. The input value is in a0 and the requested distance in a1.

The function uses only base operations: shifts, subtraction, OR and a branch.

## Follow a one-bit rotation

Start with only bit 63 set. Shifting left by one loses that top bit from the 64-bit result. Shifting the original value right by 63 produces a one at bit zero.

OR combines the two parts. The rotated result is 1.

## Normalize the distance

The function keeps only the low six bits of distance, giving a value from zero through 63. Rotating by 64 has the same result as rotating by zero.

The zero case returns directly. The C reference also separates zero so it never shifts by the full type width.

## Exercise

Use an eight-box drawing to understand the movement, then return to the 64-bit contract. Mark where bits zero and 63 move when rotating left once.

Predict results for distances 0, 1, 63, 64 and 65. The harness also checks distances beyond one complete rotation.

## Review the boundary

The reference uses unsigned values. A right shift must bring in zeroes for this construction; a signed arithmetic shift would have a different meaning.

Bit operations appear in binary formats, checksums and machine interfaces. A correct rotation alone does not establish the correctness or security of a larger algorithm that uses it.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/bits.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-understand-word-arithmetic-wrap.md) · [Next lesson](12-use-parity-as-a-small-bit-algorithm.md)

