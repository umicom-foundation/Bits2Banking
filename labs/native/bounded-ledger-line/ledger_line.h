/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/bounded-ledger-line/ledger_line.h
 * PURPOSE: Parse a deliberately small ledger-record format from exact bytes.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS2BANKING_LEDGER_LINE_H
#define BITS2BANKING_LEDGER_LINE_H
#include <stddef.h>
#include <stdint.h>

typedef enum BtbLedgerStatus {
    BTB_LEDGER_OK = 0,
    BTB_LEDGER_INVALID = 1,
    BTB_LEDGER_RANGE = 2
} BtbLedgerStatus;

typedef struct BtbLedgerRow {
    uint32_t accountId;
    int64_t changePence;
} BtbLedgerRow;

/* Exact byte grammar: ACCOUNT:SIGNED_PENCE; e.g. 1001:+2500.
 * ACCOUNT has one or more ASCII digits. SIGNED_PENCE requires '+' or '-',
 * then one or more ASCII digits. No whitespace, quoting, embedded NUL or
 * trailing newline. This is a teaching wire format, not ISO 20022 or CSV.
 * count is bounded to 128 bytes. On failure *outRow remains unchanged. */
BtbLedgerStatus BtbLedgerLineParse(const unsigned char *bytes,
                                   size_t count, BtbLedgerRow *outRow);
#endif
