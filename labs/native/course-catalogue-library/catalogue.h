/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/course-catalogue-library/catalogue.h
 * PURPOSE: Public C23 contract for a small training-course catalogue.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_COURSE_CATALOGUE_H
#define BTB_COURSE_CATALOGUE_H
#include <stddef.h>
#include <stdint.h>

#define BTB_CATALOGUE_MAX_MODULES 8U
#define BTB_CATALOGUE_TITLE_CAPACITY 64U

typedef enum BtbCatalogueStatus {
    BTB_CATALOGUE_OK = 0,
    BTB_CATALOGUE_INVALID = 1,
    BTB_CATALOGUE_FULL = 2,
    BTB_CATALOGUE_EXISTS = 3,
    BTB_CATALOGUE_OVERFLOW = 4
} BtbCatalogueStatus;

typedef struct BtbCourseModule {
    char title[BTB_CATALOGUE_TITLE_CAPACITY];
    uint32_t lessonCount;
} BtbCourseModule;

typedef struct BtbCourseCatalogue {
    BtbCourseModule modules[BTB_CATALOGUE_MAX_MODULES];
    size_t count;
    uint32_t totalLessons;
} BtbCourseCatalogue;

/* The caller owns this catalogue. Initialise it before adding entries. */
void BtbCatalogueInit(BtbCourseCatalogue *catalogue);

/* Copy the title and record the lesson count. A failure leaves every byte of
 * the catalogue unchanged, so callers can safely report or retry the edit. */
BtbCatalogueStatus BtbCatalogueAdd(BtbCourseCatalogue *catalogue,
    const char *title, uint32_t lessonCount);

/* The returned pointer is borrowed from catalogue storage and must not be
 * retained after the catalogue is destroyed or mutated. */
const BtbCourseModule *BtbCatalogueAt(const BtbCourseCatalogue *catalogue,
    size_t index);
#endif
