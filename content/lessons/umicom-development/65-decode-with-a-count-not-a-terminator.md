<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/65-decode-with-a-count-not-a-terminator.md

PURPOSE:
Explain the lesson: Decode with a count, not a terminator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Decode with a count, not a terminator

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

The decoder writes the requested bytes and publishes their count. It does not append a C string terminator. That is appropriate for binary data but matters when a later API expects a string.

## Work through the example

1. Decode IDs `69, 70` into a two-byte buffer.
2. Draw the two occupied positions.
3. Explain why printing that buffer with `%s` is unsafe without additional preparation.

## Check your reasoning

The output contains bytes 65 and 66 and count 2. There is no third position promised for a zero terminator.

## If something differs

For text display, validate the intended encoding and provide properly terminated or length-aware input to the display API. Never read beyond the returned byte count.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](64-validate-every-id-before-decoding.md) · [Next lesson](66-round-trip-a-multibyte-character.md)

