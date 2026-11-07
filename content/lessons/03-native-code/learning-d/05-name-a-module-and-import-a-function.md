<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/05-name-a-module-and-import-a-function.md

PURPOSE:
Explain the lesson: Name a module and import a function.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Name a module and import a function

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

A module groups declarations. batches names itself with module batches and imports only remainingLessons from progress. A selective import makes the dependency visible where the batch operation is defined.

## Work through the example

Find the module declaration and import. Draw batches → progress. List which file defines remainingBatch and which defines remainingLessons.

## Check your reasoning

The batch function lives in batches.d and delegates each count pair to progress.d. There is one range calculation.

## If something differs

If the compiler cannot find progress, check source paths and module spelling. Copying the function into batches would hide the build problem and create duplicate rules.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-distinguish-a-slice-from-independent-storage.md) · [Next lesson](06-understand-a-read-only-slice.md)

