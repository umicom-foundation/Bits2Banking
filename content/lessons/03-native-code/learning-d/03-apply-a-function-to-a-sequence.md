<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/03-apply-a-function-to-a-sequence.md

PURPOSE:
Explain the lesson: Apply an existing function to a sequence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Apply an existing function to a sequence

A single-course calculation becomes useful for several courses when it can process a sequence. A sequence holds values in a known order. This lab reuses remainingLessons rather than rewriting its count rules.

## Setup recap

Install DMD and confirm `dmd --version` in PowerShell or bash. Open labs/languages/d-first-program. The first course chapter explains compiler setup. Keep progress.d and batches.d in the same directory.

## 1. Pair the input values

Write these inputs on paper:

~~~text
position:  0  1  2
total:     4  0  6
completed: 1  0  6
remaining: 3  0  0
~~~

Position zero selects the first element. Two input lists must have equal lengths so that each total has a corresponding completed count.

## 2. Read the boundary check

Find remainingBatch in batches.d. It accepts two read-only views of integer elements. The first enforce call rejects unequal lengths. The function then allocates a new result array and visits each valid position with foreach.

At each position, remainingLessons validates the pair and subtracts completed from total. The new function composes an existing behavior; it does not introduce a second version of the rule.

## 3. Compile both modules

~~~text
dmd -unittest -of=progress-checks progress.d batches.d
~~~

Run `./progress-checks.exe` in Windows PowerShell or `./progress-checks` in bash on Linux or macOS. Expected: all unit checks complete, then the existing main function prints Remaining lessons: 3.

## Exercise and explanation

Add totals [10, 10] and completed [10, 0], expecting [0, 10]. Next supply lists with different lengths and expect an exception. The length check must happen before indexing either list.

A module-not-found diagnostic usually means the compiler cannot locate progress.d. An assertion failure means the program ran and a prediction did not hold. Keep those two stages separate when troubleshooting.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/batches.d). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](04-distinguish-a-slice-from-independent-storage.md)


[Previous lesson: Describe a contract and run D unit tests](02-contracts-and-unit-tests.md)
