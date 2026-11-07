<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/12-check-each-course-independently.md

PURPOSE:
Explain the lesson: Check that one course cannot change another.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that one course cannot change another

## Prepare
Use the course notebook project and its check program. Independent entries should keep independent progress. Sharing an implementation does not mean sharing the same mutable record.

## Build a small experiment
Create course A with two lessons and course B with three. Complete one lesson of A.

Read both remaining counts. A should have one remaining; B should still have three. Then complete one lesson of B and read again.

This sequence catches accidental use of a fixed array index or a shared temporary record in place of each entry's own state.

## Lab
Draw the two records:
```text
A: Total 2, Completed 1
B: Total 3, Completed 0
```
Mark the exact field updated by the next call for B. Only B.Completed changes.

## Capacity boundary
The supplied checks fill all eight entries and verify that a ninth is refused. They then read an earlier course to ensure the refusal did not disturb valid records.

Testing after a refusal is valuable: an error may corrupt state that is only noticed by a later operation.

## Troubleshoot
If every course displays the same remaining count, inspect the display loop's course number and the lookup's index translation. If the data is correct but the output is wrong, avoid changing the arithmetic unit.

## Connect to Framework
Multiple windows can use one shared service while owning distinct document or account identifiers. The same distinction applies: shared code is desirable; unintended shared mutable state is a defect. Establish ownership at the record boundary.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook_checks.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-preserve-results-on-refusal.md) · [Next lesson](13-design-the-next-persistence-step.md)

