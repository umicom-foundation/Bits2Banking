<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/71-record-the-seed-and-data-identity.md

PURPOSE:
Explain the lesson: Record the seed and data identity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record the seed and data identity

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

A seed initializes a pseudorandom generator. Repeating it can reproduce choices for the same algorithm and inputs, which helps compare experiments.

## Work through the example

1. Make an experiment record containing source revision, sequence ordering, counts and seed.
2. Change only the seed in a second record.
3. Explain which comparison this permits.

## Check your reasoning

The records distinguish a model change from a split change. A seed alone is insufficient if the dataset order or generator implementation also changes.

## If something differs

Never treat this educational generator as a security source. Its purpose here is repeatable experiment organization, not secret keys or adversarial sampling.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](70-follow-a-bounded-shuffle-step.md) · [Next lesson](72-check-the-dataset-split-boundary.md)

