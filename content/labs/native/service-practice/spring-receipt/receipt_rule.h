/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/spring-receipt/receipt_rule.h
 *
 * PURPOSE:
 *   Share fixed-width training rules between native callers and the Spring adapter.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BITSTOBANKING_RECEIPT_RULE_H
#define BITSTOBANKING_RECEIPT_RULE_H

#include <stdint.h>

enum ReceiptDecision {
    RECEIPT_ACCEPT = 0,
    RECEIPT_INVALID = 1,
    RECEIPT_REVIEW = 2
};

/* The JVM adapter publishes these exact values without owning the policy. */
enum ReceiptDecision receipt_decision(int32_t cents, int32_t ceiling);

#endif
