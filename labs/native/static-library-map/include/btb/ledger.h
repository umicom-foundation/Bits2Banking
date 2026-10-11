/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/static-library-map/include/btb/ledger.h
 * PURPOSE: Public, checked pence-totalling interface for a fictional ledger.
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_LEDGER_H
#define BTB_LEDGER_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum BtbLedgerStatus {
    BTB_LEDGER_OK = 0,
    BTB_LEDGER_BAD_ARGUMENT,
    BTB_LEDGER_OVERFLOW,
    BTB_LEDGER_BUFFER_TOO_SMALL
} BtbLedgerStatus;

/* Entries are borrowed for the duration of this call; no allocation or I/O.
 * Empty lists are valid. On any failure, *outTotal is unchanged. */
BtbLedgerStatus BtbLedgerTotalPence(const uint64_t *entries,
    size_t count, uint64_t *outTotal);

/* Render exact GBP major/minor units with no floating-point conversion.
 * outText remains unchanged when the capacity is insufficient. */
BtbLedgerStatus BtbLedgerFormatPence(uint64_t amount,
    char *outText, size_t capacity);

#ifdef __cplusplus
}
#endif
#endif
