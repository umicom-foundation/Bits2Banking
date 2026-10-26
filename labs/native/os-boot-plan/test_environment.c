/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/os-boot-plan/test_environment.c
 *
 * PURPOSE:
 *   Explore the difference between missing observations and a rejected guest service environment.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "guest_environment.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    UmiOsGuestEnvironment e = {0};
    e.observed = UMI_OS_GUEST_ALL;
    e.uid = e.effectiveUid = e.gid = e.effectiveGid = 1000;
    e.noNewPrivileges = 1;
    e.fileLimit = e.fileHardLimit = 65536;
    e.descriptorLimit = e.descriptorHardLimit = 32;
    e.workUid = e.workGid = 1000;
    e.workMode = 0700;
    e.workDirectory = e.workingDirectoryMatches = true;
    e.proc = e.sys = e.run = e.tmp = (UmiOsGuestMount){true, true};
    UmiOsGuestProblem expected;
    if (strcmp(argv[1], "complete") == 0) expected = UMI_OS_GUEST_OK;
    else if (strcmp(argv[1], "missing") == 0) {
        e.observed &= ~(uint32_t)UMI_OS_GUEST_GROUPS;
        expected = UMI_OS_GUEST_OBSERVATION;
    } else if (strcmp(argv[1], "group") == 0) {
        e.supplementaryGroups = 1; expected = UMI_OS_GUEST_EXTRA_GROUPS;
    } else if (strcmp(argv[1], "temporary-mount") == 0) {
        e.tmp.restricted = false; expected = UMI_OS_GUEST_UNSAFE_TMP;
    } else return 2;
    UmiOsGuestProblem actual = UmiOsGuestEnvironmentCheck(&e);
    if (actual != expected) {
        fprintf(stderr, "Expected %s; received %s.\n",
            UmiOsGuestProblemText(expected), UmiOsGuestProblemText(actual));
        return 1;
    }
    puts("Synthetic observation checked. No guest or host privileges were changed.");
    return 0;
}
