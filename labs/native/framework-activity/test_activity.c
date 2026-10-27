/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/framework-activity/test_activity.c
 *
 * PURPOSE:
 *   Check count boundaries, failure preservation and caller-owned output memory.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "activity.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #c); return 1; } } while (0)
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    unsigned result = 77U;
    if (!strcmp(argv[1], "first")) {
        CHECK(BtbActivityAdvance(0U, &result) == UMI_STATUS_OK && result == 1U);
    } else if (!strcmp(argv[1], "last")) {
        CHECK(BtbActivityAdvance(999U, &result) == UMI_STATUS_OK && result == 1000U);
    } else if (!strcmp(argv[1], "full")) {
        CHECK(BtbActivityAdvance(1000U, &result) == UMI_STATUS_CAPACITY_EXCEEDED && result == 77U);
    } else if (!strcmp(argv[1], "invalid")) {
        CHECK(BtbActivityAdvance(UINT_MAX, &result) == UMI_STATUS_INVALID_ARGUMENT && result == 77U);
    } else if (!strcmp(argv[1], "null")) {
        CHECK(BtbActivityAdvance(0U, NULL) == UMI_STATUS_INVALID_ARGUMENT);
    } else if (!strcmp(argv[1], "in-place")) {
        result = 9U;
        CHECK(BtbActivityAdvance(result, &result) == UMI_STATUS_OK && result == 10U);
    } else return 2;
    CHECK(umi_status_text(UMI_STATUS_OK) != NULL);
    return 0;
}
