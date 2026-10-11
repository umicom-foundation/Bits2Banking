/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/checked-money/main.c
 * PURPOSE: Show exact fictional pence transfers with checked C23 arithmetic.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "account.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static void PrintBalance(const char *label, const BtbTrainingAccount *account)
{
    (void)printf("%s: GBP %" PRIu64 ".%02" PRIu64 " (revision %" PRIu64 ")\n",
                 label, account->balancePence / 100U,
                 account->balancePence % 100U, account->revision);
}

int main(void)
{
    BtbTrainingAccount education = {15000U, 0U}; /* £150.00 */
    BtbTrainingAccount materials = {4000U, 0U};  /* £40.00 */
    BtbAccountStatus status = BtbAccountTransfer(&education, &materials, 2500U);
    if (status != BTB_ACCOUNT_OK) {
        (void)fprintf(stderr, "Training transfer rejected: %s\n", BtbAccountStatusText(status));
        return EXIT_FAILURE;
    }
    PrintBalance("Education budget", &education);
    PrintBalance("Materials budget", &materials);
    return EXIT_SUCCESS;
}
