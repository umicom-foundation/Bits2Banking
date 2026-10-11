/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/static-library-map/src/ledger.c
 * PURPOSE: Implement a small checked reusable library for educational builds.
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "btb/ledger.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/* Only the two BtbLedger* functions in ledger.h form this library's public
 * contract. This private helper has internal linkage (static): other object
 * files cannot resolve a reference to its symbol. */
static BtbLedgerStatus AddChecked(uint64_t left, uint64_t right, uint64_t *out)
{
    if (right > UINT64_MAX - left) return BTB_LEDGER_OVERFLOW;
    *out = left + right;
    return BTB_LEDGER_OK;
}

BtbLedgerStatus BtbLedgerTotalPence(const uint64_t *entries,
    size_t count, uint64_t *outTotal)
{
    if (outTotal == NULL || (entries == NULL && count != 0U))
        return BTB_LEDGER_BAD_ARGUMENT;
    uint64_t result = 0U;
    for (size_t i = 0U; i < count; ++i) {
        BtbLedgerStatus status = AddChecked(result, entries[i], &result);
        if (status != BTB_LEDGER_OK) return status;
    }
    *outTotal = result;
    return BTB_LEDGER_OK;
}

BtbLedgerStatus BtbLedgerFormatPence(uint64_t amount,
    char *outText, size_t capacity)
{
    if (outText == NULL) return BTB_LEDGER_BAD_ARGUMENT;
    char formatted[48];
    int count = snprintf(formatted, sizeof(formatted), "GBP %" PRIu64 ".%02" PRIu64,
                         amount / UINT64_C(100), amount % UINT64_C(100));
    if (count < 0 || (size_t)count >= sizeof(formatted))
        return BTB_LEDGER_BUFFER_TOO_SMALL;
    if ((size_t)count + 1U > capacity) return BTB_LEDGER_BUFFER_TOO_SMALL;
    memcpy(outText, formatted, (size_t)count + 1U);
    return BTB_LEDGER_OK;
}
