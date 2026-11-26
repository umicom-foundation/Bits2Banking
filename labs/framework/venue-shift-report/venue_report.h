/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/venue-shift-report/venue_report.h
 *
 * PURPOSE:
 *   Expose the small venue report contract for the application and its tests.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_VENUE_REPORT_H
#define BTB_VENUE_REPORT_H

#include <stddef.h>
#include <stdint.h>
#include "umicom/base/sha256.h"
#include "umicom/base/status.h"

enum {
    BTB_VENUE_INPUT_LIMIT = 8192,
    BTB_VENUE_ROW_LIMIT = 128,
    BTB_VENUE_REPORT_CAPACITY = 192
};

typedef struct BtbVenueReport {
    size_t rows;
    uint64_t minutes;
    uint64_t visitors;
    char sha256[UMI_SHA256_HEX_CAPACITY];
} BtbVenueReport;

/* bad_record is zero for a whole-input error, otherwise a one-based CSV record.
 * The report changes only after the entire input has been checked.
 * Output objects must not overlap one another or the input.
 */
UmiStatus BtbVenueSummarise(const void *bytes, size_t length,
    BtbVenueReport *report, size_t *bad_record);

/* Render once into caller storage. A refused render leaves both outputs intact.
 * The caller supplies a report returned by BtbVenueSummarise.
 */
UmiStatus BtbVenueRender(const BtbVenueReport *report, char *output,
    size_t capacity, size_t *length);

/* Write to a new absolute path in a practice directory controlled by the caller.
 * An existing file is preserved. An I/O failure may leave a new partial file.
 */
UmiStatus BtbVenuePublish(const char *path, const char *output, size_t length);

#endif
