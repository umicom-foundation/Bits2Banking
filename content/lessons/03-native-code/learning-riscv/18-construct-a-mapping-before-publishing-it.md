<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/18-construct-a-mapping-before-publishing-it.md

PURPOSE:
Explain the lesson: Construct a mapping before publishing it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Construct a mapping before publishing it

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

A failed map operation must leave the existing mapping useful. The lab validates inputs, builds a local `staged` value and copies it to the caller only at the end. This is a simple example of publishing a complete result after all checks succeed.

## Work through the example

1. Begin with the valid `0x40201000` to `0x9000` mapping.
2. Request a new mapping with physical address `0x9001`.
3. Find the alignment check before `staged` is populated.
4. Confirm that the existing space is unchanged on refusal.
5. Translate the original address again in your paper trace.

## Check your reasoning

An address ending in `001` is not a 4096-byte frame boundary. The previous mapping remains available. This lab installs exactly one mapping per successful call, replacing its model tables.

## If something differs

Do not assume `MapOne` adds a second independent mapping. Its public contract explicitly clears and replaces the supplied model on success.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](17-model-read-write-and-execute-permissions.md) · [Next lesson](19-preserve-an-output-after-translation-fails.md)

