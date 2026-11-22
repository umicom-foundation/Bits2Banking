<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/open-banking-account-access/03-check-consent-in-c.md

PURPOSE:
Check client, account, permission, active state and expiry before offering a local account projection.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Check the Trusted Consent in C23

[Course contents](index.md) · [Previous lesson · Request a Minimal Account View](02-request-a-minimal-account-view.md)

Check client, account, permission, active state and expiry before offering a local account projection.

## Name the trusted inputs

This function consumes IDs and flags supplied by a trusted practice fixture. A production adapter would authenticate the caller and bind its identity to the consent in a trusted store. This function owns the smaller business decision about permission and the requested account. The ticks below are classroom clock values from one trusted test clock.

~~~c
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum { READ_BASIC = 1u };
struct Consent { unsigned client; unsigned account; unsigned permissions;
                 uint64_t until; bool active; };
struct Request { unsigned client; unsigned account; uint64_t now;
                 bool authenticated; };

static bool permit_basic(struct Consent grant, struct Request request)
{
    // Every condition belongs to this specific read operation.
    return request.authenticated && grant.active &&
           request.client == grant.client && request.account == grant.account &&
           (grant.permissions & READ_BASIC) != 0u && request.now < grant.until;
}

int main(void)
{
    struct Consent approved = {10, 2, READ_BASIC, 200, true};
    const struct Request right_account = {10, 2, 199, true};
    const struct Request another_account = {10, 3, 199, true};
    const struct Request expired = {10, 2, 200, true};
    const struct Request other_client = {11, 2, 199, true};
    const struct Request unauthenticated = {10, 2, 199, false};
    assert(permit_basic(approved, right_account));
    assert(!permit_basic(approved, another_account));
    assert(!permit_basic(approved, expired));
    assert(!permit_basic(approved, other_client));
    assert(!permit_basic(approved, unauthenticated));
    approved.permissions = 0;
    assert(!permit_basic(approved, right_account));
    approved.permissions = READ_BASIC;
    approved.active = false;
    assert(!permit_basic(approved, right_account));
    puts("one account projection permitted");
    return 0;
}
~~~

1. Copy into consent_read.c and keep assert checks enabled. Follow the first request by marking each true condition.
2. With a C23 compiler, run the commands shown. On Windows a configured GCC toolchain can write consent-read.exe, invoked as .\consent-read.exe in PowerShell.
3. Set the trusted request time to 201. Check the denial by hand. In an application, keep the account store untouched for a denied read.

~~~text
cc -std=c23 -Wall -Wextra -pedantic consent_read.c -o consent-read
./consent-read
Expected: one account projection permitted
~~~

## Compare the expiry rule in FreeBASIC

ULongInt holds an unsigned whole number. This function models the time boundary. On paper, call it with 199 and 200, then with 200 and 200.

~~~freebasic
Function IsBeforeExpiry(ByVal currentTick As ULongInt, _
                        ByVal expiryTick As ULongInt) As Integer
    If currentTick < expiryTick Then Return 1
    Return 0
End Function
~~~

For the Umicom Bank read view, design a test that confirms a denied read returns no account projection. Keep the authorised protocol adapter and the native Bank data policy at separate boundaries.

- [Build a banking application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Open Banking Limited v4.0.1 Account and Transaction API Profile](https://openbankinguk.github.io/read-write-api-site3/v4.0.1/profiles/account-and-transaction-api-profile.html)

[Browser edition](../../../courses/open-banking-account-access/lessons/03-check-consent-in-c.html)

