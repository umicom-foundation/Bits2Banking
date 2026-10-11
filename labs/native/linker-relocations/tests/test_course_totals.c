/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: tests/test_course_totals.c
 * PURPOSE: Check overflow refusal and ABI compatibility across C/Assembly.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "btb/course_totals.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(test) do { if (!(test)) { \
    fprintf(stderr, "failed %s:%d: %s\n", __FILE__, __LINE__, #test); \
    return 1; \
} } while (0)
int main(void)
{
    uint32_t result = UINT32_C(0x12345678);
    CHECK(BtbCourseTotalsAdd(8U, 13U, &result) == 0);
    CHECK(result == 21U);
    CHECK(strcmp(BtbCourseTotalsUnit(), "lessons") == 0);
    CHECK(BtbCourseTotalsAdd(UINT32_MAX, 1U, &result) != 0);
    CHECK(result == 21U); /* Failure leaves previous output untouched. */
    CHECK(BtbCourseTotalsAdd(1U, 2U, 0) != 0);
    CHECK(BtbCourseTotalsAdd(UINT32_MAX, 0U, &result) == 0);
    CHECK(result == UINT32_MAX);
    for (uint32_t left = 0U; left < 128U; ++left) {
        for (uint32_t right = 0U; right < 128U; ++right) {
            CHECK(BtbCourseTotalsAdd(left, right, &result) == 0);
            CHECK(result == left + right);
        }
    }
    puts("[OK] 16384 C/Assembly combinations, overflow, and public API");
    return 0;
}
