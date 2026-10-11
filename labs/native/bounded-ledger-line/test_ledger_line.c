/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/bounded-ledger-line/test_ledger_line.c
 * PURPOSE: Verify exact bounds, refusal without mutation and signed limits.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "ledger_line.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(c) do { if (!(c)) { \
    fprintf(stderr, "ledger test failure line %d: %s\n", __LINE__, #c); return 1; \
} } while (0)

static BtbLedgerStatus Parse(const char *text, BtbLedgerRow *row)
{
    return BtbLedgerLineParse((const unsigned char *)text, strlen(text), row);
}

int main(void)
{
    BtbLedgerRow row = {1001U, 99};
    CHECK(Parse("1001:+2500", &row) == BTB_LEDGER_OK);
    CHECK(row.accountId == 1001U && row.changePence == 2500);
    CHECK(Parse("1001:-15", &row) == BTB_LEDGER_OK);
    CHECK(row.accountId == 1001U && row.changePence == -15);
    CHECK(Parse("4294967295:+9223372036854775807", &row) == BTB_LEDGER_OK);
    CHECK(row.accountId == UINT32_MAX && row.changePence == INT64_MAX);
    CHECK(Parse("0:-9223372036854775808", &row) == BTB_LEDGER_OK);
    CHECK(row.accountId == 0U && row.changePence == INT64_MIN);
    BtbLedgerRow saved = row;
    CHECK(Parse("4294967296:+1", &row) == BTB_LEDGER_RANGE);
    CHECK(memcmp(&saved, &row, sizeof(row)) == 0);
    CHECK(Parse("1001:+9223372036854775808", &row) == BTB_LEDGER_RANGE);
    CHECK(memcmp(&saved, &row, sizeof(row)) == 0);
    CHECK(Parse("1001:-9223372036854775809", &row) == BTB_LEDGER_RANGE);
    CHECK(memcmp(&saved, &row, sizeof(row)) == 0);
    CHECK(Parse("1001:2500", &row) == BTB_LEDGER_INVALID);
    CHECK(Parse("1001:+", &row) == BTB_LEDGER_INVALID);
    CHECK(Parse(":+1", &row) == BTB_LEDGER_INVALID);
    CHECK(Parse("1001:+12\n", &row) == BTB_LEDGER_INVALID);
    CHECK(Parse("1001:+12,admin", &row) == BTB_LEDGER_INVALID);
    CHECK(memcmp(&saved, &row, sizeof(row)) == 0);
    {
        unsigned char raw[] = {'1', '0', '0', '1', ':', '+', '1', 0U, '9'};
        CHECK(BtbLedgerLineParse(raw, sizeof(raw), &row) == BTB_LEDGER_INVALID);
        CHECK(memcmp(&saved, &row, sizeof(row)) == 0);
    }
    CHECK(BtbLedgerLineParse(NULL, 0U, &row) == BTB_LEDGER_INVALID);
    CHECK(BtbLedgerLineParse((const unsigned char *)"1:+0", 4U, NULL) == BTB_LEDGER_INVALID);
    puts("Ledger records passed: signed limits, malformed bytes, overflow, unchanged output.");
    return 0;
}
