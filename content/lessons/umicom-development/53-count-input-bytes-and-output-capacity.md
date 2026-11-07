<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/53-count-input-bytes-and-output-capacity.md

PURPOSE:
Explain the lesson: Count input bytes and output capacity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count input bytes and output capacity

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

Known hashes three bytes of abc, without the C string terminator. Its hex array uses UMI_SHA256_HEX_CAPACITY, which includes space for the output terminator. Input length and output capacity serve different purposes.

## Work through the example

Compare hashing "abc" with length three and length four. Draw the bytes a,b,c and the trailing zero. Identify which call matches the supplied reference digest.

## Check your reasoning

Length three matches the abc reference. Adding the terminator changes the message and therefore requires a different expected digest.

## If something differs

If a reference comparison fails, inspect exact bytes and length before blaming the algorithm. Newlines from text files also change the input.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](52-use-an-sdk-service-without-copying-it.md) · [Next lesson](54-feed-a-hash-in-ordered-chunks.md)

