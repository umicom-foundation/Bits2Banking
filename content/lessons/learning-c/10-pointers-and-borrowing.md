# Let a function read memory you still own

Explain what a pointer supplies, what it does not supply and how a caller keeps borrowed storage valid.

**Before you begin:** Read [Keep several values in an array](09-arrays-and-valid-positions.md), or return to it for a refresher.

## Pass access without copying every element

The borrowing example calls BtbSumCounts(activities, count). In this expression the array name is converted to a pointer to its first element. A pointer value designates a location through which code can access an object under the language's rules.

The function also receives count separately. The pointer does not automatically carry the array's element count, ownership, permissions or remaining lifetime. Treating a pointer as if it contained all that information is a common source of defects. The interface must state those requirements.

## Read the parameter declaration

The parameter const int *values means that values is a pointer through which the function reads int elements without modifying them. The asterisk marks a pointer declarator here. const applies to the pointed-to integers through this access path; it does not make all memory in the process immutable.

The parameter size_t count gives the number of elements available for this call. values[index] reads an element at a position relative to the first one. The function's contract requires at least count live int objects when count is nonzero. A pointer to a shorter array does not become safe merely because the supplied count is small enough for the function's policy.

## Make ownership explicit

The caller owns the array. Borrowing means temporarily allowing the function to access it while the caller keeps it alive. BtbSumCounts does not retain the pointer after returning, does not allocate a replacement and does not free the caller's storage.

Because the call is synchronous, it finishes before main continues to the next statement. The local array remains alive during that call. An asynchronous operation that continues later would need a different lifetime agreement. Never return a pointer to a local array whose lifetime ends when the function returns.

## Distinguish empty from invalid

NULL is a null pointer constant representing the absence of a pointer to an object in this context. The contract permits values equal to NULL only when count is zero. An empty collection has total zero and requires no element access.

A null pointer with count one is rejected. A non-null pointer is not automatically safe: it might refer to an object that has expired or contain fewer elements than claimed. Portable C cannot generally inspect an arbitrary pointer to discover the allocation's size. The caller remains responsible for supplying valid storage.

## Do not use sizeof on a pointer to recover length

Inside BtbSumCounts, sizeof values would describe the pointer object, not the caller's array. Dividing it by sizeof values[0] would not discover how many elements the caller supplied. That is why the interface receives count and why the caller calculates the count while the actual array type is known.

This is also why the words array and pointer are related but not interchangeable. The array is a collection of objects. The pointer is a value used to access an object. Some expressions convert an array name to a pointer, but that conversion does not transport the whole array's type and extent.

## Read the result without changing the caller's data

The function returns the total or minus one for rejection. The caller checks that result before formatting it. With the three values two, one and three, the expected line is Borrowed total: 6.

The contract test keeps a copy of the original element bytes and checks they remain unchanged after calls. This supports the specific read-only promise for those cases. It does not prove every possible caller supplied valid memory, so the contract and caller review still matter.

## Complete example

From the laboratory file labs/native/first-c-programs/borrowing.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/borrowing.c
 *
 * PURPOSE:
 *   Call a bounded function while keeping ownership of an array.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "borrowed_counts.h"

#include <stdio.h>

int main(void)
{
    const int activities[] = {2, 1, 3};
    const size_t count = sizeof activities / sizeof activities[0];
    const int total = BtbSumCounts(activities, count);
    if (total < 0) {
        (void)fputs("The activity counts were rejected.\n", stderr);
        return 1;
    }
    if (printf("Borrowed total: %d\n", total) < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```

## Try it step by step

1. Draw the caller's three boxes and a separate arrow labelled values pointing to the first.
2. Write count beside the arrow as a separate piece of information.
3. Cross out the arrow after the call returns; leave the caller's boxes unchanged.
4. Explain why a three-element array cannot safely be passed with count four even though four is below sixteen.

## Check your understanding

Can the function discover that an arbitrary pointer refers to only three elements by evaluating sizeof values?

**Explanation:** No. values is a pointer parameter; sizeof values measures that pointer object. The caller must provide the correct element count and keep the storage valid.

## Before you continue

You can state the caller's lifetime and length responsibilities and the function's read-only promise.

[Course contents](index.md) · [Words explained](../../courses/c-from-the-beginning/glossary.html) · [Practical lab guide](../../courses/c-from-the-beginning/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Keep several values in an array](09-arrays-and-valid-positions.md).

**Next:** [Connect borrowed memory to bounded system input](11-bounded-spans-and-rejection.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
