# Give reusable work a clear contract

Understand a declaration, an implementation, a caller and a rejected result.

**Before you begin:** Read [Repeat work without losing the stopping rule](05-repeat-with-a-boundary.md), or return to it for a refresher.

## Name a repeated piece of work

The count rule is useful beyond one example. We can place it in a function named BtbRemainingCount. A function lets a caller request a defined operation without rewriting its body every time. Reuse only helps if callers know what the operation accepts and what it promises.

A contract is that agreement. Here total must satisfy zero <= total <= one thousand, and completed must satisfy zero <= completed <= total. The function returns total minus completed for valid values and returns minus one for invalid values. It does not display text, allocate memory or change a file.

## Read the declaration

The header counts.h declares int BtbRemainingCount(int total, int completed);. The first int is the return type. The two named int parameters describe the values the function receives. A parameter is the local name used inside a function; an argument is the value supplied by a particular call.

The caller uses BtbRemainingCount(5, 2). During that call, total receives five and completed receives two. These integer values are passed by value: the function works with its own parameter objects. It cannot change a caller's separate int merely by assigning to one of these parameters.

## Keep declaration and implementation together

The source counts.c includes counts.h and defines the function body. Including its own public declaration lets the compiler check that the implementation agrees with it. functions.c includes the same header so it can call the function with the declared types.

The #ifndef, #define and #endif lines in the header form an include guard. They prevent its contents from being processed repeatedly in the same compilation when several files include it indirectly. You do not need to invent a new guard mechanism for this exercise; notice that the same guard name appears consistently.

## Return before unsafe work

The implementation checks all invalid ranges first. If any check rejects the arguments, return -1 ends that call before subtraction. Only valid small counts reach total - completed. This also makes extreme integer inputs safe to reject without performing potentially overflowing subtraction.

A valid remaining count is never negative. Reserving minus one for rejection therefore avoids confusing it with a valid result. This is a deliberately small interface. Other interfaces use a separate status and output object; read each contract rather than assuming every negative number means failure everywhere.

## Let the caller decide how to present it

functions.c stores the return value in remaining. If it is negative, the caller writes a message to stderr, the standard error stream, and returns a failure completion result. Standard error is separate from standard output so diagnostics can be collected separately from ordinary results.

With arguments five and two, remaining is three and the caller displays it on standard output. Keeping arithmetic separate from presentation allows a test to call the function directly without parsing a sentence. It also allows a future graphical interface to present the same result in its own way.

## Understand the link step

CMake builds counts.c into a small static library and links functions.c against it. A static library collects compiled object code for link-time reuse. The header supplies declarations; it does not itself provide the compiled function body.

If the linker reports an undefined reference to BtbRemainingCount, check whether counts.c was compiled and the required library was linked. Do not paste a second implementation into the caller merely to silence the error. The laboratory's CMake target records that dependency explicitly. Later Framework lessons use the same separation on a larger scale.

## Complete example

From the laboratory file labs/native/first-c-programs/functions.c.

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

## Try it step by step

1. Draw three boxes: header declaration, function implementation, caller.
2. Trace a valid call with 5 and 2 and a rejected call with 5 and 7.
3. Explain why minus one is distinguishable from every permitted result.
4. Find the library dependency in CMakeLists.txt without changing it.

## Check your understanding

Does including counts.h by itself supply the executable instructions for BtbRemainingCount?

**Explanation:** No. The header declares its interface. The implementation in counts.c must also be compiled and linked. Keeping both responsibilities explicit prevents the common missing-definition link error.

## Before you continue

You can state the contract, trace the caller's handling and explain why the implementation must be linked.

[Course contents](index.md) · [Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Repeat work without losing the stopping rule](05-repeat-with-a-boundary.md).

**Next:** [Test what you promised and understand failures](07-check-results-and-errors.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
