/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-library-composition/service_api.h
 *
 * PURPOSE:
 *   Declare two educational services whose internal counters have different units.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_LEARNING_COMPOSITION_API_H
#define UMICOM_LEARNING_COMPOSITION_API_H
#include <stddef.h>
/* Educational services use distinct units and do not share their counters. */
size_t BtbSourcePages(size_t bytes);
size_t BtbCatalogueBytes(size_t entries);
#endif
