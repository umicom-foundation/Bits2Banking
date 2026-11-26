/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/checked-reference.c
 *
 * PURPOSE:
 *   Compare a counted-byte contract on the host with the Arm plan.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t SumCheckedBytes(const uint8_t *bytes, size_t count)
{
    /* Validate the same boundaries before touching any caller storage. */
    if (count > 4U || (count != 0U && bytes == NULL))
        return UINT32_MAX;

    uint32_t sum = 0U;
    for (size_t i = 0U; i < count; ++i)
        sum += bytes[i];
    return sum;
}

int main(void)
{
    /* Each row represents a separate read authority or byte boundary. */
    const uint8_t bytes[] = {0U, 8U, UINT8_MAX, 1U};
    if (SumCheckedBytes(NULL, 0U) != 0U ||
        SumCheckedBytes(NULL, 1U) != UINT32_MAX ||
        SumCheckedBytes(bytes, 5U) != UINT32_MAX ||
        SumCheckedBytes(bytes, 3U) != 263U ||
        SumCheckedBytes(bytes, 4U) != 264U)
        return 1;
    return puts("Five counted-byte contracts passed.") < 0 ? 1 : 0;
}
