<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/61-preserve-zero-bytes-in-input.md

PURPOSE:
Explain the lesson: Preserve zero bytes in input.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve zero bytes in input

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

This tokenizer accepts a pointer and an explicit length. It can therefore represent an embedded zero byte. A C string length routine would stop at that byte and lose the remaining input.

## Work through the example

1. Draw the bytes `65, 0, 66`.
2. Encode exactly three elements.
3. Compare the result with treating the same storage as a zero-terminated string.
4. Explain which interpretation the API promises.

## Check your reasoning

The explicit-length encoding produces `69, 4, 70`. A string interpretation would see only the first visible character before the terminator.

## If something differs

Do not replace the API length with `strlen` for arbitrary input. Decide whether your caller handles text strings or binary bytes, and retain the actual byte length.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](60-introduce-byte-token-identities.md) · [Next lesson](62-measure-token-buffer-capacity.md)

