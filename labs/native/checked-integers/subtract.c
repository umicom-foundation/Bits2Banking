/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/checked-integers/subtract.c
 *
 * PURPOSE:
 *   Distinguish the mathematical difference, its storage type and a debit rule.
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

static bool reserve_units(int balance, int debit, int *remaining)
{
    /* This practice account does not permit overdrafts or negative debits. */
    if (debit < 0 || balance < debit) return false;
    int candidate;
    if (ckd_sub(&candidate, balance, debit)) return false;
    *remaining = candidate;
    return true;
}

int main(void)
{
    /* Use the same mathematical inputs with two destination types. */
    int signed_difference;
    unsigned unsigned_difference;
    if (ckd_sub(&signed_difference, 3, 5) || signed_difference != -2) return 1;
    if (!ckd_sub(&unsigned_difference, 3, 5) || unsigned_difference != UINT_MAX - 1U) return 2;

    int remaining = 3;
    if (reserve_units(3, 5, &remaining) || remaining != 3) return 3;
    if (!reserve_units(3, 3, &remaining) || remaining != 0) return 4;
    if (reserve_units(3, -1, &remaining) || remaining != 0) return 5;
    puts("Signed difference: -2. The practice account refused the overdraft.");
    return 0;
}
