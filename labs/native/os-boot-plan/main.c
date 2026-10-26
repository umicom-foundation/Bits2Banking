/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/os-boot-plan/main.c
 *
 * PURPOSE:
 *   Inspect a real Umicom OS service graph without starting any service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "boot.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Put the dependent service first deliberately. The parser owns ordering;
     * the demonstration only reads its accepted result and never launches it. */
    const char input[] =
        "UMICOM_OS_BOOT 1\nhostname=lesson\n"
        "service=display|/usr/libexec/umicom-display|storage|1000\n"
        "service=storage|/usr/libexec/umicom-storage|-|2000\n";
    UmiOsBootConfig plan;
    if (!UmiOsBootConfigParse(input, sizeof input - 1U, &plan)) return 1;
    printf("Host: %s\n", plan.hostname);
    for (size_t i = 0; i < plan.count; ++i)
        printf("%zu. %s\n", i + 1U, plan.services[plan.order[i]].id);
    puts("Inspection only: no service was executed.");
    return ferror(stdout) || fflush(stdout) ? 1 : 0;
}
