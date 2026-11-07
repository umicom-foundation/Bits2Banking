<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/09-validate-text-before-storage.md

PURPOSE:
Explain the lesson: Validate a name before bounded storage.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate a name before bounded storage

## Prepare
Open ValidName and TCourseEntry. Name is a bounded short string with space for forty characters. The incoming parameter is an ordinary String in this exercise.

The lab deliberately supports printable ASCII. This gives each permitted character a single byte and keeps the first storage exercise understandable.

## Read the policy
A name must contain one to forty bytes. Every byte must be in the printable ASCII range, 32 through 126. At least one character must be something other than a space.

The checks happen before assigning the input to the bounded field. Silent truncation would make different long names appear identical.

## Lab
Classify these names:
- an empty string;
- three spaces;
- Learning C;
- forty A characters;
- forty-one A characters;
- C followed by a newline.

Expected: Learning C and the forty-character name are accepted. The others are refused.

## Explain a limit
A restriction to ASCII is a documented teaching boundary, not a general solution for international names. UTF-8 characters can occupy multiple bytes. Extending the policy requires deciding whether the limit counts bytes, code points or displayed characters.

## Troubleshoot
Do not remove the length check because the assignment appears to work. First check whether data was truncated. Likewise, allowing newline characters would break the one-course-per-line report.

## Connect to applications
A production Framework text field may already provide encoding and validation services. Reuse those contracts when building an application. Keep this small Pascal implementation as a language exercise with its limits visible.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-translate-public-course-numbers.md) · [Next lesson](10-reuse-a-unit-through-composition.md)

