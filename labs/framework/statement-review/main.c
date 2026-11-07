/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/framework/statement-review/main.c
 *
 * PURPOSE:
 *   Compare fictional statement observations through Framework and reopen an owned review.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "umicom/bank_feed/csv_import.h"
#include "umicom/bank_feed/statement_archive.h"
#include "umicom/finance/decimal.h"

/* This is invented teaching data. Framework owns parsing, amounts, scope and
 * archive rules; this small client owns only the exercise and its diagnostics. */
static const char observations[] =
    "account,transaction,reference,information,booking_date,currency,amount,status,mutability\n"
    "lesson-account,credit-1,,Example receipt,2026-10-12,GBP,12.50,BOOK,Immutable\n"
    "lesson-account,debit-1,,Example purchase,2026-10-12,GBP,-2.25,BOOK,Immutable\n"
    "lesson-account,pending-1,,Pending purchase,2026-10-12,GBP,-999.00,PDNG,Mutable\n"
    "lesson-account,earlier-1,,Earlier receipt,2026-10-11,GBP,50.00,BOOK,Immutable\n"
    "another-account,other-1,,Separate account,2026-10-12,GBP,900.00,BOOK,Immutable\n"
    "lesson-account,euro-1,,Separate currency,2026-10-12,EUR,80.00,BOOK,Immutable\n";

static int money_is(UmiDecimal value, const char *text)
{
    UmiDecimal expected = {0};
    int order = 0;
    return UmiDecimalParse(text, strlen(text), 2U, &expected) == UMI_STATUS_OK &&
           UmiDecimalCompare(value, expected, &order) == UMI_STATUS_OK && order == 0;
}

/* A single exit path releases every successful allocation, including an early
 * failure. Checks are ordinary control flow and remain active in release builds. */
#define REQUIRE(expression) do { if (!(expression)) { \
    fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #expression); \
    goto finish; } } while (0)

int main(void)
{
    UmiBankFeed *feed = NULL;
    UmiBankFeed *copy = NULL;
    UmiBankFeed *rejected = NULL;
    UmiBankStatementArchive *archive = NULL;
    UmiBankStatementArchive *reopened = NULL;
    UmiBankFeedCsvIssue issue = {0};
    UmiBankStatementRequest request = {0};
    UmiBankStatementResult result = {0};
    UmiBankStatementArchiveSnapshot snapshot = {0};
    UmiBankFeedArchiveInfo info = {0};
    char *encoded = NULL;
    size_t encoded_length = 0U;
    int exit_code = 1;

    REQUIRE(UmiBankFeedCsvCreate(observations, sizeof(observations) - 1U,
                                &feed, &issue) == UMI_STATUS_OK);
    request.account = "lesson-account";
    request.currency = "GBP";
    REQUIRE(UmiBankStatementDate("2026-10-12", &request.firstDate) == UMI_STATUS_OK);
    request.lastDate = request.firstDate;
    REQUIRE(UmiDecimalParse("100.00", 6U, 2U, &request.openingBalance) == UMI_STATUS_OK);
    REQUIRE(UmiDecimalParse("110.25", 6U, 2U, &request.closingBalance) == UMI_STATUS_OK);
    REQUIRE(UmiBankStatementReview(feed, &request, &result) == UMI_STATUS_OK);
    REQUIRE(result.bookedRows == 2U && result.pendingRows == 1U);
    REQUIRE(result.outsidePeriodRows == 1U && result.balancesMatch);
    REQUIRE(money_is(result.credits, "12.50") && money_is(result.debits, "2.25"));
    REQUIRE(money_is(result.netMovement, "10.25"));
    REQUIRE(money_is(result.expectedClosing, "110.25") && money_is(result.difference, "0.00"));
    puts("Booked: 2; pending: 1; outside period: 1.");
    puts("100.00 + 12.50 - 2.25 = 110.25 GBP.");

    /* The source format is known; a digest has not been calculated, so its field
     * stays empty. Never manufacture provenance merely to populate a report. */
    info.sourceFormat = UMI_BANK_FEED_SOURCE_STATEMENT_CSV;
    REQUIRE(UmiBankStatementArchiveCreate(feed, &request, &info, &archive) == UMI_STATUS_OK);
    UmiBankFeedDestroy(feed);
    feed = NULL;
    REQUIRE(UmiBankStatementArchiveEncode(archive, &encoded, &encoded_length) == UMI_STATUS_OK);
    UmiBankStatementArchiveDestroy(archive);
    archive = NULL;
    REQUIRE(UmiBankStatementArchiveDecode(encoded, encoded_length, &reopened) == UMI_STATUS_OK);
    UmiBankFeedArchiveFree(encoded);
    encoded = NULL;
    REQUIRE(UmiBankStatementArchiveRead(reopened, &snapshot) == UMI_STATUS_OK);
    REQUIRE(strcmp(snapshot.account, "lesson-account") == 0 && snapshot.result.balancesMatch);
    REQUIRE(UmiBankStatementArchiveCloneFeed(reopened, &copy) == UMI_STATUS_OK);
    UmiBankStatementArchiveDestroy(reopened);
    reopened = NULL;
    REQUIRE(UmiBankStatementReview(copy, &request, &result) == UMI_STATUS_OK);
    REQUIRE(result.balancesMatch && money_is(result.expectedClosing, "110.25"));
    puts("Reopened review and independent feed retain the same calculation.");

    REQUIRE(UmiDecimalParse("111.25", 6U, 2U, &request.closingBalance) == UMI_STATUS_OK);
    REQUIRE(UmiBankStatementReview(copy, &request, &result) == UMI_STATUS_OK);
    REQUIRE(!result.balancesMatch && money_is(result.difference, "1.00"));
    puts("A supplied closing balance of 111.25 leaves a 1.00 difference.");

    REQUIRE(UmiBankStatementDate("2026-10-13", &request.firstDate) == UMI_STATUS_OK);
    request.lastDate = request.firstDate;
    request.closingBalance = request.openingBalance;
    REQUIRE(UmiBankStatementReview(copy, &request, &result) == UMI_STATUS_OK);
    REQUIRE(result.bookedRows == 0U && result.pendingRows == 0U && result.balancesMatch);
    request.account = "unknown-account";
    result.bookedRows = 73U;
    result.pendingRows = 29U;
    REQUIRE(UmiBankStatementReview(copy, &request, &result) == UMI_STATUS_NOT_FOUND);
    REQUIRE(result.bookedRows == 73U && result.pendingRows == 29U);
    puts("An empty known period differs from an account absent from the import.");

    {
        char damaged[sizeof(observations)];
        char *status = NULL;
        memcpy(damaged, observations, sizeof(observations));
        status = strstr(damaged, "PDNG");
        REQUIRE(status != NULL);
        memcpy(status, "FAIL", 4U);
        REQUIRE(UmiBankFeedCsvCreate(damaged, sizeof(damaged) - 1U,
                                    &rejected, &issue) != UMI_STATUS_OK);
        REQUIRE(rejected == NULL);
        puts("An invalid later row refuses the complete import.");
    }
    puts("An arithmetic match does not prove statement completeness or authenticity.");
    exit_code = 0;
finish:
    UmiBankFeedArchiveFree(encoded);
    UmiBankStatementArchiveDestroy(reopened);
    UmiBankStatementArchiveDestroy(archive);
    UmiBankFeedDestroy(rejected);
    UmiBankFeedDestroy(copy);
    UmiBankFeedDestroy(feed);
    return exit_code;
}
