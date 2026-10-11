/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/binary-payment-records/main.c
 * PURPOSE: Display an encoded simulated payment record for learning purposes.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "record.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const BtbPaymentRecord payment = {27U, 125000U, {'G', 'B', 'P'}, 1U};
    unsigned char bytes[BTB_PAYMENT_RECORD_SIZE] = {0};
    size_t written = 0U;
    if (BtbEncodeRecord(&payment, bytes, sizeof(bytes), &written) != BTB_RECORD_OK)
        return EXIT_FAILURE;
    puts("Simulated record bytes (network order):");
    for (size_t i = 0U; i < written; ++i)
        printf("%02X%s", (unsigned)bytes[i], i + 1U == written ? "\n" : " ");
    puts("No payment has been sent, stored or authorised.");
    return EXIT_SUCCESS;
}
