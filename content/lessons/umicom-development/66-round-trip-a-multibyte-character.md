<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/66-round-trip-a-multibyte-character.md

PURPOSE:
Explain the lesson: Round-trip a multibyte character.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Round-trip a multibyte character

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

UTF-8 can represent one displayed character with several bytes. A byte tokenizer keeps each byte separately. Token count therefore follows encoded bytes rather than the number of displayed characters.

## Work through the example

1. Use the UTF-8 bytes `C3 A9` for é.
2. Convert them to decimal 195 and 169.
3. Add the offset, then decode the IDs back.
4. Compare byte count and displayed-character count.

## Check your reasoning

The IDs are 199 and 173, and decoding restores two bytes. A UTF-8-aware renderer can display them as one character.

## If something differs

Do not split a displayed text selection by byte count without an encoding policy. This tokenizer preserves bytes; it does not provide character-boundary editing.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](65-decode-with-a-count-not-a-terminator.md) · [Next lesson](67-design-tokenizer-contract-cases.md)

