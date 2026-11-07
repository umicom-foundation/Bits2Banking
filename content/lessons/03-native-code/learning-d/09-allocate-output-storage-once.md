<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/09-allocate-output-storage-once.md

PURPOSE:
Explain the lesson: Allocate output storage once.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Allocate output storage once

## Prepare

Open batches.d and progress.d. The laboratory README explains installing DMD and compiling both modules with -unittest. These are language exercises using lesson counts; production shared services belong in Umicom Framework.

## Understand the idea

new int[totals.length] allocates enough result elements before the loop. Each successful calculation fills one position. This arrangement makes the result shape match the input shape.

## Work through the example

Count allocations visible in remainingBatch and writes to result for three input pairs. Explain why result[0] can be changed later without modifying totals[0].

## Check your reasoning

There is one explicit array allocation and three element assignments. The source test changes result[0] and checks that inputs retain their values.

## If something differs

If your adaptation assigns result = totals, it creates an alias rather than the intended independent output. Preserve the ownership decision.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-read-a-half-open-loop-range.md) · [Next lesson](10-trace-an-exception-partway-through-a-batch.md)

