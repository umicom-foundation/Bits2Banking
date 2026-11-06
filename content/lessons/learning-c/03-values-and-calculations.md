First programs · Lesson 3 of 7

# Variables and simple calculations

A message can contain a result that changes. This lesson introduces variables: named places for values. We will count unfinished lessons using the same small numbers throughout.

## 1. Start with the question

There are five lessons in a reading plan. Two are complete. How many remain? On paper, calculate `5 - 2 = 3`. A program can perform the same subtraction.

## 2. Give each value a name

```text
int total = 5;
int completed = 2;
int remaining = total - completed;
```

`int` tells C that a value is an integer: a whole number such as 0, 2 or 5. The name after it identifies the variable. `=` gives the variable its starting value. Each semicolon ends a statement, which is one complete instruction.

In the third line, C reads the values of `total` and `completed`, subtracts them and stores the result in `remaining`. The variable names help people understand what the numbers mean.

```text
Name        Value after these three statements
total       5
completed   2
remaining   3
```

## 3. Display a number

```text
printf("Remaining: %d\n", remaining);
```

`printf` is another function declared in `stdio.h`. It can combine fixed text with values. `%d` marks the position where an integer will be displayed. The comma separates the format string from the value to insert. `\n` means a new line. Unlike `puts`, `printf` does not add a new line automatically.

With `remaining` equal to 3, the output is:

```text
Remaining: 3
```

## 4. Trace a changed value

Consider this extra statement after the calculation:

```text
completed = 3;
```

It changes `completed` to 3. It does not automatically recalculate `remaining`. A variable stores a value; it does not remember a spreadsheet formula. To calculate the new result, run the assignment again:

```text
remaining = total - completed;
```

Now `remaining` becomes 2. We omit `int` because we are changing an existing variable, not declaring a new one.

## 5. Try it

1. Draw a table with columns **total**, **completed** and **remaining**.
2. Use total 8 and completed 3. Write the calculated result.
3. Change completed to 4, without recalculating remaining. Write all three values again.
4. Recalculate remaining. Write the new result.

### Answer

The first result is 5. After changing only completed, the values are 8, 4 and 5. After recalculation they are 8, 4 and 4.

## Connect this to the laboratory

Open `labs/native/first-c-programs/values.c`. It uses these same names and the numbers 5 and 2. It writes `const int` instead of `int`. **const** tells the compiler that the program must not assign another value to that variable after initialisation. Its output checks are explained in the later testing lesson; they are not needed to understand the subtraction.

Studio can display counts such as open files in the same way: calculate a value, then show it. These small fixed numbers fit in an `int`. We will not assume that every possible number does; checking inputs is the next lesson.

## Before moving on

You can explain a declaration, an assignment and the difference between storing a result and recalculating it.

---

[Read this lesson in HTML](../../courses/learning-c/lessons/03-values-and-calculations.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

First programs · Lesson 3 of 7.

[Previous: Build and run your first C program](02-build-and-run-one-step.md) · [Next: Making decisions with if](04-decisions-and-valid-input.md)

## Complete laboratory source

The short example above introduces the instructions. This is the complete source file, including its purpose and licence comment, for comparison with your local laboratory.

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
