<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/54-feed-a-hash-in-ordered-chunks.md

PURPOSE:
Explain the lesson: Feed a hash in ordered chunks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Feed a hash in ordered chunks

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

Chunks initializes a context, updates with a then bc, finalizes to raw digest bytes and converts those bytes to hexadecimal. Streaming allows input to arrive in pieces without changing its logical order.

## Work through the example

Write the concatenated input for updates a then bc, and for bc then a. Predict which can match the abc reference.

## Check your reasoning

The first sequence represents abc. The reversed sequence represents bca. Chunk boundaries do not matter when byte order and content remain identical.

## If something differs

If streaming differs from one-shot hashing, inspect context initialization, repeated bytes, omitted bytes and update order.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](53-count-input-bytes-and-output-capacity.md) · [Next lesson](55-finish-a-context-once.md)

