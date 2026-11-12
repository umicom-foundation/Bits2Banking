/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-library-composition/catalogue.c
 *
 * PURPOSE:
 *   Count catalogue bytes with bounded multiplication and independent symbol ownership.
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
#ifndef BTB_TEACH_UNQUALIFIED_HELPERS
#define Count BtbCatalogueInternalCount
#endif
/* This Count has a different contract and even a different parameter list.
 * Linker order cannot make the two implementations interchangeable. */
size_t Count(size_t entries, size_t width);
size_t Count(size_t entries, size_t width)
{
    return entries > SIZE_MAX / width ? SIZE_MAX : entries * width;
}
size_t BtbCatalogueBytes(size_t entries) { return Count(entries, 8U); }
