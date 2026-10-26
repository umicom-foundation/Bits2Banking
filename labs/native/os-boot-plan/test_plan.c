/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/os-boot-plan/test_plan.c
 *
 * PURPOSE:
 *   Demonstrate dependency ordering, parser rollback and recovery controls.
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
#define CHECK(e) do { if (!(e)) { fprintf(stderr, "check %d: %s\n", __LINE__, #e); return 1; } } while (0)
static const char PLAN[] =
    "UMICOM_OS_BOOT 1\nhostname=lesson\n"
    "service=display|/usr/libexec/umicom-display|storage|1000\n"
    "service=storage|/usr/libexec/umicom-storage|-|2000\n";
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    UmiOsBootConfig plan;
    CHECK(UmiOsBootConfigParse(PLAN, sizeof PLAN - 1U, &plan));
    if (!strcmp(argv[1], "order")) {
        CHECK(plan.count == 2 && !strcmp(plan.services[plan.order[0]].id, "storage"));
        CHECK(!strcmp(plan.services[plan.order[1]].id, "display"));
    } else if (!strcmp(argv[1], "rollback")) {
        UmiOsBootConfig saved = plan;
        const char broken[] = "UMICOM_OS_BOOT 1\nhostname=lesson\nservice=bad|/bin/sh|-|1000\n";
        CHECK(!UmiOsBootConfigParse(broken, sizeof broken - 1U, &plan));
        CHECK(!memcmp(&saved, &plan, sizeof plan));
    } else if (!strcmp(argv[1], "cycle")) {
        const char cyclic[] = "UMICOM_OS_BOOT 1\nhostname=lesson\n"
            "service=display|/usr/libexec/umicom-display|storage|1000\n"
            "service=storage|/usr/libexec/umicom-storage|display|2000\n";
        CHECK(!UmiOsBootConfigParse(cyclic, sizeof cyclic - 1U, &plan));
    } else if (!strcmp(argv[1], "recovery")) {
        UmiOsBootOptions options = {0};
        const char command[] = "console=ttyS0 umicom.recovery=1";
        CHECK(UmiOsBootOptionsParse(command, sizeof command - 1U, &options));
        CHECK(options.recovery && !options.autopoweroff);
    } else return 2;
    return 0;
}
