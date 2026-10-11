/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/checked-money/test_account.c
 * PURPOSE: Verify checked arithmetic and no partial posting on failures.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "account.h"
#include <inttypes.h>
#include <stdio.h>

#define CHECK(condition) do {                                                   \
    if (!(condition)) {                                                         \
        (void)fprintf(stderr, "FAILED %s:%d: %s\n", __FILE__, __LINE__, #condition); \
        return 1;                                                               \
    }                                                                           \
} while (0)

int main(void)
{
    uint64_t result = 123U;
    CHECK(BtbCheckedAdd(100U, 250U, &result) == BTB_ACCOUNT_OK && result == 350U);
    CHECK(BtbCheckedAdd(UINT64_MAX, 1U, &result) == BTB_ACCOUNT_OVERFLOW);
    CHECK(result == 350U);
    CHECK(BtbCheckedMultiply(UINT64_MAX, 2U, &result) == BTB_ACCOUNT_OVERFLOW);
    CHECK(result == 350U);
    CHECK(BtbCheckedMultiply(250U, 40U, &result) == BTB_ACCOUNT_OK && result == 10000U);
    CHECK(BtbCheckedSubtract(5U, 6U, &result) == BTB_ACCOUNT_INSUFFICIENT_FUNDS);
    CHECK(result == 10000U);
    CHECK(BtbCheckedAdd(1U, 1U, NULL) == BTB_ACCOUNT_INVALID);

    BtbTrainingAccount a = {15000U, 0U};
    BtbTrainingAccount b = {4000U, 0U};
    CHECK(BtbAccountTransfer(&a, &b, 2500U) == BTB_ACCOUNT_OK);
    CHECK(a.balancePence == 12500U && b.balancePence == 6500U);
    CHECK(a.revision == 1U && b.revision == 1U);
    CHECK(BtbAccountTransfer(&a, &b, 999999U) == BTB_ACCOUNT_INSUFFICIENT_FUNDS);
    CHECK(a.balancePence == 12500U && b.balancePence == 6500U);
    CHECK(a.revision == 1U && b.revision == 1U);
    CHECK(BtbAccountTransfer(&a, &a, 1U) == BTB_ACCOUNT_INVALID);
    CHECK(BtbAccountTransfer(&a, &b, 0U) == BTB_ACCOUNT_INVALID);

    BtbTrainingAccount full = {UINT64_MAX, 7U};
    CHECK(BtbAccountTransfer(&a, &full, 1U) == BTB_ACCOUNT_OVERFLOW);
    CHECK(a.balancePence == 12500U && a.revision == 1U);
    CHECK(full.balancePence == UINT64_MAX && full.revision == 7U);

    BtbTrainingAccount noRevision = {5000U, UINT64_MAX};
    CHECK(BtbAccountDebit(&noRevision, 1U) == BTB_ACCOUNT_OVERFLOW);
    CHECK(noRevision.balancePence == 5000U && noRevision.revision == UINT64_MAX);
    CHECK(BtbAccountCredit(NULL, 1U) == BTB_ACCOUNT_INVALID);
    CHECK(BtbAccountCredit(&a, 0U) == BTB_ACCOUNT_INVALID);
    CHECK(a.balancePence == 12500U);

    puts("Checked money: overflow, underflow, revisions and atomic teaching transfers passed.");
    return 0;
}
