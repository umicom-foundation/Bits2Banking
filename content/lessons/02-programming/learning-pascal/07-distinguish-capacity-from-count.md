<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/07-distinguish-capacity-from-count.md

PURPOSE:
Explain the lesson: Distinguish array capacity from occupied entries.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish array capacity from occupied entries

## Prepare
Open TCourseBook in coursebook.pas. Its array has eight entries, indexed zero through seven. Count records how many entries are currently occupied.

Capacity is allocated space. Count is current use. Empty space is not another course.

## Follow initialisation
InitialiseBook sets Count to zero and clears every entry. The next accepted addition writes Entries[Count], then increments Count.

With Count equal to three, the occupied indices are zero, one and two. Index three is the next free position.

## Lab
Draw eight boxes. Add courses A, B and C, marking the occupied boxes. Write Count beside the drawing after each addition.

Then fill the remaining five boxes. A ninth addition must fail before an array access at index eight. The capacity check uses Count greater than or equal to CourseCapacity.

## Read safely
The demo loops over public course numbers from one through Count. It does not loop over the full capacity when displaying the notebook. Printing all eight entries would expose unused slots.

## Troubleshoot
An off-by-one error is a boundary mistake of one position. A common example is permitting Count equal to capacity before writing Entries[Count]. Range checking can help detect the invalid access, but the operation should reject it explicitly.

## Check understanding
If Count is zero, how many course rows should appear? Zero. If Count is eight, what is the last occupied array index? Seven.

Framework containers also distinguish storage size from logical contents. Learn to identify both before iterating through an unfamiliar data structure.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-build-a-course-notebook.md) · [Next lesson](08-translate-public-course-numbers.md)

