/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: read_window.c
 *
 * PURPOSE:
 *   Define and check the original bounded read-window teaching contract.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "read_window.h"
/* Subtract only after proving position is in range. This avoids overflow in
 * position + requested, including deliberately oversized caller requests. */
int umi_learning_read_window(uint64_t position, size_t requested, size_t length,
    size_t *offset, size_t *count)
{
    if (!offset || !count || offset == count) return 0;
    if (position >= length) {
        *offset = length;
        *count = 0;
        return 1;
    }
    const size_t start = (size_t)position;
    const size_t remaining = length - start;
    *offset = start;
    *count = requested < remaining ? requested : remaining;
    return 1;
}
