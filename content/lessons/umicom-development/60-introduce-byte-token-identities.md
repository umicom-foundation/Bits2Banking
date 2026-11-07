<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/60-introduce-byte-token-identities.md

PURPOSE:
Explain the lesson: Introduce byte token identities.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Introduce byte token identities

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

The Framework byte tokenizer gives each byte one token ID by adding 4. IDs 0 through 3 are reserved for special purposes. Encoding changes representation; it does not learn a meaning for the text.

## Work through the example

1. Read `UMI_AI_BYTE_OFFSET` and `UMI_AI_BYTE_VOCABULARY`.
2. Calculate IDs for bytes 0, 65 and 255.
3. Draw byte → add 4 → token as three boxes.

## Check your reasoning

The IDs are 4, 69 and 259. There are 256 ordinary byte IDs and four reserved IDs, making 260 possible vocabulary entries.

## If something differs

If an ID becomes 260, inspect the input bound. The largest valid byte is 255, not 256. Keep the distinction between a count and the largest index.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](59-interpret-a-retained-chain-head.md) · [Next lesson](61-preserve-zero-bytes-in-input.md)

