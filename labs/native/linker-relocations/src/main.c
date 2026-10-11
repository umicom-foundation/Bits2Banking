/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: src/main.c
 * PURPOSE: Application composition that consumes an installed-style C API.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "btb/course_totals.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t lessons = 0U;
    if (BtbCourseTotalsAdd(8U, 13U, &lessons) != 0)
        return 1;
    if (printf("Bits2Banking learning path: %" PRIu32 " %s\n",
               lessons, BtbCourseTotalsUnit()) < 0)
        return 1;
    return 0;
}
