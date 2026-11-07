<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/07-check-related-lengths-together.md

PURPOSE:
Explain the lesson: Check related lengths together.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check related lengths together

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

The two arrays form pairs by position. Their lengths must match before the loop can safely read completed[index] for every total. Equal lengths also protect the meaning of each pair.

## Work through the example

Trace totals [4,6] with completed [1]. Explain why using the shorter length would silently discard an unfinished course instead of reporting malformed input.

## Check your reasoning

The enforce call rejects the request before allocating the result. The caller receives an exception, not a partly useful answer.

## If something differs

If an extra value is ignored, inspect the loop bound and whether the equal-length guard was replaced by a minimum-length calculation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-understand-a-read-only-slice.md) · [Next lesson](08-read-a-half-open-loop-range.md)

