<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/22-verify-an-unused-authenticator-step.md

PURPOSE:
Verify an unused authenticator step

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Verify an unused authenticator step

A password and an authenticator code answer two different questions in a sign-in workflow. The password check comes first. The authenticator check then verifies a decimal code for the account’s registered seed and expected time step. Keep the two results separate until both checks succeed.

## Follow the time window

The practice application uses Framework’s `UmiTotpVerify`. A **time step** is a numbered interval of 30 seconds, starting at the reference time. At 59 seconds the current step is 1. At 60 seconds the current step is 2 and the previous step is 1. At 90 seconds step 1 is outside the current and previous pair.

| Time in seconds | Current step | Previous step | Where step 1 falls |
| --- | --- | --- | --- |
| 59 | 1 | 0 | Current |
| 60 | 2 | 1 | Previous |
| 90 | 3 | 2 | Outside the window |

Authenticators sometimes show the old code just as a new window begins. Framework’s previous-step allowance covers that boundary. A **replay record** keeps the latest accepted step for the credential. If the account already used step 1, its code is refused at 60 seconds even though the window still admits that step. An independent practice record without the prior use can accept it there.

## Run the C example

Use a public RFC 6238 test seed and code. Open `labs/framework/totp-practice/replay.c`. Find the current acceptance, the repeat refusal, the independently valid previous step and the expired step. The tests supply time explicitly so results do not depend on your clock.

Use the source checkout procedure in this section, then run the `replay` case. It prints `Accepted step 1 once. The replay and expired code were refused.` This practice target uses Windows CNG through the existing Framework MAC callback. The native verifier target consumes the code as counted text. The number of digits is important because an authenticator can show a leading zero.

## Connect to Umicom applications

Umicom Bank and Studio can require the same Framework verifier for applicable sign-in workflows. The application should give the service the credential and its current replay state. The complete sign-in path also needs to persist the accepted step for that credential before issuing a session. This example uses only in-memory practice records.

If a code fails, diagnose its clock window separately from prior use. Never mark a code as accepted merely because its digits have the correct length. [RFC 6238 validation and test vectors](https://www.rfc-editor.org/rfc/rfc6238.html)

## Build from a Framework source checkout

This exercise selects the native Windows CNG provider. Use Windows and a C23 toolchain for this case. Open PowerShell with GCC, CMake and Ninja available. Confirm the Framework and course folders match the paths in these commands. Run the commands separately and stop if a command fails.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/framework/totp-practice -B build/totp-practice -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/totp-practice --target totp-practice-replay
ctest --test-dir build/totp-practice -R "^lesson[.]totp[.]replay$" -V --no-tests=error
~~~

Expect one passing test. Use a separate directory for Clang. For an existing installed SDK, omit the source option, point `CMAKE_PREFIX_PATH` to that SDK, and configure a fresh build directory. The exercise requests the shared `security` component.

## Read the C entry point

~~~c
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
~~~

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Keep revision exhaustion from partly changing an identity](21-revisions-and-all-or-nothing-edits.md) · [Next: Preserve replay state after provider failure](23-preserve-replay-state-after-provider-failure.md) · [HTML edition](../../../courses/learning-cyber-security/lessons/22-verify-an-unused-authenticator-step.html)
