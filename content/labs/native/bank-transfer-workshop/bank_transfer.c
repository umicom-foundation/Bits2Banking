/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/bank-transfer-workshop/bank_transfer.c
 *
 * PURPOSE:
 *   Teach checked, repeatable transfers over a tiny synthetic ledger.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum { ACCOUNT_COUNT = 2, JOURNAL_CAPACITY = 8 };

typedef struct {
    uint64_t id;
    size_t from;
    size_t to;
    int64_t cents;
} Transfer;

typedef struct {
    int64_t balance[ACCOUNT_COUNT];
    Transfer applied[JOURNAL_CAPACITY];
    size_t used;
} Ledger;

typedef enum {
    TRANSFER_APPLIED,
    TRANSFER_DUPLICATE,
    TRANSFER_CONFLICT,
    TRANSFER_INVALID,
    TRANSFER_INSUFFICIENT,
    TRANSFER_FULL
} TransferStatus;

static TransferStatus post(Ledger *ledger, Transfer request)
{
    /* Reject an incomplete request before indexing balances or reading journal rows. */
    if (ledger == NULL || ledger->used > JOURNAL_CAPACITY || request.id == 0 ||
        request.from >= ACCOUNT_COUNT || request.to >= ACCOUNT_COUNT ||
        request.from == request.to || request.cents <= 0) {
        return TRANSFER_INVALID;
    }

    /* A retry must preserve the original economics. The same identity with
       different fields needs investigation, even when it could be posted. */
    for (size_t row = 0; row < ledger->used; ++row) {
        const Transfer prior = ledger->applied[row];
        if (prior.id == request.id) {
            if (prior.from == request.from && prior.to == request.to &&
                prior.cents == request.cents) {
                return TRANSFER_DUPLICATE;
            }
            return TRANSFER_CONFLICT;
        }
    }

    const int64_t source = ledger->balance[request.from];
    const int64_t target = ledger->balance[request.to];
    /* This practice model admits no overdrafts and refuses an unrepresentable
       credit. Positive amounts keep the checked subtraction and addition safe. */
    if (source < 0 || target < 0 || target > INT64_MAX - request.cents) {
        return TRANSFER_INVALID;
    }
    if (source < request.cents) {
        return TRANSFER_INSUFFICIENT;
    }
    if (ledger->used == JOURNAL_CAPACITY) {
        return TRANSFER_FULL;
    }

    /* All refusals occur before the first write. This is one change in a
       single-threaded exercise. A durable adapter needs a database transaction. */
    ledger->balance[request.from] = source - request.cents;
    ledger->balance[request.to] = target + request.cents;
    ledger->applied[ledger->used++] = request;
    return TRANSFER_APPLIED;
}

int main(void)
{
    Ledger sample = { .balance = { 3000, 1000 } };
    const Transfer request = { .id = 71, .from = 0, .to = 1, .cents = 600 };
    /* Check the four outcomes and the retained journal and balances together. */
    const TransferStatus first = post(&sample, request);
    const TransferStatus retry = post(&sample, request);
    const TransferStatus conflict = post(&sample, (Transfer){71, 0, 1, 650});
    const TransferStatus refusal = post(&sample, (Transfer){72, 0, 1, 2401});
    if (first != TRANSFER_APPLIED || retry != TRANSFER_DUPLICATE ||
        conflict != TRANSFER_CONFLICT || refusal != TRANSFER_INSUFFICIENT ||
        sample.used != 1 || sample.balance[0] != 2400 || sample.balance[1] != 1600) {
        fputs("The training ledger failed its expected checks.\n", stderr);
        return 1;
    }
    printf("Balances: %" PRId64 ", %" PRId64 " cents\n", sample.balance[0], sample.balance[1]);
    printf("Accepted transfers: %zu\n", sample.used);
    return 0;
}
