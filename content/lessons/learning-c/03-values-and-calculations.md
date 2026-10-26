# Give values names and calculate a result

Trace a small calculation and understand the difference between a value, a name and displayed text.

**Before you begin:** Read [Prepare, build and run without mixing the steps](02-build-and-run-one-step.md), or return to it for a refresher.

## Start with a familiar count

Suppose there are five activities and you have completed two. Three remain. The values example expresses this subtraction using names. A variable is a named object that holds a value. A type describes what kinds of values and operations are permitted for that object.

int is an integer type. It represents whole numbers within a finite range; it is not an unlimited mathematical integer. These examples use small counts that fit every conforming int range. Later systems lessons must check boundaries before arithmetic rather than assuming every large value fits.

## Read a declaration from left to right

In const int total = 5;, int describes the type and total is the name. The initial value is 5. The equals sign supplies that initial value here; it is not a comparison. The semicolon ends the declaration. const says that this object cannot be modified through its declared name after initialisation.

The name completed holds 2. The expression total - completed subtracts those values, and remaining is initialised with the result. An expression is a piece of code that computes a value or designates an object. You can replace each name with its current value on paper to trace this example: 5 - 2 gives 3.

## Distinguish calculation from presentation

printf("Remaining: %d\n", remaining) displays formatted output. A format string describes the text and how supplied values should appear. %d is a conversion for an int argument. It does not mean the letter d should appear on screen.

The comma separates the format string from the argument containing the value. The sequence \n inside a C string represents a newline. The backslash is an escape character, introducing a special spelling inside the source text. The expected result is Remaining: 3 on its own line. The compiler does not print variable names unless you explicitly ask it to.

## Use the matching type

A format conversion and its argument must agree. This course uses %d with int. Other types can require different conversions. Do not change a type and assume every output format remains correct. Compiler warnings can help identify some mismatches.

printf returns a negative number if an output error is detected. The program checks that result and then flushes stdout, as in the first lesson. The success result returned from main is separate from the remaining count. A program can successfully calculate zero remaining activities and still return zero to indicate success; the two zeros play different roles.

## Ask what the rule permits

Try total equal to 5 and completed equal to 5: the remaining count is zero. Try completed equal to 7: simple subtraction gives negative two, but a completed count greater than the total does not fit our activity model. The machine does not automatically know that rule.

A domain rule describes what values make sense for a particular task. It is separate from what the integer type can represent. The next lesson checks the rule before subtracting. These examples describe activity counts, not account balances; financial values need additional contracts, units and checked arithmetic.

## Make one intentional change

Change only completed from 2 to 4 in a working copy. Predict Remaining: 1. Save, rebuild the values target and run it if your tools are ready. Compare the observed line with your prediction. If you only changed the paper example, record it as a prediction rather than an executed test.

Keeping one change at a time makes a mismatch easier to explain. You do not need to change all examples or understand every computer type before learning this relationship.

## Complete example

From the laboratory file labs/native/first-c-programs/values.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/values.c
 *
 * PURPOSE:
 *   Calculate a small count using named integer values.
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
    const int completed = 2;
    const int remaining = total - completed;

    /* These fixed, small inputs make subtraction representable. Later lessons
       move input validation into a reusable function before doing arithmetic. */
    if (printf("Remaining: %d\n", remaining) < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```

## Try it step by step

1. Create three columns headed total, completed and remaining.
2. Fill rows for 5 and 2, 5 and 5, and 8 and 3.
3. Point to the calculation in values.c and then to the instruction that displays it.
4. Explain why completed equal to 7 needs more than just subtraction when total is 5.

## Check your understanding

Does the name remaining itself appear because it is passed to printf?

**Explanation:** No. printf receives the value held by remaining. The format string determines the displayed words. With total 5 and completed 2, %d displays 3.

## Before you continue

You can calculate a result on paper and identify where the program enforces, or does not enforce, the task's rules.

[Course contents](index.md) · [Words explained](../../courses/c-from-the-beginning/glossary.html) · [Practical lab guide](../../courses/c-from-the-beginning/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Prepare, build and run without mixing the steps](02-build-and-run-one-step.md).

**Next:** [Make a decision before calculating](04-decisions-and-valid-input.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
