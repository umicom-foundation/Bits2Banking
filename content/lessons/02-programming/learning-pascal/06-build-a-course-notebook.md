<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/06-build-a-course-notebook.md

PURPOSE:
Explain the lesson: Build a small course notebook.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a small course notebook

## Prepare
Install Free Pascal, CMake and Ninja. Open the Bits2Banking repository in a terminal and follow the exact commands in labs/languages/pascal-progress/COURSE-BOOK.md. The exercise compiles independently of Umicom Applications.

A notebook here is an in-memory collection of course names and progress records. Closing the program discards these sample values; it does not yet save a file.

## Read the caller
The demo declares one TCourseBook, initialises it, adds two courses and completes two lessons of the first course. It then reads each remaining count and prints it.

TryAddCourse returns a Boolean. True means addition succeeded. The CourseNumber argument receives the new one-based number only on success.

## Lab
Predict the output before running:
```text
1. Learning C: 2 remaining
2. Introduction to RISC-V: 3 remaining
```
The first course has four lessons and two completions. The second has three lessons and no completions.

Add a third course through the same function. Do not assign directly into the Entries array. Complete one lesson and calculate its remaining count by hand.

## Understand separation
The demo controls the sequence of actions. CourseBook controls collection rules. LessonProgress controls progress arithmetic. This makes it possible to change the presentation without copying the calculation into each caller.

## Troubleshoot
If the executable is missing, check whether compilation succeeded before attempting to launch it. The guide gives separate PowerShell and Bash paths. A program that exits with status one rejected an operation; do not interpret its absence of output as an empty successful notebook.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook_demo.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-share-a-unit-and-preserve-state.md) · [Next lesson](07-distinguish-capacity-from-count.md)

