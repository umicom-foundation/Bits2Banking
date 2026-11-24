/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/totp-practice/provider_failure.c
 *
 * PURPOSE:
 *   Show that an interrupted verifier leaves one-time state unchanged.
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

typedef struct PracticeProvider {
    unsigned calls;
} PracticeProvider;

static UmiStatus refuse_second_step(void *opaque, UmiTotpAlgorithm algorithm,
    const uint8_t *secret, size_t secret_size, const uint8_t counter[UMI_TOTP_COUNTER_BYTES],
    uint8_t digest[UMI_TOTP_MAX_DIGEST_BYTES])
{
    /* Interrupt the later operation while reusing the real first calculation. */
    PracticeProvider *const practice = opaque;
    ++practice->calls;
    if (practice->calls == 2U) return UMI_STATUS_UNAVAILABLE;
    return UmiTotpPlatformMac(NULL, algorithm, secret, secret_size, counter, digest);
}

int main(void)
{
    /* The fixed inputs identify an RFC test vector, independent of the clock. */
    static const uint8_t seed[] = "12345678901234567890";
    static const char code[] = "94287082";
    PracticeProvider provider = {0};
    UmiTotpProfile profile = {.algorithm = UMI_TOTP_SHA1, .digits = 8U,
        .mac = refuse_second_step, .mac_context = &provider};
    UmiTotpReplay replay = {.last_step = 0U, .has_last_step = true};
    if (UmiTotpVerify(&profile, seed, sizeof seed - 1U, code, sizeof code - 1U, 59U, &replay) !=
        UMI_STATUS_UNAVAILABLE || provider.calls != 2U || !replay.has_last_step || replay.last_step != 0U) return 1;

    /* Correct the dependency and retry without rebuilding the replay record. */
    profile.mac = UmiTotpPlatformMac;
    profile.mac_context = NULL;
    if (UmiTotpVerify(&profile, seed, sizeof seed - 1U, code, sizeof code - 1U, 59U, &replay) != UMI_STATUS_OK ||
        !replay.has_last_step || replay.last_step != 1U) return 2;
    puts("The interrupted check preserved replay state. The corrected retry consumed step 1.");
    return 0;
}
