/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/shared-editor/main.c
 *
 * PURPOSE:
 *   Select a deterministic in-memory editor exercise and return its observed result.
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
    static const char *const buffer_cases[] = {
        "ownership", "positions", "position-refusals", "selection", "selection-refusals"
    };
    static const char *const document_cases[] = {
        "history", "redo-branch", "stale-plan", "other-tab", "invalid-replacement",
        "consumed-plan", "read-only"
    };
    if (argc != 2) {
        fputs("Choose one scenario from the shared editor course README.\n", stderr);
        return 2;
    }
    /* Dispatch labels are course exercises, not another editor command registry. */
    for (size_t i = 0U; i < sizeof buffer_cases / sizeof buffer_cases[0]; ++i)
        if (strcmp(argv[1], buffer_cases[i]) == 0)
            return RunBufferLesson(argv[1]);
    for (size_t i = 0U; i < sizeof document_cases / sizeof document_cases[0]; ++i)
        if (strcmp(argv[1], document_cases[i]) == 0)
            return RunDocumentLesson(argv[1]);
    fputs("Unknown shared editor scenario.\n", stderr);
    return 2;
}
