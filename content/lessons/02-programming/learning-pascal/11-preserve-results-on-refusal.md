<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/11-preserve-results-on-refusal.md

PURPOSE:
Explain the lesson: Preserve caller state when an operation is refused.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve caller state when an operation is refused

## Prepare
Read the first group of checks in coursebook_checks.pas. Number starts at 77, a recognisable sentinel. A sentinel in a test is a deliberately chosen value that makes an unexpected write easy to detect.

## Follow a refused addition
TryAddCourse validates capacity, name, duplicate status and progress before it writes any entry. If a check fails, it returns False.

The test then verifies both Book.Count and Number. Testing only the Boolean would miss a function that reports failure after partly changing the book.

## Lab
Start with an empty book and Number equal to 77. Try an empty name, an oversized name and a negative lesson total.

Expected: every attempt is refused, Count remains zero and Number remains 77.

Add one valid course. Then attempt the same exact name again. Count must remain one and the first course must remain intact.

## Compare semantic fields
The tests compare meaningful values rather than raw record bytes. A record's memory can contain padding or unused string capacity that is not part of its logical meaning.

## Troubleshoot
If refusal changes the output number, look for an assignment before the last validation step. Moving validation later is not a fix; the publication point should follow all required checks.

## Extend the test
Add an assertion that the first course's Total and Completed fields remain unchanged after a duplicate attempt. This checks the specific state users care about and provides a more informative failure than a general memory comparison.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/coursebook_checks.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-reuse-a-unit-through-composition.md) · [Next lesson](12-check-each-course-independently.md)

