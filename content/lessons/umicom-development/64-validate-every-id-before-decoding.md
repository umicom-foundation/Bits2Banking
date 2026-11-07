<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/64-validate-every-id-before-decoding.md

PURPOSE:
Explain the lesson: Validate every ID before decoding.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate every ID before decoding

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

The decoder uses two loops. The first validates every ID; the second writes bytes. This makes a late invalid token fail without leaving a partially changed output buffer.

## Work through the example

1. Fill a paper output array with `99, 99, 99`.
2. Supply token IDs `69, 70, 999`.
3. Trace the validation loop.
4. State whether the writing loop begins.

## Check your reasoning

The invalid third ID prevents all output writes. The three sentinel bytes remain 99 and the output count is not published.

## If something differs

When adding a new conversion, retain whole-input validation or a temporary candidate buffer. A single mixed validate-and-write loop would change the failure contract.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](63-separate-special-tokens-from-text.md) · [Next lesson](65-decode-with-a-count-not-a-terminator.md)

