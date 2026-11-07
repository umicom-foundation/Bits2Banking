<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/68-separate-training-and-evaluation-examples.md

PURPOSE:
Explain the lesson: Separate training and evaluation examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate training and evaluation examples

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

If a model is measured on the same examples used to adjust it, memorisation can look like useful generalisation. This service rearranges sequence identities so callers can assign separate groups.

## Work through the example

1. Draw six ID cards.
2. Reserve two positions for evaluation according to the public header's partition rule.
3. Place every ID in exactly one group.
4. Explain why both groups must remain nonempty.

## Check your reasoning

A valid split contains six distinct IDs and two disjoint groups. The function rejects evaluation count zero or a count at least as large as the sequence count.

## If something differs

Disjoint IDs alone do not eliminate duplicated text or related files across groups. Review how sequences were created before trusting an evaluation result.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](67-design-tokenizer-contract-cases.md) · [Next lesson](69-shuffle-identities-without-copying-corpus.md)

