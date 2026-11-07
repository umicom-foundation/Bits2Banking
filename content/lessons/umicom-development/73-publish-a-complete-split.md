<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/73-publish-a-complete-split.md

PURPOSE:
Explain the lesson: Publish a complete split.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a complete split

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

The function constructs its order in temporary memory and copies it to the caller only at the end. This keeps failed preparation from exposing half a permutation.

## Work through the example

1. Locate allocation, shuffle and final `memcpy`.
2. Trace an allocation failure.
3. Trace a generator failure inside the loop.
4. Mark every cleanup path.

## Check your reasoning

Both failures return before the output copy. Allocated temporary memory is freed on generator failure and after successful publication.

## If something differs

When extending the function, check every new early return for owned memory and output mutation. Temporary ownership is useful only if its cleanup remains complete.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](72-check-the-dataset-split-boundary.md) · [Next lesson](74-understand-a-samplers-limits.md)

