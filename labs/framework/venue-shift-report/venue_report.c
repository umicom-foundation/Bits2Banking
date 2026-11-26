/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/venue-shift-report/venue_report.c
 *
 * PURPOSE:
 *   Check every venue row before publishing totals, and render the checked report.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "venue_report.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "umicom/base/ascii_number.h"
#include "umicom/base/csv_reader.h"

static UmiStatus check_row(const UmiCsvReadRow *row, uint64_t *minutes, uint64_t *visitors)
{
    /* CSV field ownership stays with the reader. Convert before advancing it. */
    if (row->count != 3 || row->lengths[0] == 0 || row->lengths[0] > 40) {
        return UMI_STATUS_PARSE_ERROR;
    }
    UmiStatus status = umi_ascii_uint64_parse(row->fields[1], row->lengths[1], minutes);
    if (status == UMI_STATUS_OK) {
        status = umi_ascii_uint64_parse(row->fields[2], row->lengths[2], visitors);
    }
    if (status == UMI_STATUS_OK && (*minutes == 0 || *minutes > 1440 || *visitors > 10000)) {
        return UMI_STATUS_CAPACITY_EXCEEDED;
    }
    return status;
}

UmiStatus BtbVenueSummarise(const void *bytes, size_t length,
    BtbVenueReport *report, size_t *bad_record)
{
    if (!report || !bad_record || (!bytes && length)) {
        return UMI_STATUS_INVALID_ARGUMENT;
    }
    *bad_record = 0;
    if (length > BTB_VENUE_INPUT_LIMIT) {
        return UMI_STATUS_CAPACITY_EXCEEDED;
    }

    UmiCsvReader *reader = NULL;
    UmiStatus status = UmiCsvReaderCreate(bytes, length, &reader);
    if (status != UMI_STATUS_OK) {
        return status;
    }

    /* Check the header first so a reordered numeric column cannot change meaning. */
    BtbVenueReport next = {0};
    UmiCsvReadRow row;
    status = UmiCsvReaderNext(reader, &row);
    if (status != UMI_STATUS_OK) {
        *bad_record = 1;
        if (status == UMI_STATUS_NOT_FOUND) {
            status = UMI_STATUS_PARSE_ERROR;
        }
    } else if (row.count != 3 || strcmp(row.fields[0], "room") ||
               strcmp(row.fields[1], "minutes") || strcmp(row.fields[2], "visitors")) {
        status = UMI_STATUS_PARSE_ERROR;
        *bad_record = 1;
    }

    /* Accumulate locally so a late failure cannot publish a partial total.
     * The row limit and per-row bounds also keep these sums inside uint64_t.
     */
    while (status == UMI_STATUS_OK) {
        status = UmiCsvReaderNext(reader, &row);
        if (status == UMI_STATUS_NOT_FOUND) {
            status = UMI_STATUS_OK;
            break;
        }
        if (status != UMI_STATUS_OK) {
            *bad_record = next.rows + 2;
            break;
        }
        uint64_t minutes = 0;
        uint64_t visitors = 0;
        status = next.rows == BTB_VENUE_ROW_LIMIT ? UMI_STATUS_CAPACITY_EXCEEDED :
            check_row(&row, &minutes, &visitors);
        if (status != UMI_STATUS_OK) {
            *bad_record = row.record;
            break;
        }
        ++next.rows;
        next.minutes += minutes;
        next.visitors += visitors;
    }
    UmiCsvReaderDestroy(reader);

    if (status == UMI_STATUS_OK) {
        status = UmiSha256Buffer(bytes, length, next.sha256);
    }
    if (status == UMI_STATUS_OK) {
        *report = next;
    }
    return status;
}

UmiStatus BtbVenueRender(const BtbVenueReport *report, char *output,
    size_t capacity, size_t *length)
{
    if (!report || !output || !length) {
        return UMI_STATUS_INVALID_ARGUMENT;
    }

    /* Keep a complete representation in temporary storage before copying it. */
    char text[BTB_VENUE_REPORT_CAPACITY];
    int written = snprintf(text, sizeof text,
        "Rows: %zu\nMinutes: %" PRIu64 "\nVisitors: %" PRIu64 "\nSource SHA-256: %.64s\n",
        report->rows, report->minutes, report->visitors, report->sha256);
    if (written < 0) {
        return UMI_STATUS_IO_ERROR;
    }
    if ((size_t)written >= sizeof text || (size_t)written >= capacity) {
        return UMI_STATUS_CAPACITY_EXCEEDED;
    }
    memcpy(output, text, (size_t)written + 1);
    *length = (size_t)written;
    return UMI_STATUS_OK;
}
