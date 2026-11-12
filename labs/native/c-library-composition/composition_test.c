/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-library-composition/composition_test.c
 *
 * PURPOSE:
 *   Exercise both independently linked services and their size boundaries.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "service_api.h"
#include <stdint.h>
#include <stdio.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; \
} } while (0)
int main(void)
{
    CHECK(BtbSourcePages(0U) == 0U);
    CHECK(BtbSourcePages(1U) == 1U);
    CHECK(BtbSourcePages(256U) == 1U);
    CHECK(BtbSourcePages(257U) == 2U);
    CHECK(BtbSourcePages(SIZE_MAX) == SIZE_MAX / 256U + 1U);
    CHECK(BtbCatalogueBytes(0U) == 0U);
    CHECK(BtbCatalogueBytes(3U) == 24U);
    CHECK(BtbCatalogueBytes(SIZE_MAX / 8U) == (SIZE_MAX / 8U) * 8U);
    CHECK(BtbCatalogueBytes(SIZE_MAX / 8U + 1U) == SIZE_MAX);
    CHECK(BtbSourcePages(257U) == 2U);
    return 0;
}
