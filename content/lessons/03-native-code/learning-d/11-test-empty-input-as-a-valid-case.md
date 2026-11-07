<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/11-test-empty-input-as-a-valid-case.md

PURPOSE:
Explain the lesson: Test empty input as a valid case.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test empty input as a valid case

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

An empty batch contains no courses. Both lengths are zero, so the shape rule passes and the loop has no work. Returning an empty result is a useful defined outcome.

## Work through the example

Contrast remainingBatch([],[]) with remainingBatch([4],[]). Write which case is empty-but-valid and which contains a missing partner.

## Check your reasoning

The first returns an array with length zero. The second throws. Empty data and inconsistent data are different conditions.

## If something differs

If both cases are rejected, check whether a new nonempty requirement was introduced. Add such a restriction only when the application actually needs it.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-trace-an-exception-partway-through-a-batch.md) · [Next lesson](12-keep-checks-enabled-during-learning.md)

