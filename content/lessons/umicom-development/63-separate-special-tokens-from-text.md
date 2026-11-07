<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/63-separate-special-tokens-from-text.md

PURPOSE:
Explain the lesson: Separate special tokens from text.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate special tokens from text

## Prepare

Open Framework's `src/ai/training/byte_tokenizer.c` and `include/umicom/ai/training/byte_tokenizer.h`. A byte holds a number from 0 to 255. A token ID is a number used by a model to represent an input unit. These exercises need a text editor and paper; no training run or downloaded model is required.

## Understand the idea

Reserved IDs can indicate padding or sequence boundaries elsewhere in a model. The byte decoder refuses them because silently turning them into text would hide a caller-policy decision.

## Work through the example

1. Identify PAD, BOS, EOS and UNK in the header.
2. Trace decoding IDs 4, 69 and 2.
3. Mark which ID cannot be converted by this function.

## Check your reasoning

ID 2 is reserved and causes refusal. IDs 4 and 69 alone would represent bytes 0 and 65, but the whole supplied sequence must pass validation first.

## If something differs

If generated output includes an end marker, the generation layer must apply an explicit policy before byte decoding. Do not subtract 4 from a reserved unsigned ID.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/byte_tokenizer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](62-measure-token-buffer-capacity.md) · [Next lesson](64-validate-every-id-before-decoding.md)

