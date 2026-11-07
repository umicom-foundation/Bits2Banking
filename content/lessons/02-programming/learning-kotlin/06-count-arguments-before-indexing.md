<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/06-count-arguments-before-indexing.md

PURPOSE:
Explain the lesson: Count arguments before indexing.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count arguments before indexing

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

Array positions start at zero. Reading arguments[1] needs at least two elements. The function first requires exactly two, so it also rejects unused extra input rather than silently ignoring it.

## Work through the example

Trace arrays [], ["4"], ["4","1"] and ["4","1","9"]. Record whether index zero or one is read in each case.

## Check your reasoning

Only the two-element array reaches conversion. The guard protects missing positions and makes the command-line format unambiguous.

## If something differs

If an indexing exception occurs, inspect whether conversion was moved above the size guard. Preserve the refusal rule when adding optional arguments.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-read-function-inputs-and-results.md) · [Next lesson](07-follow-an-early-return.md)

