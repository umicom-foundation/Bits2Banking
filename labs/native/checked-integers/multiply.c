/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/checked-integers/multiply.c
 *
 * PURPOSE:
 *   Validate a synthetic block count before reporting its byte requirement.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdckdint.h>
#include <stdio.h>

static bool block_bytes(size_t blocks, size_t *bytes)
{
    /* The toy descriptor requires a nonempty run of 512-byte blocks. */
    if (blocks == 0U) return false;
    size_t candidate;
    if (ckd_mul(&candidate, blocks, (size_t)512)) return false;
    *bytes = candidate;
    return true;
}

int main(void)
{
    /* Review the boundary using pure arithmetic. No storage is allocated. */
    size_t bytes = 0U;
    if (!block_bytes(8U, &bytes) || bytes != 4096U) return 1;
    size_t largest_count = SIZE_MAX / (size_t)512;
    if (!block_bytes(largest_count, &bytes) || bytes != largest_count * (size_t)512) return 2;
    bytes = 4096U;
    if (block_bytes(largest_count + 1U, &bytes) || bytes != 4096U) return 3;
    if (block_bytes(0U, &bytes) || bytes != 4096U) return 4;
    puts("Eight blocks need 4096 bytes. The oversized count was refused.");
    return 0;
}
