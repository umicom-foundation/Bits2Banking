/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-checksum/checksum.h
 *
 * PURPOSE:
 *   Expose a teaching adapter from a borrowed C stream to Framework SHA-256.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_FRAMEWORK_CHECKSUM_H
#define BTB_FRAMEWORK_CHECKSUM_H
#include "umicom/base/sha256.h"
#include <stdio.h>

/* Read from the stream's current position to EOF. The caller owns and closes
 * the stream. A failure leaves output unchanged, but consumed input cannot
 * be rolled back. Output needs UMI_SHA256_HEX_CAPACITY writable bytes and
 * must not overlap the FILE object. The function does not seek or clear errors. */
UmiStatus BtbChecksumStream(FILE *stream, char output[UMI_SHA256_HEX_CAPACITY]);
#endif

