/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/bounded-ledger-line/main.c
 * PURPOSE: Decode a fictional account change without using NUL-terminated input.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "ledger_line.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    const unsigned char message[] = {'1', '0', '0', '1', ':', '+', '2', '5', '0', '0'};
    BtbLedgerRow row = {0};
    if (BtbLedgerLineParse(message, sizeof(message), &row) != BTB_LEDGER_OK)
        return 1;
    (void)printf("Training account %" PRIu32 ": change %+" PRId64 " pence\n",
                 row.accountId, row.changePence);
    return 0;
}
