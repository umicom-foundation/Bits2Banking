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
