/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: src/course_totals.c
 * PURPOSE: Checked C23 contract around one replaceable Assembly leaf function.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "btb/course_totals.h"
#include <stdint.h>

/* External Assembly leaf symbol, resolved by the linker when the final client
 * executable is produced. Its ABI is one platform-specific build decision. */
extern uint32_t BtbAssemblyAddU32(uint32_t left, uint32_t right);

/* Static gives internal linkage. This helper is private to this translation
 * unit and is not a public library symbol. */
static int BtbCanAdd(uint32_t left, uint32_t right)
{
    return right <= UINT32_MAX - left;
}

int BtbCourseTotalsAdd(uint32_t existing, uint32_t added, uint32_t *outTotal)
{
    if (outTotal == 0 || !BtbCanAdd(existing, added))
        return 1;
    /* Only after validation do we call Assembly and publish the result. */
    uint32_t calculated = BtbAssemblyAddU32(existing, added);
    *outTotal = calculated;
    return 0;
}

const char *BtbCourseTotalsUnit(void)
{
    return "lessons";
}
