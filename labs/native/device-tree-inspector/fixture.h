/*-----------------------------------------------------------------------------
 * Bits2Banking — Device Tree Inspector
 * File: labs/native/device-tree-inspector/fixture.h
 * PURPOSE: Construct one valid synthetic device-tree byte array for teaching.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_FDT_FIXTURE_H
#define BTB_FDT_FIXTURE_H
#include <stddef.h>
#include <stdint.h>
size_t BtbFdtMakeFixture(unsigned char *output, size_t capacity);
void BtbFdtWriteBe32(unsigned char *out, uint32_t value);
#endif
