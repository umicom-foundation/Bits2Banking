/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/checked-integers/record.c
 *
 * PURPOSE:
 *   Stage both size calculations before publishing a record plan.
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

typedef struct RecordSize {
    size_t body;
    size_t total;
} RecordSize;

static bool plan_record(size_t items, size_t header, RecordSize *sizes)
{
    /* Either stage may fail. Copy the complete plan after both succeed. */
    RecordSize candidate;
    if (ckd_mul(&candidate.body, items, (size_t)16)) return false;
    if (ckd_add(&candidate.total, candidate.body, header)) return false;
    *sizes = candidate;
    return true;
}

int main(void)
{
    /* Keep sentinels for both fields so either partial write is visible. */
    RecordSize sizes = {0};
    if (!plan_record(8U, 64U, &sizes) || sizes.body != 128U || sizes.total != 192U) return 1;
    size_t largest_count = SIZE_MAX / (size_t)16;
    if (plan_record(largest_count + 1U, 0U, &sizes) || sizes.body != 128U || sizes.total != 192U) return 2;
    size_t too_much_header = SIZE_MAX % (size_t)16 + 1U;
    if (plan_record(largest_count, too_much_header, &sizes) || sizes.body != 128U || sizes.total != 192U) return 3;
    puts("Body: 128 bytes. Total: 192 bytes. Both refusals kept the original plan.");
    return 0;
}
