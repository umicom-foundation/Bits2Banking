# Keep several values in an array

Use a collection's element count and distinguish its last valid position from its size.

**Before you begin:** Read [Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md), or return to it for a refresher.

## Group values without inventing many names

An array is an ordered collection of elements of one type. In arrays.c, activities holds three int values: two, one and three. The declaration const int activities[] = {2, 1, 3}; lets the compiler count the initial values. The square brackets mark an array declaration; the braces group its initial contents.

Each element has an index, a whole-number position. C array indices begin at zero. The first element is activities[0], the second is activities[1] and the third is activities[2]. This is a numbering convention, not an indication that the first element contains zero. Here activities[0] contains two.

## Draw the positions and values separately

Draw three boxes. Above them write indices zero, one and two. Inside them write the values two, one and three. The array has three elements but no fourth box. activities[3] would try to access a position outside this array.

An out-of-bounds access is not a reliable way to ask for an empty value. In C it can have undefined behaviour, meaning the language does not specify a result for that operation. It may appear to work in one run and fail in another. Prevent the access rather than using a crash as your boundary detector.

## Count elements where the array is known

sizeof activities gives the size of the whole array in bytes. sizeof activities[0] gives the size of one element in bytes. Dividing the first by the second gives the element count. This works here because activities names the actual array in this scope.

A byte is the unit used by sizeof. Do not assume every C type uses one byte or that int uses the same number of bytes on every system. The division adapts to the actual element size. The type of sizeof's result is size_t, an unsigned integer type suitable for object sizes. The %zu output conversion matches size_t.

## Visit only valid positions

The loop begins at index zero. Its condition is index < count, so with count three it permits zero, one and two. It stops before index reaches three. This is why array loops often use < rather than <=.

total += activities[index] adds the current element to total and stores the result back in total. It is a shorter spelling of total = total + activities[index] for these ordinary variables. The three fixed small values give a final total of six. If the values could come from elsewhere, we would need a rule preventing overflow before each addition.

## Keep the array alive while using it

These array elements exist during the execution of their enclosing block in main. The program does not ask the heap allocator for additional storage, so there is no allocation to release. The array is const-qualified here, preventing changes through this declared object.

Lifetime and bounds are different requirements. An index can be within a former array's size while the array itself no longer exists. A valid access needs a live object and a valid position. The next lesson explains how to let another function read the array without transferring ownership.

## Predict the complete output

The expected line is Entries: 3, total: 6. The format string contains two conversions: %zu for count and %d for total. Arguments follow in that same order. A conversion mismatch can be a defect even when both values look like small numbers.

On paper, replace the three initial values with four, zero and two. The count stays three and the total stays six, although two element values changed. A test that checks only the total would not tell those arrays apart. Choose checks according to what the program promises.

## Complete example

From the laboratory file labs/native/first-c-programs/arrays.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/arrays.c
 *
 * PURPOSE:
 *   Visit a fixed array using its actual element count.
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
    const int activities[] = {2, 1, 3};
    const size_t count = sizeof activities / sizeof activities[0];
    int total = 0;
    for (size_t index = 0; index < count; ++index) {
        /* This introductory array contains only the three fixed small values
           above. The later borrowed-span function validates outside counts. */
        total += activities[index];
    }
    if (printf("Entries: %zu, total: %d\n", count, total) < 0 ||
        fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```

## Try it step by step

1. Draw the array with separate index labels and values.
2. Trace the loop's total after each iteration: two, then three, then six.
3. Explain why index equal to count must not enter the body.
4. Predict both count and total after appending a fourth fixed value of one in a working copy.

## Check your understanding

An array has three elements. Is index three its last valid element?

**Explanation:** No. Its valid indices are zero, one and two. Three is the element count and the first invalid index for access.

## Before you continue

You can distinguish the array's size, an element's index and the value stored there.

[Course contents](index.md) · [Words explained](../../courses/c-from-the-beginning/glossary.html) · [Practical lab guide](../../courses/c-from-the-beginning/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md).

**Next:** [Let a function read memory you still own](10-pointers-and-borrowing.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
