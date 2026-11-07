/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/boot-report/main.c
 *
 * PURPOSE:
 *   Inspect an explicitly selected OS boot report through the shared Framework reader.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/platform/boot_report_file.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("Usage: btb-boot-report ABSOLUTE_REPORT_PATH [EXPECTED_SOURCE_SHA256]");
        return 0;
    }
    if (argc != 2 && argc != 3) {
        fputs("Select one absolute report path. Use --help for the command form.\n", stderr);
        return 2;
    }
    /* Framework owns file admission, bounds, parsing and source comparison.
     * This client presents an observation; it never starts or repairs a guest. */
    UmiBootReport report;
    UmiStatus status = UmiBootReportLoad(argv[1], argc == 3 ? argv[2] : NULL, &report);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Report rejected (status %d). No state was accepted.\n", (int)status);
        return 1;
    }
    printf("Observed state: %s\nCompleted checks: %u/%u\nReason: %s\nSource: %s\n",
           UmiBootReportStateText(report.state), (unsigned)report.completed,
           (unsigned)report.planned, report.reason, report.sourceId);
    puts("This is a recorded boot-phase observation, not current machine health.");
    return fflush(stdout) == 0 ? 0 : 1;
}
