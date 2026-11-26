/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/record-layout.c
 *
 * PURPOSE:
 *   Check the native Arm record layout at compile time.
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

typedef struct BtbPracticeRecord {
    uint8_t present;
    uint32_t units;
} BtbPracticeRecord;

/* These declarations describe a native record for this exercise. */
static_assert(offsetof(BtbPracticeRecord, present) == 0U);
static_assert(offsetof(BtbPracticeRecord, units) == 4U);
static_assert(sizeof(BtbPracticeRecord) == 8U);

extern uint32_t btb_record_units(const BtbPracticeRecord *record);

uint32_t btb_record_layout_probe(const BtbPracticeRecord *record)
{
    /* Ask the linker to find the Assembly owner of the matching layout. */
    return btb_record_units(record);
}
