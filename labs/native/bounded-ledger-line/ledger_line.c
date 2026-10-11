/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/bounded-ledger-line/ledger_line.c
 * PURPOSE: Check every offset and integer operation before publishing a row.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "ledger_line.h"
#include <stdint.h>

BtbLedgerStatus BtbLedgerLineParse(const unsigned char *bytes,
                                   size_t count, BtbLedgerRow *outRow)
{
    if (bytes == NULL || outRow == NULL || count < 4U || count > 128U)
        return BTB_LEDGER_INVALID;
    size_t position = 0U;
    uint32_t account = 0U;
    size_t accountDigits = 0U;
    while (position < count && bytes[position] >= (unsigned char)'0' &&
           bytes[position] <= (unsigned char)'9') {
        uint32_t digit = (uint32_t)(bytes[position] - (unsigned char)'0');
        if (account > (UINT32_MAX - digit) / 10U) return BTB_LEDGER_RANGE;
        account = account * 10U + digit;
        ++position;
        ++accountDigits;
    }
    if (accountDigits == 0U || position >= count || bytes[position] != (unsigned char)':')
        return BTB_LEDGER_INVALID;
    ++position;
    if (position >= count || (bytes[position] != (unsigned char)'+' &&
                              bytes[position] != (unsigned char)'-'))
        return BTB_LEDGER_INVALID;
    int negative = bytes[position] == (unsigned char)'-';
    ++position;
    if (position >= count) return BTB_LEDGER_INVALID;
    uint64_t magnitude = 0U;
    uint64_t limit = (uint64_t)INT64_MAX + (negative ? UINT64_C(1) : UINT64_C(0));
    size_t digits = 0U;
    for (; position < count; ++position) {
        unsigned char value = bytes[position];
        if (value < (unsigned char)'0' || value > (unsigned char)'9')
            return BTB_LEDGER_INVALID;
        uint64_t digit = (uint64_t)(value - (unsigned char)'0');
        if (magnitude > (limit - digit) / UINT64_C(10))
            return BTB_LEDGER_RANGE;
        magnitude = magnitude * UINT64_C(10) + digit;
        ++digits;
    }
    if (digits == 0U) return BTB_LEDGER_INVALID;
    BtbLedgerRow result;
    result.accountId = account;
    if (negative && magnitude == (uint64_t)INT64_MAX + UINT64_C(1))
        result.changePence = INT64_MIN;
    else {
        int64_t signedMagnitude = (int64_t)magnitude; /* <= INT64_MAX */
        result.changePence = negative ? -signedMagnitude : signedMagnitude;
    }
    /* The destination is written once, after the entire record is validated. */
    *outRow = result;
    return BTB_LEDGER_OK;
}
