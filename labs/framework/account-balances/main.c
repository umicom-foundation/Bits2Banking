/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/account-balances/main.c
 *
 * PURPOSE:
 *   Demonstrate scoped banking balances and preservation of a valid display after refusal.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/finance/banking/deposit_account_book.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

static int add_account(UmiBankingDepositAccountBook *book, const char *id,
    const char *customer, const char *currency, int64_t ledger, int64_t available,
    UmiBankingAccountStatus state)
{
    UmiBankingDepositAccount candidate = {0};
    UmiStatus status = umi_banking_deposit_account_init(&candidate, id, customer,
        "learning-deposit", currency, ledger, available, state);
    if (status == UMI_STATUS_OK)
        status = umi_banking_deposit_account_book_add(book, &candidate);
    if (status != UMI_STATUS_OK) fprintf(stderr, "Account refused: %s\n", umi_status_text(status));
    return status == UMI_STATUS_OK;
}

int main(void)
{
    UmiBankingDepositAccountBook book = {0};
    UmiBankingDepositSummary report = {0}, previous;
    UmiCurrency gbp = {{'G','B','P','\0'}};
    if (!add_account(&book, "current", "learner", "GBP", 10000, 8500, UMI_BANKING_ACCOUNT_OPEN) ||
        !add_account(&book, "review", "learner", "GBP", 2000, 1000, UMI_BANKING_ACCOUNT_BLOCKED) ||
        !add_account(&book, "dollar", "learner", "USD", 400, 300, UMI_BANKING_ACCOUNT_OPEN) ||
        !add_account(&book, "other", "another", "GBP", 500, 500, UMI_BANKING_ACCOUNT_OPEN)) return 1;
    UmiStatus status = UmiBankingDepositAccountBookSummarise(&book, "learner", &gbp, &report);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Summary refused: %s\n", umi_status_text(status));
        return 1;
    }
    printf("%s %s: %zu accounts, %zu blocked\n",
        report.customer_id.value, report.currency.code, report.account_count, report.blocked_count);
    printf("Ledger minor units: %" PRId64 "\nAvailable minor units: %" PRId64
        "\nReserved minor units: %" PRId64 "\n",
        report.ledger_minor, report.available_minor, report.reserved_minor);
    if (report.account_count != 2 || report.ledger_minor != 12000 ||
        report.available_minor != 9500 || report.reserved_minor != 2500) return 1;
    /* A display keeps its last complete projection when damaged input arrives.
     * This deliberately corrupts a synthetic record to exercise that boundary. */
    memcpy(&previous, &report, sizeof previous);
    book.items[3].available_minor = 501;
    status = UmiBankingDepositAccountBookSummarise(&book, "learner", &gbp, &report);
    if (status != UMI_STATUS_INVALID_STATE || memcmp(&previous, &report, sizeof report) != 0) return 1;
    puts("Invalid source refused; previous summary preserved.");
    puts("This balance view grants no payment or account access.");
    return 0;
}
