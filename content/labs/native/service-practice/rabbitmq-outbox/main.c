/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/rabbitmq-outbox/main.c
 *
 * PURPOSE:
 *   Model when a durable outbox event is ready to be marked as sent.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>

enum SendEvidence {
    SEND_UNKNOWN,
    SEND_NACKED,
    SEND_RETURNED,
    SEND_CONFIRMED_ROUTABLE
};

static bool may_mark_sent(bool ledger_committed, enum SendEvidence evidence)
{
    // A durable row can be marked only after its send has been correlated.
    return ledger_committed && evidence == SEND_CONFIRMED_ROUTABLE;
}

int main(void)
{
    // Unknown covers a disconnect before the publisher obtained a result.
    if (may_mark_sent(false, SEND_CONFIRMED_ROUTABLE) ||
        may_mark_sent(true, SEND_UNKNOWN) ||
        may_mark_sent(true, SEND_NACKED) ||
        may_mark_sent(true, SEND_RETURNED) ||
        !may_mark_sent(true, SEND_CONFIRMED_ROUTABLE)) {
        fputs("outbox evidence mismatch\n", stderr);
        return 1;
    }
    puts("outbox evidence checks ready");
    return 0;
}
