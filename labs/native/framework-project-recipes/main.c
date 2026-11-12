/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-project-recipes/main.c
 *
 * PURPOSE:
 *   Select one memory-only project recipe observation and report its scoped outcome.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static const char *const inputs[] = {
        "catalogue", "variables", "invalid-variable", "request",
        "invalid-request", "destination", "reserved-folder"
    };
    static const char *const previews[] = {
        "preview", "late-failure", "duplicate", "aliased-root", "gtk-branding"
    };
    if (argc != 2) {
        fputs("Use project-recipes <scenario>; see README.md.\n", stderr);
        return 2;
    }
    int result = 2;
    for (size_t i = 0U; i < sizeof inputs / sizeof inputs[0]; ++i)
        if (strcmp(argv[1], inputs[i]) == 0) result = LabInputScenario(argv[1]);
    for (size_t i = 0U; i < sizeof previews / sizeof previews[0]; ++i)
        if (strcmp(argv[1], previews[i]) == 0) result = LabPreviewScenario(argv[1]);
    if (result == 0)
        printf("%s: expected in-memory observation; no project was created.\n", argv[1]);
    else if (result == 2)
        fputs("Unknown scenario; see README.md.\n", stderr);
    return result;
}
