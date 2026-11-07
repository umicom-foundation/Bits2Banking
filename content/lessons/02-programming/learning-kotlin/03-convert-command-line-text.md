<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/03-convert-command-line-text.md

PURPOSE:
Explain the lesson: Convert command-line text into checked values.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Convert command-line text into checked values

## Text is not yet a number

A terminal passes arguments to a program as text. In `InputKt 4 1`, the two values arrive as strings. Before subtracting them, the program must answer two questions: do they represent integers, and are those integers allowed by the progress rule?

`remainingFromArguments` is an adapter: a small function that translates the terminal's representation into the model's inputs. It does not change the existing `remainingLessons` rule.

## Setup recap

Install a JDK, the Kotlin command-line compiler, CMake and Ninja. In a new terminal run `java -version` and `kotlinc -version`. Choose your practice folder and follow the [complete lab commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/README.md). Keep Progress.kt, Input.kt and InputChecks.kt together.

## Read the conversion

~~~kotlin
val total = arguments[0].toIntOrNull() ?: return null
~~~

`val` declares a value that this function does not reassign. The array subscript selects the first argument. `toIntOrNull` attempts a decimal integer conversion. If conversion fails, it returns `null`, which means no integer result. The `?:` operator uses its right-hand expression only when the left side is null.

An `Int?` return type allows either an integer or null. Zero is a real result; it must not mean failure.

The function checks the array length before reading its elements. After conversion it calls the original model. That model rejects a negative total, a negative completed count, or completed greater than total.

## Lab

1. Build the lab and run `java -cp build/progress-input.jar InputKt 4 1`. Expect Remaining lessons: 3.
2. Run with `4 4`. Expect zero remaining.
3. Run with `4 word`. Expect a usage message and nonzero exit status.
4. Run with `4 5`. Conversion succeeds, but the model rejects the values.
5. Read the status immediately: `$LASTEXITCODE` in PowerShell or `echo $?` in bash.
6. Compare the parsing branch with the model-validation branch.

A program has two output streams. Ordinary results go to standard output; diagnostic messages go to standard error. This example sends usage information to the latter.

## Exercise and explanation

Why not return zero after invalid input? Zero also means a completed course. A separate null result prevents invalid input from looking successful.

## Troubleshooting

A class-not-found error usually means the class path or entry-point name is wrong. This lab contains several entry points, so use the explicit class name shown above. Do not replace it with an assumed executable-jar command.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Input.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](02-values-functions-and-checks.md) · [Next lesson](04-test-valid-and-invalid-input.md)

