<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-kotlin/04-test-valid-and-invalid-input.md

PURPOSE:
Explain the lesson: Test valid and invalid terminal input.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test valid and invalid terminal input

## A check needs an observable promise

A test supplies input and compares the actual result with a stated expectation. The expectation must describe the useful behaviour, not merely repeat the implementation.

This lab promises that valid progress produces a remaining count and invalid terminal input produces no result. It also promises that the command-line program reports failure to the operating system.

## Setup recap

Use a JDK and Kotlin compiler with the [input lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/README.md). Its CMake project compiles the three Kotlin source files into one jar. Read the command-line conversion chapter if `null`, an array or an exit status is unfamiliar.

## Divide the inputs

| Group | Example | Expected observation |
| --- | --- | --- |
| Ordinary success | 4 and 1 | 3 |
| Empty course | 0 and 0 | 0 |
| Completed course | 4 and 4 | 0 |
| Missing argument | 4 alone | null |
| Invalid text | 4 and word | null |
| Too large for Int | 2147483648 and 0 | null |
| Invalid model range | 4 and 5 | null |

The last two failures happen for different reasons. The first cannot be represented by Kotlin's Int. The second is representable but violates the course-progress rule.

## Lab

1. Open InputChecks.kt and find a case from each row.
2. Build the lab using the README commands.
3. Run `java -cp build/progress-input.jar InputChecksKt`.
4. Run the registered checks with `ctest --test-dir build --output-on-failure`.
5. In a separate practice copy, change one expected answer from 3 to 2. Rebuild and expect the check to fail.
6. Restore the expectation and rerun the same check.

The deliberate failure establishes that the check can detect that wrong answer. It does not establish every other property of the program.

## Exceptions and process results

The adapter catches IllegalArgumentException from the existing model. It does not catch every possible exception: a programming fault should not quietly become ordinary invalid input.

CTest also starts the command-line entry point. Its valid case checks visible output. Its invalid case expects a failing process status. These observations complement the direct function checks; a correct function can still be wired to a broken entry point.

## Exercise and explanation

Would one successful test with 4 and 1 establish safe array indexing? No. Missing and extra arguments exercise the length check. They belong in the input table because real terminal users can supply them.

## Troubleshooting

Check failures should name the input and expected outcome. If a test times out, distinguish compiler startup from a running program that never exits. Save the command, output and source revision before changing the test timeout.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/InputChecks.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-convert-command-line-text.md)


[Next: Read function inputs and results](05-read-function-inputs-and-results.md)
