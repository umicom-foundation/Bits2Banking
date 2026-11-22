/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/mysql-ledger/main.c
 *
 * PURPOSE:
 *   Qualify the signed row values a MySQL client passes to the native ledger rule.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct LedgerRow {
    int64_t cents;
    bool posted;
};

static bool posted_cents(const struct LedgerRow *rows, size_t count, int64_t *result)
{
    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        if (!rows[i].posted) {
            continue;
        }
        const int64_t cents = rows[i].cents;
        // Reject overflow without evaluating the overflowing addition.
        if ((cents > 0 && sum > INT64_MAX - cents) ||
            (cents < 0 && sum < INT64_MIN - cents)) {
            return false;
        }
        sum += cents;
    }
    // The caller's previous complete result survives every rejected batch.
    *result = sum;
    return true;
}

int main(void)
{
    const struct LedgerRow normal[] = {{2600, true}, {-850, true}, {500, false}};
    const struct LedgerRow overflowing[] = {{INT64_MAX, true}, {1, true}};
    int64_t result = -99;

    if (!posted_cents(normal, 3, &result) || result != 1750 ||
        posted_cents(overflowing, 2, &result) || result != 1750 ||
        !posted_cents(normal, 0, &result) || result != 0) {
        fputs("ledger rule mismatch\n", stderr);
        return 1;
    }
    puts("posted cents and overflow checks ready");
    return 0;
}
