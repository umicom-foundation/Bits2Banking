<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/56-retain-a-usable-context-after-rejected-input.md

PURPOSE:
Explain the lesson: Retain a usable context after rejected input.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Retain a usable context after rejected input

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

Updating with a null pointer and nonzero length is invalid. The test then appends abc and expects the normal reference digest. This checks that rejection did not silently advance or corrupt the context.

## Work through the example

Follow Rejected in main.c. List the invalid input, recovery update and final expected value. Distinguish testing an error code from testing later usability.

## Check your reasoning

The invalid update returns INVALID_ARGUMENT; the subsequent valid update and finalization still produce the abc digest.

## If something differs

If the later digest differs, inspect whether the invalid update changed counters before checking its pointer. The recovery assertion is what exposes that defect.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](55-finish-a-context-once.md) · [Next lesson](57-serialize-fields-before-hashing.md)

