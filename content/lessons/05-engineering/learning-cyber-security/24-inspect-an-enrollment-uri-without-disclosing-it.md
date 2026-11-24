<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/24-inspect-an-enrollment-uri-without-disclosing-it.md

PURPOSE:
Inspect an enrollment URI without disclosing it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Inspect an enrollment URI without disclosing it

During enrollment, an authenticator and the account service learn the same seed. An enrollment URI is a small text address that contains that seed and also tells the app which algorithm, number of digits and time period to use. Treat the entire URI as secret when using a real account.

## Read regular fields without displaying the seed

The practice C example uses a published seed and fictitious labels. `UmiTotpBuildEnrollmentUri` writes the issuer, account label and settings into the output only when the whole address fits. A space becomes `%20` and the at sign becomes `%40`. These encodings protect the field boundaries. The result’s size counts bytes before the final zero terminator.

A program can check whether expected labels and settings appear in the result without printing it. The class example verifies those fields and then clears the entire temporary array with Framework’s `umi_secret_clear`. The same application should keep the URI out of test logs, status reports and screenshots when enrolling a real account.

## Prove that an insufficient output stays usable

1. Open `labs/framework/totp-practice/enrollment.c`. Find the short prior string `keep` and its saved length of four.
2. Follow the course’s source checkout build steps and select `enrollment`. The first attempt deliberately provides too little room. The function should report capacity and preserve the string and length.
3. Watch the ordinary attempt use a buffer large enough for the complete result. The test checks the actual count and clears the result before printing `The full URI fit and was cleared. The undersized output stayed intact.`

The address is only one stage of enrollment. A real local profile should remain pending until the first code and account binding have been checked. Apply this rule in Umicom Bank, Studio, or a WebServer-backed interface through the shared Framework services. The practice case creates no credential or account. [RFC 4648 Base32](https://www.rfc-editor.org/rfc/rfc4648.html#section-6)

## Build from a Framework source checkout

This exercise can use the shared URI formatter independently of the Windows authenticator provider. Open PowerShell with GCC, CMake and Ninja available. Confirm the Framework and course folders match the paths in these commands. Run the commands separately and stop if a command fails.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/framework/totp-practice -B build/totp-practice -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/totp-practice --target totp-practice-enrollment
ctest --test-dir build/totp-practice -R "^lesson[.]totp[.]enrollment$" -V --no-tests=error
~~~

Expect one passing test. Use a separate directory for Clang. For an existing installed SDK, omit the source option, point `CMAKE_PREFIX_PATH` to that SDK, and configure a fresh build directory. The exercise requests the shared `security` component.

## Read the C entry point

~~~c
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
~~~

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Preserve replay state after provider failure](23-preserve-replay-state-after-provider-failure.md) · [HTML edition](../../../courses/learning-cyber-security/lessons/24-inspect-an-enrollment-uri-without-disclosing-it.html)
