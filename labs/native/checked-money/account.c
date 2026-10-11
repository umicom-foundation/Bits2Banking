/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/checked-money/account.c
 * PURPOSE: Reject arithmetic errors before publishing account changes.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "account.h"
#include <stdint.h>
#include <stddef.h>

BtbAccountStatus BtbCheckedAdd(uint64_t left, uint64_t right, uint64_t *out)
{
    if (out == NULL) return BTB_ACCOUNT_INVALID;
    if (left > UINT64_MAX - right) return BTB_ACCOUNT_OVERFLOW;
    *out = left + right;
    return BTB_ACCOUNT_OK;
}
BtbAccountStatus BtbCheckedMultiply(uint64_t left, uint64_t right, uint64_t *out)
{
    if (out == NULL) return BTB_ACCOUNT_INVALID;
    if (right != 0U && left > UINT64_MAX / right) return BTB_ACCOUNT_OVERFLOW;
    *out = left * right;
    return BTB_ACCOUNT_OK;
}
BtbAccountStatus BtbCheckedSubtract(uint64_t left, uint64_t right, uint64_t *out)
{
    if (out == NULL) return BTB_ACCOUNT_INVALID;
    if (left < right) return BTB_ACCOUNT_INSUFFICIENT_FUNDS;
    *out = left - right;
    return BTB_ACCOUNT_OK;
}

BtbAccountStatus BtbAccountCredit(BtbTrainingAccount *account, uint64_t amountPence)
{
    if (account == NULL || amountPence == 0U) return BTB_ACCOUNT_INVALID;
    uint64_t balance = 0U;
    uint64_t revision = 0U;
    BtbAccountStatus status = BtbCheckedAdd(account->balancePence, amountPence, &balance);
    if (status == BTB_ACCOUNT_OK)
        status = BtbCheckedAdd(account->revision, 1U, &revision);
    if (status != BTB_ACCOUNT_OK) return status;
    account->balancePence = balance;
    account->revision = revision;
    return BTB_ACCOUNT_OK;
}

BtbAccountStatus BtbAccountDebit(BtbTrainingAccount *account, uint64_t amountPence)
{
    if (account == NULL || amountPence == 0U) return BTB_ACCOUNT_INVALID;
    uint64_t balance = 0U;
    uint64_t revision = 0U;
    BtbAccountStatus status = BtbCheckedSubtract(account->balancePence, amountPence, &balance);
    if (status == BTB_ACCOUNT_OK)
        status = BtbCheckedAdd(account->revision, 1U, &revision);
    if (status != BTB_ACCOUNT_OK) return status;
    account->balancePence = balance;
    account->revision = revision;
    return BTB_ACCOUNT_OK;
}

BtbAccountStatus BtbAccountTransfer(BtbTrainingAccount *from,
                                    BtbTrainingAccount *to, uint64_t amountPence)
{
    if (from == NULL || to == NULL || from == to || amountPence == 0U)
        return BTB_ACCOUNT_INVALID;
    uint64_t fromBalance = 0U;
    uint64_t toBalance = 0U;
    uint64_t fromRevision = 0U;
    uint64_t toRevision = 0U;
    BtbAccountStatus status = BtbCheckedSubtract(from->balancePence, amountPence, &fromBalance);
    if (status == BTB_ACCOUNT_OK)
        status = BtbCheckedAdd(to->balancePence, amountPence, &toBalance);
    if (status == BTB_ACCOUNT_OK)
        status = BtbCheckedAdd(from->revision, 1U, &fromRevision);
    if (status == BTB_ACCOUNT_OK)
        status = BtbCheckedAdd(to->revision, 1U, &toRevision);
    if (status != BTB_ACCOUNT_OK) return status;

    /* The pair is committed only after every necessary check succeeds.
     * This is a teaching demonstration, not crash-durable or thread-safe. */
    from->balancePence = fromBalance;
    to->balancePence = toBalance;
    from->revision = fromRevision;
    to->revision = toRevision;
    return BTB_ACCOUNT_OK;
}

const char *BtbAccountStatusText(BtbAccountStatus status)
{
    switch (status) {
    case BTB_ACCOUNT_OK: return "OK";
    case BTB_ACCOUNT_INVALID: return "invalid input";
    case BTB_ACCOUNT_OVERFLOW: return "arithmetic or revision overflow";
    case BTB_ACCOUNT_INSUFFICIENT_FUNDS: return "insufficient fictional funds";
    default: return "unknown status";
    }
}
