/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/static-library-map/src/main.c
 * PURPOSE: Link one fictional ledger application against a C23 static library.
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "btb/ledger.h"
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Fictional contributions to the Umicom educational learning fund:
     * GBP 350.00, GBP 149.99 and GBP 4.01. No real money is processed. */
    const uint64_t entries[] = {UINT64_C(35000), UINT64_C(14999), UINT64_C(401)};
    uint64_t total = 0U;
    char output[48];
    if (BtbLedgerTotalPence(entries, sizeof(entries) / sizeof(entries[0]), &total)
            != BTB_LEDGER_OK ||
        BtbLedgerFormatPence(total, output, sizeof(output)) != BTB_LEDGER_OK) {
        fputs("Cannot calculate fictional ledger total.\n", stderr);
        return 1;
    }
    printf("Learning fund total (fictional): %s\n", output);
    return 0;
}
