<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/15-follow-a-three-level-page-walk.md

PURPOSE:
Explain the lesson: Follow a three-level page walk.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a three-level page walk

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

A walk follows table entries until it reaches a leaf that describes a physical frame. The lab represents intermediate table addresses using the symbolic page numbers 2 and 3. These are identities within the model, not pointers to real RAM.

## Work through the example

1. Read `BtbSv39MapOne` and locate the root entry containing `MIDDLE_PPN`.
2. Locate the middle entry containing `LEAF_PPN`.
3. Find the leaf entry containing the requested physical page number.
4. Read `BtbSv39Translate` in the same order.
5. Cross out the root valid bit on paper and identify the first refusal.

## Check your reasoning

With the root entry invalid, the walk returns unmapped before inspecting a later table. An apparently useful leaf cannot repair a broken route from the root.

## If something differs

Do not dereference the model's page numbers as C pointers. They are intentionally checked constants selecting owned arrays.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-extract-three-page-table-indices.md) · [Next lesson](16-check-canonical-virtual-addresses.md)

