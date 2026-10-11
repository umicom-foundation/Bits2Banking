/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/assembly-functions/main.c
 * PURPOSE: Compare one unsigned addition contract across C23 and Assembly.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* The Assembly routine uses the platform's documented argument registers.
 * It returns the low 32 bits. Unsigned C addition has the same wraparound. */
extern uint32_t AddTwoAssembly(uint32_t left, uint32_t right);

static uint32_t AddTwoC(uint32_t left, uint32_t right)
{
    return left + right;
}

int main(void)
{
    static const uint32_t values[] = {
        0U, 1U, 2U, 7U, 25U, 1024U, UINT32_MAX,
        UINT32_MAX - 1U, UINT32_C(0x80000000), UINT32_C(0x7fffffff)
    };
    size_t checked = 0U;
    for (size_t i = 0U; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        for (size_t j = 0U; j < sizeof(values) / sizeof(values[0]); ++j)
        {
            uint32_t left = values[i], right = values[j];
            uint32_t actual = AddTwoAssembly(left, right);
            uint32_t expected = AddTwoC(left, right);
            if (actual != expected)
            {
                fprintf(stderr, "Mismatch for %" PRIu32 " + %" PRIu32
                        ": Assembly=%" PRIu32 ", C=%" PRIu32 "\n",
                        left, right, actual, expected);
                return EXIT_FAILURE;
            }
            ++checked;
        }
    }
    printf("Payment IDs 27 and 15 combine to %" PRIu32 ".\n",
           AddTwoAssembly(27U, 15U));
    printf("C and Assembly agree on %zu value pairs.\n", checked);
    return EXIT_SUCCESS;
}
