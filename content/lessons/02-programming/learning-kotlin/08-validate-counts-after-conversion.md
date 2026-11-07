<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/08-validate-counts-after-conversion.md

PURPOSE:
Explain the lesson: Validate counts after conversion.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate counts after conversion

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

Conversion establishes that text represents an Int. It does not establish that the counts make sense. remainingLessons requires a nonnegative total and completed between zero and total.

## Work through the example

Trace ["4","5"], ["4","-1"], ["0","0"]. Separate the conversion result from the range result in two columns.

## Check your reasoning

All strings convert. The first two violate the progress rule and become null through the catch block. Zero total and zero completed returns zero successfully.

## If something differs

If negative counts appear accepted, verify the call still delegates to Progress.kt. Do not duplicate a weaker range rule in the command-line wrapper.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-follow-an-early-return.md) · [Next lesson](09-explain-null-without-a-sentinel-number.md)

