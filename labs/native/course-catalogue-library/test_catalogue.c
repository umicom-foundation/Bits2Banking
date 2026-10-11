/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/course-catalogue-library/test_catalogue.c
 * PURPOSE: Check the separate library's public interface and update safety.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "catalogue.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(EXPR) do { if (!(EXPR)) { \
    fprintf(stderr, "Failed at line %d: %s\n", __LINE__, #EXPR); return 1; \
} } while (0)

int main(void)
{
    BtbCourseCatalogue catalogue;
    BtbCatalogueInit(&catalogue);
    CHECK(BtbCatalogueAt(&catalogue, 0U) == NULL);
    CHECK(BtbCatalogueAdd(&catalogue, "Computing", 4U) == BTB_CATALOGUE_OK);
    CHECK(catalogue.count == 1U && catalogue.totalLessons == 4U);
    CHECK(BtbCatalogueAt(&catalogue, 0U) != NULL);
    BtbCourseCatalogue snapshot = catalogue;
    CHECK(BtbCatalogueAdd(&catalogue, "Computing", 3U) == BTB_CATALOGUE_EXISTS);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    CHECK(BtbCatalogueAdd(&catalogue, "", 2U) == BTB_CATALOGUE_INVALID);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    CHECK(BtbCatalogueAdd(&catalogue, "Contains\nnewline", 2U) == BTB_CATALOGUE_INVALID);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    char oversized[BTB_CATALOGUE_TITLE_CAPACITY + 3U];
    memset(oversized, 'A', sizeof(oversized));
    oversized[sizeof(oversized) - 1U] = '\0';
    CHECK(BtbCatalogueAdd(&catalogue, oversized, 2U) == BTB_CATALOGUE_INVALID);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    CHECK(BtbCatalogueAdd(&catalogue, "Overflow", UINT32_MAX) == BTB_CATALOGUE_OVERFLOW);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    CHECK(BtbCatalogueAdd(&catalogue, "Unknown", 0U) == BTB_CATALOGUE_INVALID);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    CHECK(BtbCatalogueAdd(&catalogue, "Assembly", 3U) == BTB_CATALOGUE_OK);
    CHECK(catalogue.totalLessons == 7U);
    CHECK(BtbCatalogueAt(&catalogue, 2U) == NULL);
    for (unsigned i = 0U; i < 6U; ++i) {
        char title[16];
        if (snprintf(title, sizeof(title), "Module-%u", i) < 0) return 1;
        CHECK(BtbCatalogueAdd(&catalogue, title, 1U) == BTB_CATALOGUE_OK);
    }
    CHECK(catalogue.count == BTB_CATALOGUE_MAX_MODULES);
    snapshot = catalogue;
    CHECK(BtbCatalogueAdd(&catalogue, "One more", 1U) == BTB_CATALOGUE_FULL);
    CHECK(memcmp(&catalogue, &snapshot, sizeof(catalogue)) == 0);
    puts("[OK] Separate compilation, capacity, overflow, borrowed read and unchanged failed edits.");
    return 0;
}
