First programs · Lesson 4 of 7

# Making decisions with if

A program sometimes needs to choose between two actions. This lesson uses `if` to decide whether a completed-lesson count makes sense before subtracting it.

## 1. State the rule in ordinary words

If a plan contains five lessons, a count of two completed lessons makes sense. A count of seven does not fit that plan. A negative completed count does not make sense either. We want to accept counts from zero up to the total, including both ends.

```text
completed:  -1   0   1   2   3   4   5   6
valid?       no  yes yes yes yes yes yes  no
```

**Validation** means checking that information follows a rule before using it. It does not mean guessing what an incorrect value was meant to be.

## 2. Read a comparison

```text
completed > total
```

`>` asks whether the left value is greater than the right value. The result is either true or false. With completed 7 and total 5 it is true. With completed 2 and total 5 it is false. Other comparisons include `<` (less than), `==` (equal) and `!=` (not equal). The two equals signs compare values; one equals sign assigns a value.

## 3. Choose an action

```text
if (completed > total) {
    puts("The completed count is too large.");
} else {
    int remaining = total - completed;
    printf("Remaining: %d\n", remaining);
}
```

The expression in parentheses after `if` is the **condition**. If it is true, run the first block between braces. Otherwise, `else` selects the second block. Only one of those blocks runs for this decision.

## 4. Check all invalid counts

```text
if (total < 0 || completed < 0 || completed > total) {
    puts("Please check the counts.");
} else {
    int remaining = total - completed;
    printf("Remaining: %d\n", remaining);
}
```

`||` means “or”. The condition is true when any of the three comparisons is true. Read it aloud: “total is negative, or completed is negative, or completed is greater than total”. We subtract only after all those problems have been ruled out. For nonnegative `int` values with completed no greater than total, the subtraction also stays within the range of `int`.

## 5. Work through examples

| Total | Completed | Action |
| --- | --- | --- |
| 5 | 2 | Display Remaining: 3 |
| 5 | 5 | Display Remaining: 0 |
| 5 | 7 | Display Please check the counts. |
| 5 | -1 | Display Please check the counts. |

## Try it

Predict the result for total 0 and completed 0. Then predict total -2 and completed 0.

### Answer

Zero and zero is valid and gives zero remaining. A negative total fails the first comparison, so the program asks you to check the counts.

## Where Umicom uses this idea

The Bits2Banking file `labs/native/first-c-programs/decisions.c` introduces checks before calculation. Framework applies the same principle when checking a requested file position or the size of an input. You do not need those larger implementations yet: being able to trace this decision is the objective of this lesson.

---

[Read this lesson in HTML](../../courses/learning-c/lessons/04-decisions-and-valid-input.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

First programs · Lesson 4 of 7.

[Previous: Variables and simple calculations](03-values-and-calculations.md) · [Next: Repeating work with a loop](05-repeat-with-a-boundary.md)

## Complete laboratory source

The short example above introduces the instructions. This is the complete source file, including its purpose and licence comment, for comparison with your local laboratory.

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
