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
