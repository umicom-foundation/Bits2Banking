<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/04-distinguish-a-slice-from-independent-storage.md

PURPOSE:
Explain the lesson: Distinguish a slice from independent storage.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish a slice from independent storage

When two variables describe the same elements, changing an element through one variable can be visible through the other. Understanding this relationship helps prevent accidental changes to input data.

## Setup recap

Use DMD and both files from labs/languages/d-first-program. Compile with `dmd -unittest -of=progress-checks progress.d batches.d`. Run the resulting program using the operating-system command in the laboratory README.

## 1. Draw the ownership

A dynamic array value describes a length and a reference to elements. Draw a box for the variable and a separate row for the elements. A second slice may point at that same row.

In remainingBatch, `new int[totals.length]` creates a new result row. The input views are const through the function. The caller still owns the input values and must not assume every slice copy creates new elements.

## 2. Follow the mutation check

The unittest builds totals [4, 0, 6] and completed [1, 0, 6], calls remainingBatch, then changes result[0] to 2. The next assertion checks that the two input arrays remain unchanged.

This is a meaningful independence check. Merely checking the original result [3, 0, 0] would not reveal an implementation that accidentally reused input storage.

## 3. Follow a rejected batch

The call with totals [4, 2] and completed [1, 3] fails on the second pair. A partly filled internal array may exist briefly, but no result is returned to the caller. The exception is the outcome of the whole call.

That behavior should be stated before a caller relies on it. A streaming interface might instead publish partial results and would need a different contract.

## Exercise and explanation

Add an invalid final pair to a three-element batch. Check that an exception occurs, then inspect the original input arrays. Neither should have changed. Explain why the test must inspect values as well as the failure path.

An @safe function can still contain incorrect arithmetic or rules. The annotation does not replace the explicit count and length checks. Keep both the language guarantees and the application contract visible.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-apply-a-function-to-a-sequence.md)


[Next: Name a module and import a function](05-name-a-module-and-import-a-function.md)
