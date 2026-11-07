<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/13-split-an-address-into-page-and-offset.md

PURPOSE:
Explain the lesson: Split an address into a page and an offset.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Split an address into a page and an offset

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

A page is a fixed-sized region of memory. This example uses 4096-byte pages. An address identifies both a page and a byte within that page. Keeping the offset separate lets a program use one address while the operating system chooses a different physical frame.

## Work through the example

1. Write `0x40201120`.
2. Keep the low twelve bits: `address & 0xfff` gives `0x120`.
3. Clear those bits: the virtual page starts at `0x40201000`.
4. Follow `main.c`, where that page maps to the physical frame `0x9000`.
5. Add the offset to obtain `0x9120`.

```text
virtual page 0x40201000 + offset 0x120
                 mapping ↓
physical frame 0x9000  + offset 0x120
```

## Check your reasoning

Repeat for offset `0xfff`: the result is `0x9fff`, the last byte in the frame. The offset fits because its range is zero through 4095.

## If something differs

If you obtain `0x9000` for every byte, you discarded the offset. If you use decimal 1000 as the page size, revisit hexadecimal notation before continuing.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-use-parity-as-a-small-bit-algorithm.md) · [Next lesson](14-extract-three-page-table-indices.md)

