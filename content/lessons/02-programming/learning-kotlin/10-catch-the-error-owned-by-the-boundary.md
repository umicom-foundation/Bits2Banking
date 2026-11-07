<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/10-catch-the-error-owned-by-the-boundary.md

PURPOSE:
Explain the lesson: Catch the error owned by the boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Catch the error owned by the boundary

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

require throws IllegalArgumentException. The wrapper catches that expected input error and converts it to a nullable result. It does not catch every throwable and pretend every failure is a user's typo.

## Work through the example

Find the two require statements in Progress.kt. List the inputs each rejects. Then locate the catch clause in Input.kt and match the exception type.

## Check your reasoning

The total rule rejects negatives; the completed rule rejects negatives and values above total. The wrapper has one public refusal representation for both.

## If something differs

If another exception appears, investigate it rather than broadening the catch blindly. A broken installation or programming defect may need a different diagnosis.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-explain-null-without-a-sentinel-number.md) · [Next lesson](11-choose-the-correct-jvm-entry-class.md)

