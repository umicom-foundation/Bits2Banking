<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/05-read-function-inputs-and-results.md

PURPOSE:
Explain the lesson: Read function inputs and results.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read function inputs and results

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

A function gives a name to a calculation. remainingFromArguments receives an Array<String> and returns Int?, meaning an integer or null. The question mark is part of the type; callers must account for refusal.

## Work through the example

Draw a box labelled remainingFromArguments. Put ["4", "1"] at its input and 3 at its output. Put ["four", "1"] at another input and trace where null is returned.

## Check your reasoning

The valid case reaches remainingLessons. The text four fails conversion before the range rule runs. Input conversion and progress calculation have distinct responsibilities.

## If something differs

If you expect an exception for four, read toIntOrNull: this conversion reports unsuccessful conversion with null.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-test-valid-and-invalid-input.md) · [Next lesson](06-count-arguments-before-indexing.md)

