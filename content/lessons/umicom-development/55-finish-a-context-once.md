<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/55-finish-a-context-once.md

PURPOSE:
Explain the lesson: Finish a context once.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Finish a context once

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

The Rejected scenario checks that a finalized context refuses another Final operation and leaves the supplied output untouched. Finalization is a lifecycle boundary, not an ordinary read of a reusable accumulator.

## Work through the example

Trace Init → Update → Final → Final. Mark the call that should produce a digest and the call that should refuse. Explain why another independent message needs a new initialization.

## Check your reasoning

The first Final succeeds. The repeated Final is expected to refuse without overwriting its sentinel buffer. A fresh message starts with Init.

## If something differs

If a wrapper reuses a finalized context, fix its ownership and lifecycle rather than ignoring the second status.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](54-feed-a-hash-in-ordered-chunks.md) · [Next lesson](56-retain-a-usable-context-after-rejected-input.md)

