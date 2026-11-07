<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/05-visit-values-in-an-array.md

PURPOSE:
Explain the lesson: Visit values in an array.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Visit values in an array

An array keeps several values of the same type together. In this lesson, three activity counts are stored in one named array, then added.

## Prepare a small workspace

Open labs/native/first-c-programs/README.md in your Bits2Banking checkout. Its PowerShell and Bash instructions prepare CMake and Ninja. No earlier course is required: a source file is plain text describing instructions, and a compiler turns that text into a program.

Find arrays.c. Read the file before building the btb-first-arrays target.

## 1. Give each element a position

The declaration contains 2, 1 and 3. C numbers their positions 0, 1 and 2. These positions are called indices. The index is not the stored value.

Draw three boxes:

```text
index:     0   1   2
value:     2   1   3
```

An array with three elements has no element at index 3.

## 2. Follow the loop

The loop begins with index zero. Before each visit it checks index < count. It adds the selected value and increases the index.

Make a table with columns index, selected value and total after addition. The totals are 2, 3 and 6. At index 3 the condition is false, so the loop stops before reading outside the array.

The less-than sign matters. Changing it to less-than-or-equal would admit an invalid fourth visit.

## 3. Understand the count expression

Here sizeof activities measures the complete array in bytes. Dividing by the size of one element gives the element count.

This works where activities is an actual array. A function parameter written as an array is adjusted to a pointer, so the same expression cannot discover the caller's allocation there.

## Exercise and checks

Build and run this target using the lab instructions. Expect Entries: 3, total: 6. Record what actually happens.

In a personal copy, add a fourth small value. Predict the new count and total, then rebuild. The original output check should report the intentional difference until its expectation is reviewed.

This fixed example uses small values with a safe sum. Arbitrary inputs need additional range checks, introduced in the borrowed-array lesson.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/first-c-programs/arrays.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](06-pass-an-array-with-its-length.md)


[Previous: Describe a result, test it and investigate a failure](04-tests-and-debugging.md)
