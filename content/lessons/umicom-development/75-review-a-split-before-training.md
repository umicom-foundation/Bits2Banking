<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/75-review-a-split-before-training.md

PURPOSE:
Explain the lesson: Review a split before training.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Review a split before training

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

A split is an experimental artifact worth checking before an expensive run. Checking it early prevents hours of training against an unsuitable evaluation set.

## Work through the example

1. Specify checks for ID range, duplicates, total count and group intersection.
2. Add dataset fingerprint and seed to the record.
3. Inspect examples from each group.
4. Keep the split fixed during a controlled comparison.

## Check your reasoning

The review combines structural checks with content review. An empty intersection of IDs is necessary but does not establish absence of duplicated content.

## If something differs

If source sequences change, create a new recorded split identity rather than silently reusing an old experiment label. Evaluation claims must identify the data actually used.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](74-understand-a-samplers-limits.md) · [Next lesson](76-measure-a-gradient-vector.md)

