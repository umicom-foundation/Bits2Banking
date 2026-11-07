<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/16-check-canonical-virtual-addresses.md

PURPOSE:
Explain the lesson: Check canonical virtual addresses.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check canonical virtual addresses

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

The model checks that the high bits of a 64-bit address agree with bit 38. This makes some bit patterns valid addresses and others invalid before any table lookup. The check is in `CanonicalSv39`; it is separate from whether a valid address actually has a mapping.

## Work through the example

1. Trace `0x0000000040201000`: bit 38 and the upper bits are zero.
2. Trace `0xffffffc000201000`: bit 38 and the upper bits are one.
3. Trace `0x0000008000000000`: the upper group is nonzero while bit 38 is zero.
4. Read the corresponding cases in `test_sv39.c`.

The architectural reference is the [RISC-V privileged specification](https://docs.riscv.org/reference/isa/_attachments/riscv-privileged.pdf).

## Check your reasoning

The first two patterns are canonical; the third is refused as an invalid address. Canonical does not mean mapped or permitted.

## If something differs

Do not repair an invalid address by silently masking its high bits. That could turn a bad input into access to a different address.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-follow-a-three-level-page-walk.md) · [Next lesson](17-model-read-write-and-execute-permissions.md)

