/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/sort_records.c
 *
 * PURPOSE:
 *   Observe ordering, duplicate preservation and sort idempotence.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "collections.h"
#include <stdio.h>

int main(void)
{
    BtbList sequence = {.values = {4, -2, 4, 0, -2}, .count = 5};
    const int expected[] = {-2, -2, 0, 4, 4};
    if (BtbListSort(&sequence) != BTB_OK || sequence.count != 5) return 1;
    for (size_t i = 0; i < sequence.count; ++i) {
        if (sequence.values[i] != expected[i]) return 2;
        printf("%zu: %d\n", i, sequence.values[i]);
    }
    /* Sorting twice must leave the observable sequence unchanged. This
       property complements the explicit expected sequence above. */
    if (BtbListSort(&sequence) != BTB_OK) return 3;
    for (size_t i = 0; i < sequence.count; ++i)
        if (sequence.values[i] != expected[i]) return 4;
    return 0;
}
