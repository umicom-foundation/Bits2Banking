/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/counts.h
 *
 * PURPOSE:
 *   Declare a small, explicit count contract for first programming exercises.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS2BANKING_FIRST_COUNTS_H
#define BITS2BANKING_FIRST_COUNTS_H

/* Accept 0 <= completed <= total <= 1000. Return total minus completed.
   Return -1 for any rejected input. There are no side effects or allocations. */
int BtbRemainingCount(int total, int completed);

#endif
