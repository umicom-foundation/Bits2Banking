<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/08-translate-public-course-numbers.md

PURPOSE:
Explain the lesson: Translate a public number into an array index.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Translate a public number into an array index

## Prepare
Read TryCompleteCourseLesson and TryReadRemaining. Public course numbers start at one because that is convenient in the displayed list. The underlying Pascal array starts at zero.

These are two representations of the same position. The translation is explicit:
```text
array index = course number - 1
```

## Validate before translating
The functions first require CourseNumber to be at least one and no greater than Book.Count. Only then do they subtract one and access Entries.

For course number one, the index is zero. For course number eight in a full book, the index is seven.

## Lab
Make a table for numbers -1, 0, 1, 3 and 4 when Count is three. The first two and the last are refused. Numbers one and three refer to occupied entries.

Explain why checking only CourseNumber less than or equal to eight is insufficient. An array position may exist physically without holding a course.

## Output preservation
TryReadRemaining keeps its output unchanged when the number is invalid. Set Remaining to 99, request course zero and inspect the result. The function returns False and Remaining stays 99.

## Troubleshoot
If completing course one changes course two, inspect the translation. If an invalid number causes a range-check failure, inspect the validation order. Do not solve either problem by disabling range checks.

## Extend carefully
If a future user interface sorts the displayed courses, a visible row number will no longer be a stable identity. Introduce an explicit identifier rather than silently reusing the current array position as a permanent key.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-distinguish-capacity-from-count.md) · [Next lesson](09-validate-text-before-storage.md)

