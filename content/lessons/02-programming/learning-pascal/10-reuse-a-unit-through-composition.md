<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/10-reuse-a-unit-through-composition.md

PURPOSE:
Explain the lesson: Reuse progress arithmetic through a unit.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reuse progress arithmetic through a unit

## Prepare
Open coursebook.pas and lessonprogress.pas side by side. A Pascal unit groups declarations and implementations that other programs can use.

CourseBook imports LessonProgress. It stores a TLessonProgress inside each TCourseEntry.

## Follow the calls
Adding a course asks TryCreateProgress to validate its total and initial completion count. Completing a lesson calls TryCompleteLesson. Reading a remaining count calls RemainingLessons.

CourseBook does not calculate Total minus Completed independently. Its own responsibility is selecting a valid course entry and managing names and capacity.

## Lab
Trace TryCompleteCourseLesson for course one. List each check and function call until the Completed field changes.

Then try completing a course that already has all lessons completed. The progress unit rejects the increment. The book does not need a second copy of that arithmetic rule.

## Why this helps
If the progress contract changes, one implementation remains responsible for it. Tests for the collection still verify that it selects the correct entry and preserves other courses.

This is composition: a larger feature is built by connecting smaller, defined parts.

## Troubleshoot
A missing unit error concerns source search paths or compilation order. The supplied CMake file passes the source directory with Free Pascal's unit-search option and creates separate unit-output folders for each program.

## Production connection
Umicom applications follow the same architectural principle at a larger scale: reusable services belong in Framework. Language exercises can demonstrate the principle without becoming competing production services. State clearly which layer owns the reusable rule.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-validate-text-before-storage.md) · [Next lesson](11-preserve-results-on-refusal.md)

