<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/08-observe-output-and-completion.md

PURPOSE:
Explain the lesson: Observe output and completion.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Observe output and completion

A command can print text and also report whether it completed successfully. These are separate channels of information.

## Setup recap

Open a terminal in your Bits2Banking checkout and use the first-c-programs guide. Build the greeting target. A terminal accepts commands; the program writes its normal output back to that terminal.

No previous testing course is required. A test is simply a repeatable check against a stated expectation.

## 1. Observe the greeting

The greeting program is expected to print Hello, learner. It also returns zero when its output operations succeed.

In PowerShell, read $LASTEXITCODE immediately after the executable. In Bash, use echo $? immediately after it. Another command can replace the result you meant to inspect.

A printed greeting alone does not prove that the program finished successfully.

## 2. Separate normal output from diagnostics

Programs conventionally write their ordinary results to standard output and explanations of errors to standard error. A test can inspect both.

When a command fails, preserve its diagnostic text. Do not replace it with a guessed explanation such as “the compiler is broken.”

## 3. Read the output check

The lab's check_output.cmake runs a program and compares its result with the corresponding expected text file. Read how it handles line endings before interpreting a difference.

Text checks should deliberately account for platform differences that are irrelevant to the contract, while retaining differences that reveal changed behavior.

## Exercise

Write down the expected greeting text and completion result. Run once and fill a separate actual-result column.

Then deliberately change the greeting in a personal copy. Predict which output check changes. Restore or review the intended wording before treating the test as healthy again.

## Troubleshooting

If the test cannot find an executable, build it first. If no tests are found, inspect BUILD_TESTING and the selected build directory. A skipped or missing test supplies no behavioral evidence.

If output matches but completion is nonzero, inspect the reported failure rather than declaring success from appearance.

These habits also apply to Framework tools: record the command, relevant source revision, diagnostics and result together.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/first-c-programs/check_output.cmake). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-connect-source-files-at-link-time.md)


[Next: Give results meaningful names](09-name-results-with-an-enumeration.md)
