# Repeat work without losing the stopping rule

Trace a loop's initial value, condition, body and update.

**Before you begin:** Read [Make a decision before calculating](04-decisions-and-valid-input.md), or return to it for a refresher.

## Why repeat an instruction?

Suppose you want to display three numbered steps. You could write three output calls, but a loop expresses repeated work with a shared rule. A loop is a control structure that runs a body repeatedly while its condition permits it. Each execution of the body is an iteration.

The repetition example deliberately uses only three iterations. You can inspect every state on paper. Real software may use larger limits, but a large number is not required to understand the mechanism. Finishing this lesson does not require judging how fast a processor runs.

## Read the four parts of for

In for (int step = 1; step <= 3; step = step + 1), the first part creates step and initialises it to one. This happens once before checking the loop condition. The condition asks whether step is less than or equal to three. The <= operator includes equality.

If the condition is true, the loop body runs. Afterwards the update step = step + 1 computes a value one greater and assigns it back to step. Assignment stores a new value; it differs from ==, which compares values. The condition is then checked again before another body execution.

## Follow the exact order

Initially step is one, so the first line is Step 1. The update makes it two. The condition permits another iteration, which displays Step 2. The next update makes it three, and equality is still permitted, so Step 3 appears.

The update then makes step four. Four is not less than or equal to three, so the body does not run again. Nothing displays Step 4. The program continues after the loop and flushes standard output. That final flush is outside the braces and runs once after a successful loop.

## Understand where a name is available

A scope is the region of source code where a name can be used. step is declared in the for initialisation and is available to the condition, update and body. It is not available after that for statement. This reduces the chance of accidentally using a loop's temporary counter elsewhere.

The counter has type int and these small values cannot overflow its range. If you change this pattern to accept very large outside values, you must reconsider the range and update. A stopping condition is not enough if arithmetic overflows before reaching it.

## Predict two common mistakes

If you change <= 3 to < 3, the iteration with step three is no longer permitted. The output becomes two lines. This is a boundary error, often called an off-by-one error: an operation includes one too many or one too few elements.

If you remove the update, step remains one and the condition remains true. The program can keep producing output. Do not deliberately run an endless example to understand it; trace it on paper. If you accidentally launch one in a terminal, use that terminal's interrupt action, commonly Ctrl+C, then correct the source before rebuilding.

## Connect loops to checked work

The output result is checked inside each iteration. If writing a line reports an error, return 1 leaves main immediately, including the loop. Successful earlier lines do not make a later error disappear.

A bounded loop is useful in systems software when visiting a known number of entries. Later lessons introduce arrays, which are ordered collections of elements. A loop visiting an array must use its real element count and valid indices. The current lesson uses no array access so you can learn control flow first.

## Complete example

From the laboratory file labs/native/first-c-programs/repetition.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/repetition.c
 *
 * PURPOSE:
 *   Trace a bounded loop one iteration at a time.
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
    /* The counter starts at one, is checked before each body, and advances
       after it. A small bound lets learners trace every state on paper. */
    for (int step = 1; step <= 3; step = step + 1) {
        if (printf("Step %d\n", step) < 0) {
            return 1;
        }
    }
    if (fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```

## Try it step by step

1. Draw columns for step before condition, condition result, displayed line and step after update.
2. Fill four rows, including the final condition check at four.
3. Predict the output if the upper bound becomes two.
4. On paper, remove the update and explain why the condition no longer changes.

## Check your understanding

Why does the body run at step three but not at step four?

**Explanation:** The condition is step <= 3. Equality at three is allowed. After the update to four, the next condition is false and execution continues after the loop.

## Before you continue

You can trace every condition check, including the one that stops the loop.

[Course contents](index.md) · [Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Make a decision before calculating](04-decisions-and-valid-input.md).

**Next:** [Give reusable work a clear contract](06-functions-with-a-contract.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
