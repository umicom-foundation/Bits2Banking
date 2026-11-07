<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/57-serialize-fields-before-hashing.md

PURPOSE:
Explain the lesson: Serialize fields before hashing.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Serialize fields before hashing

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

HashLink consumes a fixed eight-byte record: two unsigned little-endian 32-bit fields. It hashes explicit bytes rather than the raw storage of a C structure, whose padding and layout may vary.

## Work through the example

Decode {1,0,0,0,25,0,0,0}. Then write the eight bytes for sequence two and amount thirty. Compare with the second record in Chain.

## Check your reasoning

The first record means sequence one and amount twenty-five. Explicit byte order makes the teaching format clear across hosts.

## If something differs

If another language produces different hashes, compare serialized bytes first. Matching field values alone does not prove matching representation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](56-retain-a-usable-context-after-rejected-input.md) · [Next lesson](58-separate-hash-domains.md)

