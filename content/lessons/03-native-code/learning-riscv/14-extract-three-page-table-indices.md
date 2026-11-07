<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/14-extract-three-page-table-indices.md

PURPOSE:
Explain the lesson: Extract three page-table indices.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Extract three page-table indices

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

A page table is an array describing mappings. The teaching Sv39 walker chooses an entry from each of three tables. Each index contains nine bits, giving 512 possible entries. The helper `Index` shifts a selected group to the right and masks away other bits.

## Work through the example

1. Find calls to `Index` with shifts 30, 21 and 12.
2. Use virtual address `0x40201120`.
3. Calculate the root index as `(address >> 30) & 511`.
4. Repeat for the middle and leaf tables.
5. Draw three boxes labelled with the resulting indices.

## Check your reasoning

The indices are root 1, middle 1 and leaf 1. The remaining `0x120` selects the byte inside the mapped page. Index calculations select entries; they do not themselves grant access.

## If something differs

If an index exceeds 511, the mask is missing or applied before shifting. Keep the value unsigned when experimenting with shifts.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-split-an-address-into-page-and-offset.md) · [Next lesson](15-follow-a-three-level-page-walk.md)

