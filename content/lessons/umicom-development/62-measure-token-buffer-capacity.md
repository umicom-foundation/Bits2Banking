<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/62-measure-token-buffer-capacity.md

PURPOSE:
Explain the lesson: Measure token buffer capacity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Measure token buffer capacity

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

The output capacity counts token elements, not bytes of allocation. Here each token occupies a `uint32_t`; confusing those units can allow writing beyond the allocated array.

## Work through the example

1. Declare a paper buffer `uint32_t tokens[3]`.
2. State its element capacity.
3. Trace length 3 with capacity 3, then length 4 with capacity 3.
4. Locate the capacity guard before the loop.

## Check your reasoning

The capacity is 3. Length 4 is refused before any token writes. Using `sizeof tokens` as an element count would incorrectly describe the buffer.

## If something differs

Use an element-count expression such as `sizeof tokens / sizeof tokens[0]` for an actual array. A pointer does not retain its original array length.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](61-preserve-zero-bytes-in-input.md) · [Next lesson](63-separate-special-tokens-from-text.md)

