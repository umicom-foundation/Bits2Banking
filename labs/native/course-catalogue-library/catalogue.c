/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/course-catalogue-library/catalogue.c
 * PURPOSE: Implement a bounded module catalogue for static-library lessons.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "catalogue.h"
#include <string.h>
#include <stdint.h>

void BtbCatalogueInit(BtbCourseCatalogue *catalogue)
{
    if (catalogue != NULL) *catalogue = (BtbCourseCatalogue){0};
}

BtbCatalogueStatus BtbCatalogueAdd(BtbCourseCatalogue *catalogue,
    const char *title, uint32_t lessonCount)
{
    if (catalogue == NULL || title == NULL || lessonCount == 0U)
        return BTB_CATALOGUE_INVALID;
    size_t length = 0U;
    while (length < BTB_CATALOGUE_TITLE_CAPACITY && title[length] != '\0') {
        const unsigned char value = (unsigned char)title[length];
        if (value < 0x20U || value == 0x7fU) return BTB_CATALOGUE_INVALID;
        ++length;
    }
    if (length == 0U || length == BTB_CATALOGUE_TITLE_CAPACITY)
        return BTB_CATALOGUE_INVALID;
    if (catalogue->count > BTB_CATALOGUE_MAX_MODULES)
        return BTB_CATALOGUE_INVALID;
    for (size_t i = 0U; i < catalogue->count; ++i)
        if (strcmp(catalogue->modules[i].title, title) == 0)
            return BTB_CATALOGUE_EXISTS;
    if (catalogue->count == BTB_CATALOGUE_MAX_MODULES)
        return BTB_CATALOGUE_FULL;
    if (lessonCount > UINT32_MAX - catalogue->totalLessons)
        return BTB_CATALOGUE_OVERFLOW;

    /* All validation finishes before one atomic logical update. The title is
     * stored inside the caller's catalogue, not as a borrowed input pointer. */
    BtbCourseModule *entry = &catalogue->modules[catalogue->count];
    memcpy(entry->title, title, length + 1U);
    entry->lessonCount = lessonCount;
    catalogue->totalLessons += lessonCount;
    ++catalogue->count;
    return BTB_CATALOGUE_OK;
}

const BtbCourseModule *BtbCatalogueAt(const BtbCourseCatalogue *catalogue,
    size_t index)
{
    return catalogue != NULL && index < catalogue->count &&
           catalogue->count <= BTB_CATALOGUE_MAX_MODULES ?
        &catalogue->modules[index] : NULL;
}
