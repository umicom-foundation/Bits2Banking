/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/totp-practice/replay.c
 *
 * PURPOSE:
 *   Verify a public authenticator code and distinguish window and replay refusal.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/security/totp.h"
#include <stdio.h>

int main(void)
{
    /* RFC 6238 uses publicly published input here instead of account data. */
    static const uint8_t seed[] = "12345678901234567890";
    static const char code[] = "94287082";
    const UmiTotpProfile profile = {.algorithm = UMI_TOTP_SHA1, .digits = 8U,
        .mac = UmiTotpPlatformMac};
    UmiTotpReplay used = {0};

    /* At 59 seconds the public code belongs to time step 1. */
    if (UmiTotpVerify(&profile, seed, sizeof seed - 1U, code, sizeof code - 1U, 59U, &used) != UMI_STATUS_OK ||
        !used.has_last_step || used.last_step != 1U) return 1;
    if (UmiTotpVerify(&profile, seed, sizeof seed - 1U, code, sizeof code - 1U, 60U, &used) !=
        UMI_STATUS_PERMISSION_DENIED || used.last_step != 1U) return 2;

    /* An independent example shows the previous step is still in the window. */
    UmiTotpReplay fresh = {0};
    if (UmiTotpVerify(&profile, seed, sizeof seed - 1U, code, sizeof code - 1U, 60U, &fresh) != UMI_STATUS_OK ||
        !fresh.has_last_step || fresh.last_step != 1U) return 3;
    UmiTotpReplay expired = {0};
    if (UmiTotpVerify(&profile, seed, sizeof seed - 1U, code, sizeof code - 1U, 90U, &expired) !=
        UMI_STATUS_PERMISSION_DENIED || expired.has_last_step) return 4;

    puts("Accepted step 1 once. The replay and expired code were refused.");
    return 0;
}
