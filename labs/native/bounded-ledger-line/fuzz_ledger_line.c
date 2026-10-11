/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/bounded-ledger-line/fuzz_ledger_line.c
 * PURPOSE: Repeat deterministic malformed-byte checks without external fuzzers.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "ledger_line.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint32_t Next(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

int main(void)
{
    uint32_t state = UINT32_C(0x2B720026);
    unsigned char bytes[144];
    for (size_t sample = 0U; sample < 20000U; ++sample) {
        size_t count = (size_t)(Next(&state) % 145U);
        for (size_t i = 0U; i < count; ++i)
            bytes[i] = (unsigned char)(Next(&state) >> 24U);
        BtbLedgerRow row = {UINT32_C(0x11223344), INT64_C(123456789)};
        BtbLedgerStatus result = BtbLedgerLineParse(bytes, count, &row);
        if (result != BTB_LEDGER_OK &&
            (row.accountId != UINT32_C(0x11223344) || row.changePence != INT64_C(123456789))) {
            fprintf(stderr, "Failed input changed the destination at case %zu\n", sample);
            return 1;
        }
        if (result == BTB_LEDGER_OK && count > 128U) {
            fputs("Oversized input was accepted.\n", stderr);
            return 1;
        }
    }
    puts("20,000 deterministic inputs checked; rejected data never changes the record.");
    return 0;
}
