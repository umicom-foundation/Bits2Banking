/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/boot-report-comparison/capture_identity.c
 *
 * PURPOSE:
 *   Compare parsed observations while checking the identity of their exact file bytes.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/platform/boot_report_file.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        fputs("Supply two absolute fixture paths.\n", stderr);
        return 1;
    }

    /* Use the shared reader so each digest describes the bytes it really parsed. */
    UmiBootReportCapture earlier = {0};
    UmiBootReportCapture reordered = {0};
    if (UmiBootReportInspectFile(argv[1], NULL, NULL, &earlier) != UMI_STATUS_OK ||
        UmiBootReportInspectFile(argv[2], NULL, NULL, &reordered) != UMI_STATUS_OK) {
        fputs("Could not read both capture fixtures.\n", stderr);
        return 1;
    }

    /* Ask Framework to compare fields. Comparing structs as bytes would include
     * padding, while the digest also includes layout details such as field order. */
    uint32_t changes = UINT32_MAX;
    if (UmiBootReportCompare(&earlier.report, &reordered.report, &changes) != UMI_STATUS_OK ||
        changes != 0U || earlier.byteCount != reordered.byteCount ||
        strcmp(earlier.captureSha256, reordered.captureSha256) == 0) {
        fputs("Expected identical observations in two different byte sequences.\n", stderr);
        return 1;
    }

    /* Keep a previously accepted snapshot visible when an exact-byte pin fails.
     * A successful pin on the original fixture makes the refusal meaningful. */
    UmiBootReportCapture accepted = {0};
    if (UmiBootReportInspectFile(argv[1], NULL, earlier.captureSha256, &accepted) != UMI_STATUS_OK)
        return 1;
    if (UmiBootReportInspectFile(argv[2], NULL, earlier.captureSha256, &accepted) != UMI_STATUS_INVALID_STATE ||
        accepted.byteCount != earlier.byteCount ||
        strcmp(accepted.captureSha256, earlier.captureSha256) != 0 ||
        UmiBootReportCompare(&accepted.report, &earlier.report, &changes) != UMI_STATUS_OK || changes != 0U) {
        fputs("Expected a digest refusal with the previous snapshot preserved.\n", stderr);
        return 1;
    }

    puts("Parsed fields and file lengths match.");
    puts("Capture digests differ.");
    puts("The original digest refuses the reordered capture.");
    return ferror(stdout) || fflush(stdout) ? 1 : 0;
}
