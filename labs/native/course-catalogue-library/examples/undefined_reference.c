/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/course-catalogue-library/examples/undefined_reference.c
 * PURPOSE: Source for manually reproducing an unresolved external symbol.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
/* This is a deliberately incomplete teaching example and is NOT part of any
 * executable target. Compare the linker diagnostic with the CMake library
 * target to understand how separate object files become one programme. */
#include "../catalogue.h"

int main(void)
{
    BtbCourseCatalogue value;
    BtbCatalogueInit(&value); /* Declared in a header, defined in catalogue.c. */
    return (int)value.count;
}
