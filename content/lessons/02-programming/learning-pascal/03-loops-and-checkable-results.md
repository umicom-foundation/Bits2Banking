<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/03-loops-and-checkable-results.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Loops and checkable results

[Course contents](index.md) · [Previous: Values, functions and input validation](02-values-functions-and-validation.md)

## Repeat an operation deliberately
A loop repeats instructions according to a rule. The progress program prints one practice-item line for each remaining item. The loop counter Item tells us which repetition is happening.

## Prepare and run
Use [the course setup](index.md) to build the Pascal lab. The complete program is labs/languages/pascal-progress/progress.pas. Run progress with argument 2 and read:
~~~text
Remaining: 3
Practice item 1
Practice item 2
Practice item 3
~~~
The three practice lines are produced by:
~~~pascal
for Item := 1 to Remaining do
  WriteLn('Practice item ', Item);
~~~
The lower bound is 1 and the upper bound is Remaining. WriteLn receives a string and an integer; it formats them in order. The loop increments Item as it proceeds.

## Trace before running
1. Set the input on paper to 4.
2. Calculate Remaining = 5 - 4 = 1.
3. Predict one iteration with Item = 1.
4. Run progress 4 and compare the actual output.
5. Repeat with input 5. Remaining is zero, so the upward loop has no iterations.

The empty case matters. Printing one practice line when nothing remains would be a logic error even though the program compiled.

## What a test checks
The lab's check_progress.cmake starts the executable with several inputs. It checks successful output and checks that rejected input produces an error exit. This tests the boundary between terminal text and program behaviour.

A test is an executable question about behaviour. It does not prove every possible property. The supplied checks cover valid counts, a completed course and selected invalid input. They do not prove that every compiler or terminal behaves identically.

Use the course's ctest command after a successful build. If it reports a failure, read the named check, the command result and the output. Fix the source that caused the mismatch; do not change the expected answer merely to obtain a green result.

## Extend the exercise
In your practice copy, display both the completed and remaining totals. Write the expected output for inputs 0, 2 and 5 first. Keep the invalid-input behaviour. Then add a check for the new line.

Worked answer for input 2: completed is 2, remaining is 3, and there are three practice-item lines. The sum of the two counts should be 5.

## Read the Umicom connection
The C first-programs/test_counts.c file checks the same boundary values without launching a terminal program. Comparing the two styles introduces a unit test, which calls a function directly, and a process test, which starts an executable.

## Recovery
A timeout means the process did not finish within the check's limit. An unexpected exit means it finished but reported a different result. Neither is a passing test. Preserve the diagnostic and reproduce the smallest failing input before editing.

## Source map
Read `labs/languages/pascal-progress/check_progress.cmake` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Values, functions and input validation](02-values-functions-and-validation.md)

[Continue: Group related values in a record](04-group-values-in-records.md)
