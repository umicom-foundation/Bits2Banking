/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/riscv-sequences/check.c
 *
 * PURPOSE:
 *   Check RV64 examples against independent C expectations.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "sequences.h"
#include <limits.h>
#include <stdio.h>
_Static_assert(sizeof(size_t) == 8, "This lab targets RV64 with LP64.");
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "%d: %s\n", __LINE__, #x); return 1; } } while (0)

static uint64_t Rotate(uint64_t value, unsigned distance)
{
    distance &= 63U;
    /* C requires a separate zero case: shifting by the type width is invalid. */
    return distance == 0 ? value : (value << distance) | (value >> (64U - distance));
}
static uint64_t Parity(uint64_t value)
{
    uint64_t count = 0;
    for (unsigned i = 0; i < 64U; ++i) count += (value >> i) & UINT64_C(1);
    return count % 2U;
}
int main(void)
{
    const uint64_t data[] = {1, 2, 3, UINT64_MAX};
    REQUIRE(BtbSum64(NULL, 0) == 0);
    REQUIRE(BtbSum64(data, 1) == 1);
    REQUIRE(BtbSum64(data, 4) == 5);
    REQUIRE(BtbSumAndBias64(data, 4, 7) == 12);
    REQUIRE(BtbSumAndBias64(NULL, 0, UINT64_MAX) == UINT64_MAX);
    REQUIRE(BtbMinSigned64(-1, 1) == -1);
    REQUIRE(BtbMinSigned64(INT64_MIN, INT64_MAX) == INT64_MIN);
    REQUIRE(BtbMinSigned64(4, -9) == -9);
    REQUIRE(BtbMinUnsigned64(UINT64_MAX, 1) == 1);
    REQUIRE(BtbMinUnsigned64(1, UINT64_MAX) == 1);
    const uint64_t words[] = {0, 1, UINT64_MAX, UINT64_C(0x8000000000000000), UINT64_C(0x1020304050607080)};
    for (size_t i = 0; i < sizeof(words) / sizeof(words[0]); ++i) {
        REQUIRE(BtbParity64(words[i]) == Parity(words[i]));
        for (unsigned distance = 0; distance <= 129U; ++distance)
            REQUIRE(BtbRotateLeft64(words[i], distance) == Rotate(words[i], distance));
    }
    puts("RISC-V sequence checks passed");
    return 0;
}
