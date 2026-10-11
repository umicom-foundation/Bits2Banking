/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/static-library-map/tests/test_ledger.c
 * PURPOSE: Test a public C23 library contract independently of its CLI.
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "btb/ledger.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"FAIL at %d: %s\n",__LINE__,#x); return 1; } } while(0)

int main(void)
{
    const uint64_t valid[] = {UINT64_C(999), UINT64_C(1)};
    uint64_t total = 7U;
    CHECK(BtbLedgerTotalPence(valid, 2U, &total) == BTB_LEDGER_OK);
    CHECK(total == 1000U);
    CHECK(BtbLedgerTotalPence(NULL, 0U, &total) == BTB_LEDGER_OK);
    CHECK(total == 0U);
    total = 42U;
    const uint64_t tooLarge[] = {UINT64_MAX, 1U};
    CHECK(BtbLedgerTotalPence(tooLarge, 2U, &total) == BTB_LEDGER_OVERFLOW);
    CHECK(total == 42U);
    CHECK(BtbLedgerTotalPence(NULL, 1U, &total) == BTB_LEDGER_BAD_ARGUMENT);
    CHECK(total == 42U);
    CHECK(BtbLedgerTotalPence(valid, 2U, NULL) == BTB_LEDGER_BAD_ARGUMENT);
    char text[48] = "previous-result";
    CHECK(BtbLedgerFormatPence(12501U, text, 4U) == BTB_LEDGER_BUFFER_TOO_SMALL);
    CHECK(strcmp(text, "previous-result") == 0);
    CHECK(BtbLedgerFormatPence(12501U, text, sizeof(text)) == BTB_LEDGER_OK);
    CHECK(strcmp(text, "GBP 125.01") == 0);
    CHECK(BtbLedgerFormatPence(UINT64_MAX, text, sizeof(text)) == BTB_LEDGER_OK);
    CHECK(strcmp(text, "GBP 184467440737095516.15") == 0);
    puts("[OK] Library outputs preserved on failures; exact pence formatting.");
    return 0;
}
