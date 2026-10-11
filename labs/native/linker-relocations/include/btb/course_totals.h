/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: include/btb/course_totals.h
 * PURPOSE: Public, checked lesson-count API used by the linker laboratory.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_COURSE_TOTALS_H
#define BTB_COURSE_TOTALS_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/** Add two counts. On overflow or a NULL output, return nonzero and leave
 * the existing output unchanged; no allocation, I/O or global mutation. */
int BtbCourseTotalsAdd(uint32_t existing, uint32_t added, uint32_t *outTotal);
/** Return the immutable name of the count unit; caller must not free it. */
const char *BtbCourseTotalsUnit(void);
#ifdef __cplusplus
}
#endif
#endif
