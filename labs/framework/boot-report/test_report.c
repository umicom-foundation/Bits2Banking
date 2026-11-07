/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/boot-report/test_report.c
 *
 * PURPOSE:
 *   Check boot observation admission and preserve previous state on malformed input.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/platform/boot_report.h"
#include <stdio.h>
#include <string.h>

static const char ready[] =
    "UMICOM_BOOT_REPORT 1\nmode=normal\nstate=ready\nplanned=2\n"
    "completed=2\nreason=none\n"
    "source=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef\n";
static const char recovery[] =
    "UMICOM_BOOT_REPORT 1\nmode=normal\nstate=recovery\nplanned=2\n"
    "completed=1\nreason=service-exit\n"
    "source=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef\n";

static int Unchanged(const UmiBootReport *a, const UmiBootReport *b)
{
    /* Compare fields, not padding bytes that a C structure may contain. */
    return a->mode == b->mode && a->state == b->state &&
           a->planned == b->planned && a->completed == b->completed &&
           strcmp(a->reason, b->reason) == 0 && strcmp(a->sourceId, b->sourceId) == 0;
}

int main(void)
{
    UmiBootReport report = {0};
    if (UmiBootReportParse(ready, sizeof ready - 1U, &report) != UMI_STATUS_OK ||
        report.state != UMI_BOOT_REPORT_READY || report.completed != 2U) return 1;
    if (UmiBootReportParse(recovery, sizeof recovery - 1U, &report) != UMI_STATUS_OK ||
        report.state != UMI_BOOT_REPORT_RECOVERY || strcmp(report.reason, "service-exit")) return 2;
    UmiBootReport previous = report;
    char inconsistent[sizeof ready];
    memcpy(inconsistent, ready, sizeof ready);
    char *completed = strstr(inconsistent, "completed=2");
    if (!completed) return 3;
    completed[strlen("completed=")] = '1';
    if (UmiBootReportParse(inconsistent, sizeof inconsistent - 1U, &report) == UMI_STATUS_OK ||
        !Unchanged(&report, &previous)) return 4;
    /* Excluding the last LF tests a truncated record, not a missing C terminator. */
    if (UmiBootReportParse(ready, sizeof ready - 2U, &report) == UMI_STATUS_OK ||
        !Unchanged(&report, &previous)) return 5;
    if (UmiBootReportParse(NULL, 0U, &report) == UMI_STATUS_OK ||
        !Unchanged(&report, &previous)) return 6;
    if (UmiBootReportParse(ready, sizeof ready - 1U, NULL) == UMI_STATUS_OK) return 7;
    char duplicate[UMI_BOOT_REPORT_MAX_BYTES];
    int count = snprintf(duplicate, sizeof duplicate, "%smode=normal\n", ready);
    if (count < 0 || (size_t)count >= sizeof duplicate) return 8;
    if (UmiBootReportParse(duplicate, (size_t)count, &report) == UMI_STATUS_OK ||
        !Unchanged(&report, &previous)) return 9;
    puts("Boot report contract cases completed.");
    return 0;
}
