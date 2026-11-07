<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/72-check-the-dataset-split-boundary.md

PURPOSE:
Explain the lesson: Check the dataset-split boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the dataset-split boundary

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

The service accepts between 2 and 4096 sequences and requires output capacity for every ID. These limits bound work and ensure a usable split.

## Work through the example

1. Trace sequence counts 1, 2 and 4097.
2. For count 6, compare evaluation counts 0, 2 and 6.
3. Try output capacity 5.
4. Label each refusal before allocation.

## Check your reasoning

Only valid counts and sufficient capacity reach allocation. For six sequences, evaluation count 2 is admissible; capacity 5 is too small.

## If something differs

Do not increase a constant in a caller to bypass a service limit. Understand memory, runtime and API constraints before changing the shared implementation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](71-record-the-seed-and-data-identity.md) · [Next lesson](73-publish-a-complete-split.md)

