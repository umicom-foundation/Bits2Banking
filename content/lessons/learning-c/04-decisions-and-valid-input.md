# Make a decision before calculating

Express an allowed range and follow both the accepted and rejected paths.

**Before you begin:** Read [Give values names and calculate a result](03-values-and-calculations.md), or return to it for a refresher.

## Write the rule in ordinary language

For this activity counter, total must be between zero and one thousand, including both ends. completed must be between zero and total. We choose a maximum of one thousand to keep the example bounded. It is a rule of this exercise, not a universal limit for programs.

A boundary is an edge of the allowed set. Zero and one thousand are total's boundaries. A value just outside a boundary is useful when checking the rule. For example, minus one and one thousand and one must be rejected. Checking only a comfortable middle value can miss mistakes at the edges.

## Translate one comparison at a time

total < 0 asks whether total is less than zero. total > 1000 asks whether it is greater than one thousand. completed < 0 rejects a negative completed count. completed > total rejects a count larger than the total.

The || operator connects these questions with or. The whole condition is true if any one rejection condition is true. C uses zero for false and a nonzero value for true in conditions. These comparisons produce an int result of zero or one. You do not have to understand machine bits to trace the choice.

## Follow the selected body

if (condition) chooses its body when the condition is true. else chooses the alternative when it is false. Braces make the start and end of each body visible. In decisions.c the initial values are total 5 and completed 7, so the rejection body is selected.

The rejection body displays Counts do not fit the rule. It does not calculate a negative remaining count and pretend it is a valid answer. The alternative subtracts only after all four checks permit it. This order is useful in larger systems: validate the conditions that make an operation safe before performing it.

## Separate rejection from a program crash

Here rejection is an expected demonstration result. If the rejection message is delivered successfully, main returns zero because the example behaved as designed. The later function uses a distinct negative return value to tell its caller that input was rejected. Different interfaces can use different conventions; their contracts must explain which one applies.

Neither a rejection message nor a nonzero completion result is automatically a crash. A crash means execution ended abnormally, for example because the operating system stopped an invalid memory access. Do not make a test accept a crash merely because both situations indicate a problem.

## Trace the alternatives

With total 5 and completed 2, every rejection question is false and the program displays Remaining: 3. With total 5 and completed 5, the remaining count is zero. With total 0 and completed 0, the empty set of activities is valid.

With total 1001, the second question rejects the input even when completed is zero. With completed minus one, the third rejects it. Check one case at a time on paper. Write the reason as well as the output; that helps distinguish a correctly rejected value from an accidentally rejected one.

## Use a condition to protect an operation

This example does not read text typed by a user. Its inputs are constants in the source so that you can focus on decisions. Accepting outside text would add parsing: recognising whether bytes follow a required grammar and safely turning them into values. That is a later topic.

OS and Kernel parsers also validate first, but have more responsibilities, including input length, integer overflow and memory ownership. Understanding this small choice prepares you to read those checks without claiming that this example is itself a secure parser.

## Complete example

From the laboratory file labs/native/first-c-programs/decisions.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/decisions.c
 *
 * PURPOSE:
 *   Choose a result only after checking a count's allowed range.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>

int main(void)
{
    const int total = 5;
    const int completed = 7;
    int written;

    /* Reject the state before subtracting: a completed count cannot exceed the
       total. This example reports rejection as an expected teaching outcome. */
    if (total < 0 || total > 1000 || completed < 0 || completed > total) {
        written = puts("Counts do not fit the rule.");
    } else {
        written = printf("Remaining: %d\n", total - completed);
    }
    if (written < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```

## Try it step by step

1. Draw a decision box with two exits: rejected and accepted.
2. Trace the initial 5 and 7 values through the four questions.
3. Repeat with 5 and 2, 0 and 0, 1001 and 0, and 5 and minus 1.
4. For each row, write both the selected message and the reason.

## Check your understanding

Why is total 5 with completed 5 accepted?

**Explanation:** The rule permits equality. completed > total is false when both are 5, so the remaining count can be zero. Changing > to >= would incorrectly reject completion of all activities.

## Before you continue

You can explain both paths and name at least one boundary case.

[Course contents](index.md) · [Words explained](../../courses/c-from-the-beginning/glossary.html) · [Practical lab guide](../../courses/c-from-the-beginning/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Give values names and calculate a result](03-values-and-calculations.md).

**Next:** [Repeat work without losing the stopping rule](05-repeat-with-a-boundary.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
