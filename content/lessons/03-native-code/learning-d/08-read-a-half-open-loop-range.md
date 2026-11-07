<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/08-read-a-half-open-loop-range.md

PURPOSE:
Explain the lesson: Read a half-open loop range.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a half-open loop range

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

The range 0 .. totals.length includes zero and excludes the length. For three elements the indices are zero, one and two. Excluding the endpoint keeps each index within the array.

## Work through the example

Write the indices visited for lengths zero, one and three. For length three, calculate the three remaining counts using [4,0,6] and [1,0,6].

## Check your reasoning

An empty range visits no indices. The three-element result is [3,0,0]. The last valid index is length minus one when length is nonzero.

## If something differs

If a bounds error appears at the end, check for an inclusive range or a <= comparison introduced while rewriting the loop.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-check-related-lengths-together.md) · [Next lesson](09-allocate-output-storage-once.md)

