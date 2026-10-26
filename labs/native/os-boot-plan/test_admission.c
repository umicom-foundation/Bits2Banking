/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/os-boot-plan/test_admission.c
 *
 * PURPOSE:
 *   Explore how real OS startup policy keeps a failure visible during requested recovery.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "boot_admission.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    UmiOsBootInputs observed = {true, true, true, true, true, {false, false}, 2};
    const char *expected = "none";
    bool shouldStart = true;
    if (!strcmp(argv[1], "requested")) {
        observed.options.recovery = true;
        expected = "requested";
        shouldStart = false;
    } else if (!strcmp(argv[1], "hostname")) {
        observed.options.recovery = true;
        observed.hostnameApplied = false;
        expected = "configuration";
        shouldStart = false;
    } else if (strcmp(argv[1], "normal")) return 2;

    /* These are supplied observations, not host mount or hostname operations.
     * The lab links the policy used by PID1 without executing PID1 itself. */
    UmiOsBootDecision decision;
    if (!UmiOsBootDecide(&observed, &decision) ||
        strcmp(decision.reason, expected) ||
        decision.mayStartServices != shouldStart || decision.planned != 2) {
        fputs("The startup decision did not preserve the expected prerequisites.\n", stderr);
        return 1;
    }
    printf("mode=%s state=%s reason=%s services-allowed=%s\n",
        decision.mode, decision.state, decision.reason,
        decision.mayStartServices ? "yes" : "no");
    return 0;
}
