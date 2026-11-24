<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/23-preserve-replay-state-after-provider-failure.md

PURPOSE:
Preserve replay state after provider failure

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Preserve replay state after provider failure

Verification can fail because a code does not match, or because the provider could not finish the calculation. A sign-in workflow needs both facts available so its developer can diagnose the system. It can still report a general refusal to the person trying to sign in.

## Use a controlled interruption

The `provider_failure.c` practice program first verifies the current step using the existing Windows CNG callback. A **callback** is a function that a service can invoke when it needs work from another component. The practice callback calls the actual provider on its first invocation and reports `UMI_STATUS_UNAVAILABLE` on the second invocation. This makes the later step fail predictably even though the first calculation succeeded.

The test starts with an already consumed step 0 and checks both the saved flag and number. Framework examines the admitted time window before publishing a new accepted step. The interrupted attempt preserves step 0. Replacing the practice callback with the usual provider lets the retry consume step 1.

~~~text
READ the previous replay record
CHECK each step required by the verifier
IF a provider cannot finish
    KEEP the previous record and refuse this attempt
IF the code is valid and the step is unused
    PUBLISH the accepted step
~~~

## Build and observe the case

Use the source checkout commands in this section and select `provider_failure`. Read the callback count and the replay checks in `labs/framework/totp-practice/provider_failure.c` before running it. Expect `The interrupted check preserved replay state. The corrected retry consumed step 1.`

If the case reports unavailable after the corrected retry, check that the Windows CNG provider is available to the test process. Look at its origin and status in the local test output. The practice callback should be selected only for the first attempt. A provider fault cannot authorize a new session.

In a Bank sign-in handler, persist the accepted replay step through the credential store's normal transaction. The application can issue a session only after that transaction and the preceding factors succeed. The lesson demonstrates the verification part with local test data.

## Build from a Framework source checkout

This exercise selects the native Windows CNG provider. Use Windows and a C23 toolchain for this case. Open PowerShell with GCC, CMake and Ninja available. Confirm the Framework and course folders match the paths in these commands. Run the commands separately and stop if a command fails.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/framework/totp-practice -B build/totp-practice -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/totp-practice --target totp-practice-provider_failure
ctest --test-dir build/totp-practice -R "^lesson[.]totp[.]provider_failure$" -V --no-tests=error
~~~

Expect one passing test. Use a separate directory for Clang. For an existing installed SDK, omit the source option, point `CMAKE_PREFIX_PATH` to that SDK, and configure a fresh build directory. The exercise requests the shared `security` component.

## Read the C entry point

~~~c
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
~~~

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Verify an unused authenticator step](22-verify-an-unused-authenticator-step.md) · [Next: Inspect an enrollment URI without disclosing it](24-inspect-an-enrollment-uri-without-disclosing-it.md) · [HTML edition](../../../courses/learning-cyber-security/lessons/23-preserve-replay-state-after-provider-failure.html)
