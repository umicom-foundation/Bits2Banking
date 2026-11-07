<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/09-explain-null-without-a-sentinel-number.md

PURPOSE:
Explain the lesson: Explain null without a sentinel number.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain null without a sentinel number

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

Zero can mean a course is complete. Using it for invalid input would combine two different outcomes. A nullable result keeps the distinction visible, and main checks it before printing success.

## Work through the example

Compare InputKt 4 4 with InputKt 4 bad. Write the intended message stream and exit status for both, using the README commands after building.

## Check your reasoning

The completed course prints Remaining lessons: 0 and returns normally. Invalid input prints usage to standard error and exits with status two.

## If something differs

If automation reports success for invalid input, inspect the exit status immediately after the Java command; a later command can replace it.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-validate-counts-after-conversion.md) · [Next lesson](10-catch-the-error-owned-by-the-boundary.md)

