/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/boot-report-comparison/main.c
 *
 * PURPOSE:
 *   Compare captured boot observations through the canonical Framework parser and comparator.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/platform/boot_report.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
static const char EARLIER[] = "UMICOM_BOOT_REPORT 1\nmode=normal\nstate=starting\n"
    "planned=2\ncompleted=1\nreason=none\n"
    "source=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef\n";
static const char LATER[] = "UMICOM_BOOT_REPORT 1\nmode=normal\nstate=ready\n"
    "planned=2\ncompleted=2\nreason=none\n"
    "source=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef\n";
int main(void)
{
    UmiBootReport earlier, later;
    UmiStatus status = UmiBootReportParse(EARLIER, sizeof EARLIER - 1U, &earlier);
    if (status != UMI_STATUS_OK) return 1;
    status = UmiBootReportParse(LATER, sizeof LATER - 1U, &later);
    if (status != UMI_STATUS_OK) return 1;
    uint32_t changes = 0U;
    if (UmiBootReportCompare(&earlier, &later, &changes) != UMI_STATUS_OK) return 1;
    if (changes != (UMI_BOOT_REPORT_CHANGED_STATE | UMI_BOOT_REPORT_CHANGED_COMPLETED)) return 1;
    printf("state: %s -> %s\ncompleted: %" PRIu32 " -> %" PRIu32 "\n",
        UmiBootReportStateText(earlier.state), UmiBootReportStateText(later.state),
        earlier.completed, later.completed);
    /* Simulate malformed caller-owned data without reading beyond its array.
     * Refusal must leave the last successfully published mask unchanged. */
    memset(later.reason, 'x', sizeof later.reason);
    uint32_t saved = changes;
    if (UmiBootReportCompare(&earlier, &later, &changes) != UMI_STATUS_INVALID_ARGUMENT ||
        changes != saved) return 1;
    puts("Malformed report refused; previous comparison preserved.");
    puts("Captured observations do not establish current machine health.");
    return ferror(stdout) || fflush(stdout) ? 1 : 0;
}
