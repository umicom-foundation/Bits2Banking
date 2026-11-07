<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/03-loops-and-functions.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Repeat work and name a reusable operation

[Course contents](index.md) · [Previous: Values, variables and decisions](02-values-and-decisions.md) · [Next: Describe a result, test it and investigate a failure](04-tests-and-debugging.md)

## Two ways to reduce repetition
A loop repeats instructions while a condition permits it. A function groups an operation under a name so callers can use it. A loop decides how many times to work; a function defines the work.

## Setup recap
Build the first-c-programs lab using [the course setup](index.md). Read repetition.c, functions.c, counts.h and counts.c. A header, ending in .h, declares the operation callers can use; the .c implementation supplies its behaviour.

## Trace a small loop
~~~c
for (int item = 1; item <= 3; ++item) {
    printf("Practice item %d\n", item);
}
~~~
Read the three parts in order: initialise item to 1; continue while item is at most 3; increase item by one after each body. The body runs with 1, then 2, then 3. The next test sees 4 and stops.
~~~text
check 1 -> print 1 -> increment
check 2 -> print 2 -> increment
check 3 -> print 3 -> increment
check 4 -> stop
~~~
If you replace <= with <, the last printed item becomes 2. A one-character edit can change the meaning.

## Call a function
The repository functions.c calls BtbRemainingCount(5, 2). The values inside parentheses are arguments: inputs supplied by the caller. The result is a returned value.
~~~c
const int remaining = BtbRemainingCount(5, 2);
~~~
The function's contract reserves -1 for invalid input. Its caller checks for that result before printing a count. A contract is a promise about accepted inputs, outputs and errors.

## Lab
1. Run btb-first-functions. Expect "Remaining: 3".
2. Follow its include to counts.h, then open counts.c.
3. Locate the rejection check. Explain why -1 cannot also be a valid remaining count.
4. Read test_counts.c to see independent callers checking the promise.
5. Write down expected loop output before running repetition.c; compare with that source's actual loop bounds.

## Exercise and worked answer
A function receives total = 3 and completed = 3. Its valid result is 0, not -1. A caller must not treat every nonpositive value as failure. It should distinguish the reserved negative error from a legitimate empty remainder.

## Connect to Framework
Framework-owned services let different applications call the same implementation. The small counts library demonstrates the shape of that arrangement without requiring a large build. A production service also needs ownership, concurrency and persistence decisions appropriate to its job.

## Troubleshooting
An "undefined reference" during linking often means the declaration was found but the implementation was not linked. Build this lab through its CMakeLists.txt so counts.c accompanies functions.c. Compiling functions.c alone cannot supply BtbRemainingCount.

## Source map
Read `labs/native/first-c-programs/functions.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Values, variables and decisions](02-values-and-decisions.md) · [Next: Describe a result, test it and investigate a failure](04-tests-and-debugging.md)
