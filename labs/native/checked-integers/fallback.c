/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/checked-integers/fallback.c
 *
 * PURPOSE:
 *   Demonstrate equivalent unsigned range guards without a C23 library header.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool size_product(size_t count, size_t width, size_t *bytes)
{
    /* Check the largest safe count before multiplying; skip division by zero. */
    if (width != 0U && count > SIZE_MAX / width) return false;
    *bytes = count * width;
    return true;
}

static bool size_sum(size_t left, size_t right, size_t *total)
{
    /* Subtraction is safe because right already has the destination type. */
    if (left > SIZE_MAX - right) return false;
    *total = left + right;
    return true;
}

int main(void)
{
    /* Check boundary acceptance, overflow refusal and the mathematical zero. */
    size_t result = 0U;
    if (!size_product(8U, 16U, &result) || result != 128U) return 1;
    if (!size_sum(result, 64U, &result) || result != 192U) return 2;
    if (size_product(SIZE_MAX, 2U, &result) || result != 192U) return 3;
    if (size_sum(SIZE_MAX, 1U, &result) || result != 192U) return 4;
    if (!size_product(SIZE_MAX, 0U, &result) || result != 0U) return 5;
    if (!size_sum(SIZE_MAX - 1U, 1U, &result) || result != SIZE_MAX) return 6;
    puts("The manual guards accepted 192 and kept it after overflow.");
    return 0;
}
