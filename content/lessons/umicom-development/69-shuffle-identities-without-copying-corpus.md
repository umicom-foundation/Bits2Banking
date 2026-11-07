<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/69-shuffle-identities-without-copying-corpus.md

PURPOSE:
Explain the lesson: Shuffle identities without copying corpus.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Shuffle identities without copying corpus

## Prepare

Open `src/ai/training/dataset_split.c` and its public header in Framework. A dataset is a collection of examples. Training examples adjust a model; evaluation examples measure its behavior on a separate group. Use IDs 0 through 5 to stand for six complete sequences.

## Understand the idea

An identity is a reference to an existing example. Shuffling IDs changes which examples are selected while leaving their source bytes untouched.

## Work through the example

1. Locate `order[i] = i`.
2. Draw the ID array beside six unchanged source sequences.
3. Swap two IDs in the drawing.
4. Identify what changed and what did not.

## Check your reasoning

The order changes; corpus bytes do not move. A caller uses the returned ID to locate the corresponding sequence.

## If something differs

If the source collection changes after the split, the same ID might identify different bytes. Retain dataset identity and ordering together with the split.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_split.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](68-separate-training-and-evaluation-examples.md) · [Next lesson](70-follow-a-bounded-shuffle-step.md)

