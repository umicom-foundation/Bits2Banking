/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/totp-practice/enrollment.c
 *
 * PURPOSE:
 *   Inspect public enrollment URI fields while keeping current output on refusal.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/security/secrets.h"
#include "umicom/security/totp_enrollment.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Use a public fixture and exercise capacity with a visibly prior value. */
    static const uint8_t seed[] = "12345678901234567890";
    char old[8] = "keep";
    size_t old_size = 4U;
    if (UmiTotpBuildEnrollmentUri("Practice Library", "student@example.invalid", UMI_TOTP_SHA1,
        8U, seed, sizeof seed - 1U, old, sizeof old, &old_size) != UMI_STATUS_CAPACITY_EXCEEDED ||
        strcmp(old, "keep") != 0 || old_size != 4U) return 1;

    char uri[UMI_TOTP_ENROLLMENT_URI_CAPACITY] = {0};
    size_t written = 0U;
    const UmiStatus status = UmiTotpBuildEnrollmentUri("Practice Library", "student@example.invalid",
        UMI_TOTP_SHA1, 8U, seed, sizeof seed - 1U, uri, sizeof uri, &written);
    /* Inspect the expected label and policy without printing the shared secret. */
    const bool complete = status == UMI_STATUS_OK && written == strlen(uri) &&
        strstr(uri, "otpauth://totp/Practice%20Library:student%40example.invalid?") == uri &&
        strstr(uri, "&issuer=Practice%20Library&algorithm=SHA1&digits=8&period=30") != NULL;
    umi_secret_clear(uri, sizeof uri);
    if (!complete) return 2;
    /* Check the whole buffer, including storage past the formatted result. */
    for (size_t i = 0U; i < sizeof uri; ++i) {
        if (uri[i] != '\0') return 3;
    }
    puts("The full URI fit and was cleared. The undersized output stayed intact.");
    return 0;
}
