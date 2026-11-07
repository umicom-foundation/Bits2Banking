<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/12-keep-checks-enabled-during-learning.md

PURPOSE:
Explain the lesson: Keep checks enabled during learning.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep checks enabled during learning

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

The unittest blocks state expected behavior, including thrown errors. DMD's -unittest option includes them. Assertions are diagnostic checks, so exercise commands should not use options that disable them.

## Work through the example

Read every assertion in batches.d and label it value, independence, empty input or refusal. Add a prediction for totals [10,10] with completed [10,0] before editing a disposable copy.

## Check your reasoning

The prediction is [0,10]. An observed run should be recorded with compiler version and command; reading assertions does not prove they executed.

## If something differs

If no checks seem to run, confirm both modules were compiled and -unittest was present. A successful main message alone does not identify every included test.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-test-empty-input-as-a-valid-case.md)

