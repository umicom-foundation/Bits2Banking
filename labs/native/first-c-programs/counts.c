/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/counts.c
 *
 * PURPOSE:
 *   Validate small count inputs before computing a remaining amount.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "counts.h"

int BtbRemainingCount(int total, int completed)
{
    /* A bound is part of this lesson's contract, not a general money or
       inventory policy. Rejection precedes subtraction, including for INT_MIN. */
    if (total < 0 || total > 1000 || completed < 0 || completed > total) {
        return -1;
    }
    return total - completed;
}
