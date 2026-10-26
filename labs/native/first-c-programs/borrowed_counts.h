/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/borrowed_counts.h
 *
 * PURPOSE:
 *   Declare bounded read-only borrowing of an integer array.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS2BANKING_BORROWED_COUNTS_H
#define BITS2BANKING_BORROWED_COUNTS_H

#include <stddef.h>

/* Accept at most 16 counts, each in 0..1000. Return their sum, or -1 for a
   rejected input. A zero-length input returns zero and may use NULL.
   For a nonempty input, values must point to at least count live int objects.
   No pointer is retained and no element is written. The caller owns storage. */
int BtbSumCounts(const int *values, size_t count);

#endif
