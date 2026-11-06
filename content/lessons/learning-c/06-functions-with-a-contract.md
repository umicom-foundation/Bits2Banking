First programs · Lesson 6 of 7

# Writing and calling a function

You have already called library functions such as `puts`. Now you will define a small function of your own. It will calculate how many lessons remain, using the rules introduced earlier.

## 1. Give the work a name

```text
int RemainingLessons(int total, int completed)
{
    if (total < 0 || completed < 0 || completed > total) {
        return -1;
    }
    return total - completed;
}
```

`RemainingLessons` is the function's name. The first `int` is the type of value returned. Inside parentheses are two **parameters**, named inputs available inside the function: total and completed. Each parameter has a type and a name. The function body is the block between braces.

A `return` ends the current function call and supplies its result. Here, an invalid input returns -1. Valid inputs return a count of zero or more. We choose -1 as an error result because it cannot be a valid remaining count.

## 2. Call the function

```text
int remaining = RemainingLessons(5, 2);
```

The numbers 5 and 2 are **arguments**: values supplied for this call. The first goes to total and the second to completed. The function checks them, returns 3, and the calling statement stores that result in remaining.

```text
Caller supplies arguments: 5, 2
                 ↓
RemainingLessons: total = 5, completed = 2
                 ↓ check and subtract
Return 3 to the caller
                 ↓
Caller stores remaining = 3
```

## 3. Handle the result

```text
if (remaining < 0) {
    puts("Please check the counts.");
} else {
    printf("Remaining: %d\n", remaining);
}
```

The calculation function does not decide how a window should look. Its caller chooses what to display. This separation lets the same calculation serve a terminal program or a graphical application.

## 4. Describe its promise

A function's **contract** describes its inputs and result. Our contract is: total and completed are integers; both must be nonnegative and completed must not exceed total; valid input returns total minus completed; invalid input returns -1. Describing this in words makes it possible for another programmer to call the function correctly.

## 5. Follow the real laboratory

1. Open `labs/native/first-c-programs/counts.h`. It declares `BtbRemainingCount`, the laboratory's name for this operation. A declaration tells callers how to call it.
2. Open `counts.c` beside it. This contains the definition: the instructions that do the work.
3. Open `functions.c`. Find the call that supplies 5 and 2.
4. Compare the result handling with the example above.

You are following one operation through three files, not learning three unrelated topics. A header shares the declaration; a source file implements it; another source file calls it.

## Try it

Predict the results for (6, 4), (6, 6), (6, 7) and (-1, 0).

### Answer

The results are 2, 0, -1 and -1. The last two are rejected inputs. In the next lesson you will turn predictions like these into tests.

---

[Read this lesson in HTML](../../courses/learning-c/lessons/06-functions-with-a-contract.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

First programs · Lesson 6 of 7.

[Previous: Repeating work with a loop](05-repeat-with-a-boundary.md) · [Next: Test what you promised and understand failures](07-check-results-and-errors.md)

## Complete laboratory source

The short example above introduces the instructions. This is the complete source file, including its purpose and licence comment, for comparison with your local laboratory.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/functions.c
 *
 * PURPOSE:
 *   Call a separately implemented count function and handle rejection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "counts.h"

#include <stdio.h>

int main(void)
{
    const int remaining = BtbRemainingCount(5, 2);

    /* Negative one is reserved for rejection by this deliberately small API.
       It cannot be confused with a valid result, which is never negative. */
    if (remaining < 0) {
        (void)fputs("Counts do not fit the rule.\n", stderr);
        return 1;
    }
    if (printf("Remaining: %d\n", remaining) < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```
