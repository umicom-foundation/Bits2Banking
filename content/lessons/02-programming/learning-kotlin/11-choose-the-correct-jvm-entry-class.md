<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/11-choose-the-correct-jvm-entry-class.md

PURPOSE:
Explain the lesson: Choose the correct JVM entry class.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Choose the correct JVM entry class

## Prepare

Open Input.kt and Progress.kt in the Kotlin laboratory. Its README gives JDK, Kotlin, CMake and Ninja setup and commands for PowerShell and bash. Work with a copy of the lab; the examples calculate remaining lessons without writing course progress.

## Understand the idea

A jar can contain several classes with main functions. The laboratory names InputKt explicitly with java -cp because its file is Input.kt and has no package declaration. The classpath tells Java where to search.

## Work through the example

Locate progress-input.jar in the build command output. Explain the four parts of java -cp build/progress-input.jar InputKt 4 1, then identify which parts are application arguments.

## Check your reasoning

The jar supplies code, InputKt selects the entry class, and 4 and 1 become the two strings. The -cp option is consumed by Java, not by remainingFromArguments.

## If something differs

If Java cannot find InputKt, check the successful compilation, jar path and class spelling before changing the calculation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-catch-the-error-owned-by-the-boundary.md) · [Next lesson](12-keep-language-adapters-small.md)

