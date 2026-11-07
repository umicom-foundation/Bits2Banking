<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/70-follow-a-bounded-shuffle-step.md

PURPOSE:
Explain the lesson: Follow a bounded shuffle step.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a bounded shuffle step

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

The shuffle chooses a position within the remaining prefix and swaps it with that prefix's last position. The prefix then shrinks, so already placed entries are not revisited.

## Work through the example

1. Start with `[0,1,2,3]`.
2. For remaining 4, choose position 1 and perform the swap.
3. For remaining 3, choose position 0.
4. Write both intermediate arrays.

## Check your reasoning

The arrays become `[0,3,2,1]`, then `[2,3,0,1]`. Every original ID remains present exactly once because swaps exchange values.

## If something differs

Do not claim a particular seed produces these positions; they are hand-selected for the trace. Seeded output requires the actual generator and source version.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](69-shuffle-identities-without-copying-corpus.md) · [Next lesson](71-record-the-seed-and-data-identity.md)

