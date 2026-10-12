/*
 * Bits2Banking — statement reconciliation lesson
 * Sammy Hegab, Umicom Foundation. MIT.
 * Use the installed Framework to compare invented observations with a balance.
 */
#include "umicom/bank_feed/statement.h"
#include <stdio.h>
#include <string.h>
static const char example[] =
    "{\"Data\":{\"Transaction\":["
    "{\"AccountId\":\"lesson-account\",\"TransactionId\":\"receipt\","
    "\"CreditDebitIndicator\":\"Credit\",\"Status\":\"BOOK\","
    "\"BookingDateTime\":\"2026-10-12T10:00:00Z\","
    "\"Amount\":{\"Amount\":\"12.50\",\"Currency\":\"GBP\"}},"
    "{\"AccountId\":\"lesson-account\",\"TransactionId\":\"payment\","
    "\"CreditDebitIndicator\":\"Debit\",\"Status\":\"BOOK\","
    "\"BookingDateTime\":\"2026-10-12T11:00:00Z\","
    "\"Amount\":{\"Amount\":\"2.25\",\"Currency\":\"GBP\"}},"
    "{\"AccountId\":\"lesson-account\",\"TransactionId\":\"pending\","
    "\"CreditDebitIndicator\":\"Debit\",\"Status\":\"PDNG\","
    "\"BookingDateTime\":\"2026-10-12T12:00:00Z\","
    "\"Amount\":{\"Amount\":\"999.00\",\"Currency\":\"GBP\"}}]}}";
int main(int argc, char **argv) {
  if (argc > 2) {
    fprintf(stderr, "Usage: statement-reconciliation [reported-closing]\n");
    return 2;
  }
  const char *closing = argc == 2 ? argv[1] : "110.25";
  UmiBankStatementRequest request = {"lesson-account", "GBP",
                                     {2026, 10, 12},   {2026, 10, 12},
                                     {10000, 2},       {0, 2}};
  /* The lesson deliberately fixes two decimal places. Real applications may
   * accept another explicit scale, but should never round silently. */
  UmiStatus status =
      UmiDecimalParse(closing, strlen(closing), 2, &request.closingBalance);
  UmiBankFeed *feed = NULL;
  if (status == UMI_STATUS_OK)
    status = UmiBankFeedCreate(example, sizeof example - 1U, &feed);
  UmiBankStatementResult result;
  if (status == UMI_STATUS_OK)
    status = UmiBankStatementReview(feed, &request, &result);
  char expected[UMI_DECIMAL_TEXT_MAX], difference[UMI_DECIMAL_TEXT_MAX];
  if (status == UMI_STATUS_OK)
    status =
        UmiDecimalFormat(result.expectedClosing, expected, sizeof expected);
  if (status == UMI_STATUS_OK)
    status = UmiDecimalFormat(result.difference, difference, sizeof difference);
  /* The result contains values, not pointers into the feed. It remains valid
   * after destruction, making ownership easy to follow and extend. */
  UmiBankFeedDestroy(feed);
  if (status != UMI_STATUS_OK) {
    fprintf(stderr, "Comparison failed: %s\n", umi_status_text(status));
    return 1;
  }
  printf(
      "Expected closing: %s\nDifference: %s\nPending entries excluded: %zu\n",
      expected, difference, result.pendingRows);
  puts("Arithmetic comparison only; completeness and authenticity remain "
       "unverified.");
  return 0;
}
