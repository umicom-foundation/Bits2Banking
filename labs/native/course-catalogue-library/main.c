/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/course-catalogue-library/main.c
 * PURPOSE: Compose the catalogue library into a small console application.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "catalogue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BtbCourseCatalogue catalogue;
    BtbCatalogueInit(&catalogue);
    if (BtbCatalogueAdd(&catalogue, "Computer architecture", 4U) != BTB_CATALOGUE_OK ||
        BtbCatalogueAdd(&catalogue, "C23 and Assembly", 9U) != BTB_CATALOGUE_OK ||
        BtbCatalogueAdd(&catalogue, "Banking systems", 8U) != BTB_CATALOGUE_OK)
        return EXIT_FAILURE;
    for (size_t i = 0U; i < catalogue.count; ++i) {
        const BtbCourseModule *entry = BtbCatalogueAt(&catalogue, i);
        if (entry == NULL || printf("%s: %u lessons\n", entry->title,
                (unsigned)entry->lessonCount) < 0) return EXIT_FAILURE;
    }
    if (printf("Total lessons: %u\n", (unsigned)catalogue.totalLessons) < 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
