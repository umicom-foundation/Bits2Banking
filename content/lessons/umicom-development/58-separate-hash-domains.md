<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/58-separate-hash-domains.md

PURPOSE:
Explain the lesson: Separate hash domains.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate hash domains

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

HashLink begins with the fixed UMICOM-LEARNING-LINK tag, then previous digest and record. The tag identifies the intended format context. Fixed-width fields make the boundaries unambiguous in this exercise.

## Work through the example

Draw the byte sequence as tag | previous digest | eight-byte record. Explain what must change if a later format introduces variable-length text.

## Check your reasoning

The current boundaries are known from fixed sizes. Variable-length fields need an explicit reviewed encoding, such as lengths, rather than ambiguous concatenation.

## If something differs

If two formats reuse a tag accidentally, rename or version their defined domain through a compatibility plan. A tag is not a secret key.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](57-serialize-fields-before-hashing.md) · [Next lesson](59-interpret-a-retained-chain-head.md)

