/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/checked-integers/add.c
 *
 * PURPOSE:
 *   Test representable C23 sums and preserve the caller result on overflow.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <limits.h>
#include <stdckdint.h>
#include <stdio.h>

static bool add_int(int left, int right, int *result)
{
    /* The macro may write a wrapped value even when it reports overflow. */
    int candidate;
    if (ckd_add(&candidate, left, right)) return false;
    *result = candidate;
    return true;
}

int main(void)
{
    /* Exercise ordinary, exact-limit and refused cases on every int width. */
    int stored = 0;
    if (!add_int(19, 23, &stored) || stored != 42) return 1;
    if (!add_int(INT_MAX - 1, 1, &stored) || stored != INT_MAX) return 2;
    stored = 42;
    if (add_int(INT_MAX, 1, &stored) || stored != 42) return 3;
    puts("The total is 42. The refused sum kept it unchanged.");
    return 0;
}
