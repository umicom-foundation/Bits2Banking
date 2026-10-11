/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/checked-money/account.h
 * PURPOSE: Check exact integer arithmetic for a fictional ledger exercise.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS2BANKING_CHECKED_ACCOUNT_H
#define BITS2BANKING_CHECKED_ACCOUNT_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum BtbAccountStatus {
    BTB_ACCOUNT_OK = 0,
    BTB_ACCOUNT_INVALID = 1,
    BTB_ACCOUNT_OVERFLOW = 2,
    BTB_ACCOUNT_INSUFFICIENT_FUNDS = 3
} BtbAccountStatus;

typedef struct BtbTrainingAccount {
    uint64_t balancePence;
    uint64_t revision;
} BtbTrainingAccount;

/* Out arguments must be non-NULL; failure does not modify them. */
BtbAccountStatus BtbCheckedAdd(uint64_t left, uint64_t right, uint64_t *out);
BtbAccountStatus BtbCheckedMultiply(uint64_t left, uint64_t right, uint64_t *out);
BtbAccountStatus BtbCheckedSubtract(uint64_t left, uint64_t right, uint64_t *out);

/* These operate on fictional nonnegative GBP balances, measured in pence.
 * They are NOT payment or banking APIs. Call only from one owner thread.
 * Both balances and revisions remain unchanged on failure. */
BtbAccountStatus BtbAccountCredit(BtbTrainingAccount *account, uint64_t amountPence);
BtbAccountStatus BtbAccountDebit(BtbTrainingAccount *account, uint64_t amountPence);
BtbAccountStatus BtbAccountTransfer(BtbTrainingAccount *from,
                                    BtbTrainingAccount *to, uint64_t amountPence);
const char *BtbAccountStatusText(BtbAccountStatus status);
#ifdef __cplusplus
}
#endif
#endif
