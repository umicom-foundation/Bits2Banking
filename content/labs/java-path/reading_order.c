/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/reading_order.c
 *
 * PURPOSE:
 *   Check that the C23 report places readings in the same order as the Java lesson.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Reading {
    int sequence;
    int value;
} Reading;

/* qsort asks which of its two readings belongs first. Compare their values
 * directly so the difference cannot overflow at opposite ends of the range. */
static int CompareReadings(const void *left, const void *right)
{
    const Reading *first = left;
    const Reading *second = right;

    if (first->value < second->value) return -1;
    if (first->value > second->value) return 1;

    /* Use sequence only when both readings have the same value. */
    if (first->sequence < second->sequence) return -1;
    if (first->sequence > second->sequence) return 1;
    return 0;
}

int main(void)
{
    const Reading input[] = {{11, 7}, {4, 3}, {2, 7}};
    Reading sorted[sizeof(input) / sizeof(input[0])];
    const size_t count = sizeof(input) / sizeof(input[0]);

    /* qsort rearranges its array. Sort a copy to retain the source order. */
    (void)memcpy(sorted, input, sizeof sorted);
    qsort(sorted, count, sizeof sorted[0], CompareReadings);

    (void)puts("Value Sequence");
    for (size_t index = 0; index < count; ++index) {
        (void)printf("%d %d\n", sorted[index].value, sorted[index].sequence);
    }
    return 0;
}
