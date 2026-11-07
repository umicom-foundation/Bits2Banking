<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/74-understand-a-samplers-limits.md

PURPOSE:
Explain the lesson: Understand a sampler's limits.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand a sampler's limits

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

This educational shuffle maps a floating-point sample to an integer index. Its source documents that it is not a production unbiased integer sampler or a statistically stratified splitter.

## Work through the example

1. Read the two sampling comments.
2. Explain why rounding or finite precision can affect index frequencies.
3. List a property that shuffling does preserve regardless: the set of IDs.

## Check your reasoning

Swapping preserves membership and uniqueness. That does not prove every permutation has exactly equal probability or that rare example categories are balanced.

## If something differs

Do not describe the split as representative merely because it is shuffled. A research report should state these limitations and measure the resulting groups.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](73-publish-a-complete-split.md) · [Next lesson](75-review-a-split-before-training.md)

