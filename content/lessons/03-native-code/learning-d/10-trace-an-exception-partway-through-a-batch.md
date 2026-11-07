<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/10-trace-an-exception-partway-through-a-batch.md

PURPOSE:
Explain the lesson: Trace an exception partway through a batch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace an exception partway through a batch

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

The first pair may be valid while a later pair fails the existing range rule. An exception leaves the function before return result, so the caller does not receive that partially filled array.

## Work through the example

Trace totals [4,2] and completed [1,3]. Mark the first assignment, the second call and the point at which normal control flow ends.

## Check your reasoning

The first result element becomes three internally. The second call throws because completed exceeds total. No result is returned.

## If something differs

If a caller displays partial results, inspect its own error-handling or callbacks. This function has no progress callback and publishes only at its return.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-allocate-output-storage-once.md) · [Next lesson](11-test-empty-input-as-a-valid-case.md)

