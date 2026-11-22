/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/spring-receipt/main.c
 *
 * PURPOSE:
 *   Check the native receipt rule before connecting it to any Java host.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "receipt_rule.h"
#include <stdio.h>

int main(void)
{
    /* Fix the units and boundary values so the tests can be traced on paper. */
    const int32_t ceiling = INT32_C(20000);
    if (receipt_decision(10000, ceiling) != RECEIPT_ACCEPT ||
        receipt_decision(ceiling, ceiling) != RECEIPT_ACCEPT ||
        receipt_decision(0, ceiling) != RECEIPT_INVALID ||
        receipt_decision(10000, 0) != RECEIPT_INVALID ||
        receipt_decision(20001, ceiling) != RECEIPT_REVIEW) {
        fputs("receipt rule mismatch\n", stderr);
        return 1;
    }

    puts("receipt rules ready");
    return 0;
}
