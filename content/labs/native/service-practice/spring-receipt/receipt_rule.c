/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/spring-receipt/receipt_rule.c
 *
 * PURPOSE:
 *   Decide whether a fictional receipt is within a training limit.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "receipt_rule.h"

enum ReceiptDecision receipt_decision(int32_t cents, int32_t ceiling)
{
    /* Refuse a nonpositive configuration before comparing a receipt with it. */
    if (cents <= 0 || ceiling <= 0) {
        return RECEIPT_INVALID;
    }

    /* The ceiling is inclusive, so exactly the configured amount is accepted. */
    return cents > ceiling ? RECEIPT_REVIEW : RECEIPT_ACCEPT;
}
