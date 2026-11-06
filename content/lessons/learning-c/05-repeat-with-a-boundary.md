First programs · Lesson 5 of 7

# Repeating work with a loop

A **loop** repeats instructions. We will use one to display the numbers 1, 2 and 3. The important questions are where it starts, when it stops and what changes each time.

## 1. Write the repetition without a loop

```text
printf("Lesson %d\n", 1);
printf("Lesson %d\n", 2);
printf("Lesson %d\n", 3);
```

Only the number changes. A loop can express that pattern without writing the same instruction three times.

## 2. Read a for loop

```text
for (int lesson = 1; lesson <= 3; lesson = lesson + 1) {
    printf("Lesson %d\n", lesson);
}
```

The three parts inside parentheses are separated by semicolons. `int lesson = 1` sets the starting value and runs once. `lesson <= 3` asks whether lesson is less than or equal to 3; this is checked before every repetition. `lesson = lesson + 1` increases the value after each completed repetition. The braces contain the repeated instructions, called the **loop body**.

## 3. Trace every repetition

| Value before the check | Is it at most 3? | What happens? |
| --- | --- | --- |
| 1 | Yes | Print Lesson 1; increase to 2. |
| 2 | Yes | Print Lesson 2; increase to 3. |
| 3 | Yes | Print Lesson 3; increase to 4. |
| 4 | No | Leave the loop. Nothing is printed for 4. |

```text
Lesson 1
Lesson 2
Lesson 3
```

The last check matters as much as the first. It is what ends the repetition.

## 4. Recognise a common spelling

You will often see `++lesson` instead of `lesson = lesson + 1`. In this position both increase the variable by one. You may also see loops that start at zero. Those are useful for arrays, which we will study later.

## 5. Try two changes on paper

1. Change the starting value from 1 to 2. Keep the condition unchanged. Write the output.
2. Restore the starting value to 1. Change `<= 3` to `< 3`. Write the output.

### Answer

The first change prints Lesson 2 and Lesson 3. The second prints Lesson 1 and Lesson 2: “less than 3” excludes 3, whereas “less than or equal to 3” includes it.

## A stopping rule is part of the program

If the value never changes, a true condition may stay true forever. If it grows without a suitable limit, a number can exceed the range of its type. Our loop stops at a small fixed value. When you write another loop, write its start, stopping rule and update in words before trying it.

## Where this appears in the codebase

`labs/native/first-c-programs/repetition.c` contains a count-based loop. Framework uses loops to inspect lists of files and lessons. The larger examples have more checks, but the same three questions let you begin reading them.

## Before moving on

You can trace the value for every iteration, including the check that ends the loop. An **iteration** is one pass through the loop body.

---

[Read this lesson in HTML](../../courses/learning-c/lessons/05-repeat-with-a-boundary.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

First programs · Lesson 5 of 7.

[Previous: Making decisions with if](04-decisions-and-valid-input.md) · [Next: Writing and calling a function](06-functions-with-a-contract.md)

## Complete laboratory source

The short example above introduces the instructions. This is the complete source file, including its purpose and licence comment, for comparison with your local laboratory.

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
