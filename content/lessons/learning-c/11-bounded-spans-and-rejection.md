# Connect borrowed memory to bounded system input

Trace rejection before access and understand why a length check cannot prove memory ownership.

**Before you begin:** Read [Let a function read memory you still own](10-pointers-and-borrowing.md), or return to it for a refresher.

## Combine a location with a length

A span is a description of consecutive elements using a starting location and a count. The borrowed-count function uses a span of int elements. Kernel input readers often use byte spans instead. Always identify the unit: three integers and three bytes can describe different amounts of storage.

BtbSumCounts accepts no more than sixteen elements and permits each value from zero through one thousand. These are explicit educational limits. They are not inferred from the pointer. The function returns minus one for a rejected count or element, and zero for an empty input.

## Reject an excessive length before touching memory

The first check asks whether count exceeds sixteen. If it does, the function returns immediately. This allows a test to pass a valid pointer to one element with an excessive logical count and confirm rejection without accessing additional elements.

The next check rejects a missing pointer when count is nonzero. Only after those checks does the loop read values[index]. The ordering is part of the safety argument. If the function read an element before checking an empty or invalid span, a later rejection would not undo the invalid access.

## Keep the arithmetic representable

Every accepted element is checked before addition. At most sixteen values of at most one thousand can produce a total of at most sixteen thousand. That fits the minimum positive range guaranteed for int. The fixed bound therefore makes every accepted addition representable in this exercise.

A larger general-purpose summation function would need a different overflow policy, often checking before each addition. Simply changing sixteen to a very large count would invalidate the current argument. When a limit changes, revisit the explanation, implementation and tests together.

## Understand what remains the caller's responsibility

A count of three passes the logical length rule, but the function still needs three actual live elements. Passing one real element with count three violates the contract. The function cannot safely probe beyond the allocation to discover its boundary.

Operating-system and Framework APIs often have the same distinction between logical validation and ownership. A parser can check a supplied byte count while relying on its caller to provide that many accessible bytes. The source-reader must establish those caller conditions before invoking the parser.

## Read the rejection tests

test_borrowed_counts.c checks an empty input, a missing nonempty input, a valid prefix, the maximum accepted total, invalid values and excessive lengths. It also calls the function again after rejected inputs to check that it has not retained state that changes the next answer.

The tests use valid objects and avoid inventing invalid pointer values. For the count-above-sixteen case, the expected early rejection means the single real element need not be read. This is a test of ordering, not permission to violate the contract for an accepted length.

## Return to the OS and Kernel examples

You can now read the bounded-input lesson with three separate questions: how much memory is available, what representation is accepted and who owns the storage during the call? A string adds an ending-marker convention; a span supplies an explicit length. Neither guarantees that text is valid in a chosen encoding.

Use the linked learning map to return to the existing borrowed-memory chapter and the Kernel byte-span lab. Read their contracts before compiling. The hosted sum example does not establish firmware validity or Kernel boot behaviour. It gives you a small, explainable model for the checks you will encounter there.

## Complete example

From the laboratory file labs/native/first-c-programs/borrowed_counts.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/borrowed_counts.c
 *
 * PURPOSE:
 *   Validate bounded borrowed counts before returning a representable total.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "borrowed_counts.h"

int BtbSumCounts(const int *values, size_t count)
{
    /* The count bound is checked before accessing any element. This validates
       the logical length, not the physical allocation: the caller supplies a
       valid live span. Sixteen values of at most 1000 sum to at most 16000,
       within the minimum range guaranteed for int. */
    if (count > 16U || (count != 0U && values == NULL)) {
        return -1;
    }
    int total = 0;
    for (size_t index = 0; index < count; ++index) {
        if (values[index] < 0 || values[index] > 1000) {
            return -1;
        }
        total += values[index];
    }
    return total;
}
```

## Try it step by step

1. Trace count zero with NULL and explain why no access occurs.
2. Trace count seventeen with a pointer to one real int and identify the rejecting condition.
3. Calculate the largest accepted total from the two stated limits.
4. Explain why increasing a limit requires reviewing arithmetic and tests, not only editing one number.

## Check your understanding

The function accepts counts up to sixteen. Is a pointer to one element with count three therefore valid?

**Explanation:** No. The policy limit and the actual storage extent are separate. The caller must provide at least three live int objects for an accepted count of three.

## Before you continue

You can separate policy limits, storage extent, lifetime and arithmetic bounds before reading a system parser.

[Course contents](index.md) · [Words explained](../../courses/c-from-the-beginning/glossary.html) · [Practical lab guide](../../courses/c-from-the-beginning/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Let a function read memory you still own](10-pointers-and-borrowing.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
