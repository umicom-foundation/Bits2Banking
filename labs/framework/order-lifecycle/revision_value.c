/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/order-lifecycle/revision_value.c
 *
 * PURPOSE:
 *   Demonstrate exact unsigned observation display through the shared Framework UI value service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "umicom/ui/value.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: btb-revision-value small|boundary|maximum\n", stderr); return 2;
    }
    uint64_t number;
    const char *expected;
    if (!strcmp(argv[1], "small")) { number = 42U; expected = "42"; }
    else if (!strcmp(argv[1], "boundary")) { number = UINT64_C(9223372036854775808); expected = "9223372036854775808"; }
    else if (!strcmp(argv[1], "maximum")) { number = UINT64_MAX; expected = "18446744073709551615"; }
    else { fputs("Unknown observation example.\n", stderr); return 2; }
    UmiUiValue value;
    UmiStatus status = UmiUiValueSetUnsigned(&value, number);
    if (status != UMI_STATUS_OK) { fprintf(stderr, "Value conversion failed: %d\n", status); return 1; }
    /* The service owns conversion. This client only checks and presents the
     * documented existing kinds; it never casts a large value to signed. */
    if (number <= (uint64_t)INT64_MAX) {
        if (value.kind != UMI_UI_VALUE_INTEGER || value.integer_value != (int64_t)number) return 1;
        printf("INTEGER: %" PRId64 "\n", value.integer_value);
    } else {
        if (value.kind != UMI_UI_VALUE_STRING || strcmp(value.string_value, expected)) return 1;
        printf("STRING: %s\n", value.string_value);
    }
    return 0;
}
