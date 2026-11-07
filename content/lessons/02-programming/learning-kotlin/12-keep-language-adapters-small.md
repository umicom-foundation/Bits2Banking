<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/12-keep-language-adapters-small.md

PURPOSE:
Explain the lesson: Keep language adapters small.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep language adapters small

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

Input.kt converts text and presents results; Progress.kt owns the calculation in this exercise. The same separation is useful when a native Framework service later supplies a shared application model.

## Work through the example

Draw terminal → Kotlin conversion → progress rule → result → terminal. Mark the point where a future C bridge would call Framework. List which checks remain local to the terminal format.

## Check your reasoning

Argument count and text conversion remain presentation-boundary concerns. Shared domain rules should have one implementation rather than separate copies for Android, desktop and web.

## If something differs

If two frontends disagree, compare their accepted inputs and service calls first. A language lesson is not evidence that a production cross-language bridge has been implemented.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-choose-the-correct-jvm-entry-class.md)

