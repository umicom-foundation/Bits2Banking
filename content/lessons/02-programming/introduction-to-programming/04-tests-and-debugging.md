<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/04-tests-and-debugging.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Describe a result, test it and investigate a failure

[Course contents](index.md) · [Previous: Repeat work and name a reusable operation](03-loops-and-functions.md)

## What a test does
A test calls some behaviour, observes a result and compares it with an expectation. A passing test supports that particular example. It does not prove every possible input or every user workflow works.

A bug is a mismatch between required and actual behaviour. Debugging is the process of finding why that mismatch occurs. An error message is evidence, not an instruction to change random code.

## Setup recap
Use [the setup and lab commands](index.md). The CMake build creates small example programs and tests. CTest starts the tests; it does not repair source or build missing executables.

## Write a test table
~~~text
total  completed  expected
5      2          3
5      5          0
5      6         -1
0      0          0
~~~
The first is an ordinary case. The next two sit on either side of a boundary. The last checks an empty case. Expected values should come from the rule, not from copying whatever the current program prints.

## Lab
1. Open labs/native/first-c-programs/test_counts.c.
2. Locate a call to BtbRemainingCount and its expectation.
3. Run the course's CTest command after a successful build.
4. If a test fails, record the test name, input, expected result, actual result and source revision.
5. Rebuild after fixing the cause. Run the affected test again, then related boundary cases.

## Practise investigation without changing the shared source
In a practice copy, deliberately change a correct comparison so completed == total becomes invalid. Predict which row in the table exposes that error. Restore the correct comparison after the experiment. This is a controlled experiment, not a suggested production change.

## Read diagnostics in stages
~~~text
compiler error -> source cannot become an object
linker error   -> required implementation is missing or inconsistent
test failure   -> executable ran but violated an expectation
launch error   -> operating system could not start the executable
~~~
These stages need different evidence. A stale executable can still launch after a compiler failure; its output does not validate the edited source.

## Exercise and worked answer
A test expects 0 but receives -1 for total = 5 and completed = 5. Inspect the input validation before the subtraction. A >= check would wrongly reject the equality case; the intended upper-bound rejection is completed > total.

## Next projects
Follow [Learning Data Structures](../learning-data-structures/index.md) to store several values, then [Learning Algorithms](../learning-algorithms/index.md) to find and order them. [Building a Text Editor in C](../../05-engineering/building-a-text-editor/index.md) combines input handling, state changes and tests in a small usable project.

## Limits
This lab teaches console logic. GUI click delivery, accessibility, disk failure and network behaviour need their own tests. Keep skipped tests distinct from passes, and never describe a command you have only written as a completed test run.

## Source map
Read `labs/native/first-c-programs/test_counts.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Repeat work and name a reusable operation](03-loops-and-functions.md)

[Next: Visit values in an array](05-visit-values-in-an-array.md)
