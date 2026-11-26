/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/venue-shift-report/main.c
 *
 * PURPOSE:
 *   Read, validate and print a venue report with an optional new receipt file.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "venue_report.h"

#include <stdio.h>
#include "umicom/platform/input_file.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        fputs("Usage: btb-venue-report ABSOLUTE_CSV [NEW_ABSOLUTE_RECEIPT]\n", stderr);
        return 2;
    }

    /* Limit the allocation at the read boundary. The app owns this buffer. */
    unsigned char *bytes = NULL;
    size_t length = 0;
    UmiStatus status = UmiInputFileRead(argv[1], BTB_VENUE_INPUT_LIMIT, &bytes, &length);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "input: %s\n", umi_status_text(status));
        return 1;
    }

    BtbVenueReport report;
    size_t bad_record = 0;
    status = BtbVenueSummarise(bytes, length, &report, &bad_record);
    UmiInputFileFree(bytes);
    if (status != UMI_STATUS_OK) {
        if (bad_record) {
            fprintf(stderr, "record %zu: %s\n", bad_record, umi_status_text(status));
        } else {
            fprintf(stderr, "summary: %s\n", umi_status_text(status));
        }
        return 1;
    }

    char output[BTB_VENUE_REPORT_CAPACITY];
    status = BtbVenueRender(&report, output, sizeof output, &length);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "render: %s\n", umi_status_text(status));
        return 1;
    }

    /* The chosen receipt is opened only after validation and rendering. */
    if (argc == 3) {
        status = BtbVenuePublish(argv[2], output, length);
        if (status != UMI_STATUS_OK) {
            fprintf(stderr, "receipt: %s\n", umi_status_text(status));
            return 1;
        }
    }
    if (fwrite(output, 1, length, stdout) != length || fflush(stdout) != 0) {
        fputs("output: write failed\n", stderr);
        return 1;
    }
    return 0;
}
