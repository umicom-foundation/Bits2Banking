/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/studio-build-evidence/main.c
 *
 * PURPOSE:
 *   Turn a typed evidence assessment into a CLI result and process exit.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "evidence.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        fputs("usage: expected-sha256 observed-sha256\n", stderr);
        return UMICOM_LAB_EVIDENCE_INVALID;
    }

    /* The program output teaches the result. The exit code lets its caller
     * decide whether to accept it as the expected outcome of an exercise. */
    const enum UmicomLabEvidence result = UmicomLabCompareEvidence(argv[1], argv[2]);
    const char *message = NULL;
    switch (result) {
    case UMICOM_LAB_EVIDENCE_MATCH:
        message = "evidence matches";
        break;
    case UMICOM_LAB_EVIDENCE_CHANGED:
        message = "evidence differs";
        break;
    case UMICOM_LAB_EVIDENCE_INVALID:
        message = "invalid digest record";
        break;
    }
    /* A buffered write can fail at flush time. Reserve exit 1 for output
     * failure, which the test must never treat as a valid refusal. */
    if (message == NULL || puts(message) == EOF || fflush(stdout) == EOF)
        return 1;
    return (int)result;
}
