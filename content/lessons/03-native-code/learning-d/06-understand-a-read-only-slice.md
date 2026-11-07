<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/06-understand-a-read-only-slice.md

PURPOSE:
Explain the lesson: Understand a read-only slice.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand a read-only slice

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

A slice describes a sequence of elements and its length. const(int)[] lets this function read integer elements without modifying them through this parameter. It is not a promise that no other reference anywhere can change the storage.

## Work through the example

Draw totals [4,0,6] and completed [1,0,6]. Label each length three. Identify the operation that only reads these slices and the separate array receiving results.

## Check your reasoning

The loop reads input positions and writes result[index]. Its output allocation is independent of both input slices.

## If something differs

If inputs change unexpectedly in an extended example, inspect aliases held outside the function. const access is not synchronization between threads.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-name-a-module-and-import-a-function.md) · [Next lesson](07-check-related-lengths-together.md)

