/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/venue-shift-report/test_venue_report.c
 *
 * PURPOSE:
 *   Verify bounded totals, failed-input ownership and complete rendering.
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
#include <string.h>

/* Keep the checks live even when the consumer is built with NDEBUG. */
#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "check failed at line %d: %s\n", __LINE__, #condition); \
        return 1; \
    } \
} while (0)

static const char good_csv[] =
    "room,minutes,visitors\n\"Gallery, east\",35,12\nWorkshop,25,0\nMain Hall,40,48\n";

static int check_good(void)
{
    BtbVenueReport report;
    size_t bad_record = 41;
    char expected[UMI_SHA256_HEX_CAPACITY];
    CHECK(BtbVenueSummarise(good_csv, sizeof good_csv - 1, &report, &bad_record) == UMI_STATUS_OK);
    CHECK(bad_record == 0 && report.rows == 3 && report.minutes == 100 && report.visitors == 60);
    CHECK(UmiSha256Buffer(good_csv, sizeof good_csv - 1, expected) == UMI_STATUS_OK);
    CHECK(strcmp(report.sha256, expected) == 0);
    return 0;
}

static int check_refused(const char *input, size_t length, size_t record)
{
    /* Seed meaningful values so a late, partial assignment is visible. */
    BtbVenueReport report = {.rows = 7, .minutes = 80, .visitors = 41, .sha256 = "previous"};
    size_t bad_record = 123;
    CHECK(BtbVenueSummarise(input, length, &report, &bad_record) != UMI_STATUS_OK);
    CHECK(bad_record == record);
    CHECK(report.rows == 7 && report.minutes == 80 && report.visitors == 41);
    CHECK(strcmp(report.sha256, "previous") == 0);
    return 0;
}

static int check_empty(void)
{
    const char header[] = "room,minutes,visitors\r\n";
    BtbVenueReport report = {.rows = 99};
    size_t bad_record = 99;
    CHECK(BtbVenueSummarise(header, sizeof header - 1, &report, &bad_record) == UMI_STATUS_OK);
    CHECK(report.rows == 0 && report.minutes == 0 && report.visitors == 0 && bad_record == 0);
    return check_refused("", 0, 1);
}

static int check_limit(void)
{
    const char row[] = "A,1,0\n";
    char input[BTB_VENUE_INPUT_LIMIT + 1] = "room,minutes,visitors\n";
    size_t bytes = strlen(input);
    for (size_t i = 0; i < BTB_VENUE_ROW_LIMIT; ++i) {
        memcpy(input + bytes, row, sizeof row - 1);
        bytes += sizeof row - 1;
    }
    BtbVenueReport report;
    size_t bad_record = 0;
    CHECK(BtbVenueSummarise(input, bytes, &report, &bad_record) == UMI_STATUS_OK);
    CHECK(report.rows == BTB_VENUE_ROW_LIMIT && report.minutes == BTB_VENUE_ROW_LIMIT);
    memcpy(input + bytes, row, sizeof row - 1);
    CHECK(check_refused(input, bytes + sizeof row - 1, BTB_VENUE_ROW_LIMIT + 2) == 0);
    return check_refused(input, sizeof input, 0);
}

static int check_render(void)
{
    BtbVenueReport report;
    size_t bad_record = 0;
    CHECK(BtbVenueSummarise(good_csv, sizeof good_csv - 1, &report, &bad_record) == UMI_STATUS_OK);

    char small[4] = "old";
    size_t length = 77;
    CHECK(BtbVenueRender(&report, small, sizeof small, &length) == UMI_STATUS_CAPACITY_EXCEEDED);
    CHECK(strcmp(small, "old") == 0 && length == 77);

    char output[BTB_VENUE_REPORT_CAPACITY];
    CHECK(BtbVenueRender(&report, output, sizeof output, &length) == UMI_STATUS_OK);
    CHECK(strlen(output) == length && strstr(output, "Visitors: 60\n") != NULL);
    CHECK(strstr(output, report.sha256) != NULL);

    char exact[BTB_VENUE_REPORT_CAPACITY];
    size_t size = 0;
    CHECK(BtbVenueRender(&report, exact, length + 1, &size) == UMI_STATUS_OK);
    CHECK(size == length && strcmp(exact, output) == 0);
    return 0;
}

int main(int argc, char *argv[])
{
    static const char wrong_header[] = "room,visitors,minutes\nA,9,3\n";
    static const char wrong_number[] = "room,minutes,visitors\nA,9,3\nB,9,4 extra\n";
    static const char wrong_range[] = "room,minutes,visitors\nA,1441,1\n";
    static const char unclosed[] = "room,minutes,visitors\nA,9,3\n\"B,9,1\n";
    if (argc != 2) {
        return 2;
    }
    if (!strcmp(argv[1], "good")) {
        return check_good();
    }
    if (!strcmp(argv[1], "header")) {
        return check_refused(wrong_header, sizeof wrong_header - 1, 1);
    }
    if (!strcmp(argv[1], "number")) {
        return check_refused(wrong_number, sizeof wrong_number - 1, 3);
    }
    if (!strcmp(argv[1], "range")) {
        return check_refused(wrong_range, sizeof wrong_range - 1, 2);
    }
    if (!strcmp(argv[1], "malformed")) {
        return check_refused(unclosed, sizeof unclosed - 1, 3);
    }
    if (!strcmp(argv[1], "empty")) {
        return check_empty();
    }
    if (!strcmp(argv[1], "limit")) {
        return check_limit();
    }
    if (!strcmp(argv[1], "render")) {
        return check_render();
    }
    fprintf(stderr, "unknown case: %s\n", argv[1]);
    return 2;
}
