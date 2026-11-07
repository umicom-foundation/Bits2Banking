<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/07-follow-an-early-return.md

PURPOSE:
Explain the lesson: Follow an early return.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow an early return

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

The Elvis operator ?: supplies an alternative when its left side is null. Here the alternative is return null, which exits the entire function. It is not a numeric default.

## Work through the example

Trace ["8","bad"] one statement at a time. Write total after its conversion, then identify the exact statement that ends the function. Repeat with ["bad","2"].

## Check your reasoning

In the first case total is eight, then completed conversion ends the function. In the second case the function exits before attempting completed. Neither calls remainingLessons.

## If something differs

If you substitute zero for failure, the caller can no longer distinguish a legitimate zero remaining from invalid input.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-count-arguments-before-indexing.md) · [Next lesson](08-validate-counts-after-conversion.md)

