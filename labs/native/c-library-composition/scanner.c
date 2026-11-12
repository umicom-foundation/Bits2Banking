/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-library-composition/scanner.c
 *
 * PURPOSE:
 *   Count source pages without colliding with another component helper.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "service_api.h"
/* A component prefix scopes external linkage. The optional teaching switch
 * deliberately restores the collision for a separate failing-build exercise. */
#ifndef BTB_TEACH_UNQUALIFIED_HELPERS
#define Count BtbSourceInternalCount
#endif
size_t Count(size_t bytes);
size_t Count(size_t bytes)
{
    return bytes / 256U + (bytes % 256U != 0U ? 1U : 0U);
}
size_t BtbSourcePages(size_t bytes) { return Count(bytes); }
