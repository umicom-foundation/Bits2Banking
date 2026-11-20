<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/06-web-login-and-session-boundaries.md

PURPOSE:
Design a web login without confusing sessions and passwords

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Design a web login without confusing sessions and passwords

Learn how application inputs, memory ownership and identity checks fit together. The examples use Umicom Framework and a small Bits2Banking consumer. Every chapter explains its vocabulary before the exercise.

## Start here

A source file is readable program text. A compiler turns that text into machine instructions. A library supplies reusable functions; this course calls the security library in Umicom Framework. A terminal accepts commands. You can read and trace every example without installing anything.

For the practical lab, install Git, a C23 compiler, CMake 3.26 or newer, Ninja, and a matching Framework SDK containing UmiLocalProfileNameBytes. In Windows PowerShell, open the repository with Set-Location and make the UCRT64 tools visible:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/profile-name-boundary -B build/profile-name -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build/profile-name
ctest --test-dir build/profile-name --output-on-failure --no-tests=error
& ".\build\profile-name\btb-profile-name.exe"
~~~

Run one command at a time and stop on an error. Change the SDK path to your installation. In bash, use cd to enter your checkout, the same three CMake/CTest commands, and ./build/profile-name/btb-profile-name to launch. The expected line is Canonical name: alice_7. A missing package means the SDK path is wrong or incomplete; a missing symbol means its header and library must be updated together. This lab does not collect credentials or write a password store. The [Learning C course](../../../courses/learning-c/index.html) explains basic syntax in more depth.


## What a web session represents

A browser sends separate requests. A session lets a server associate later requests with an earlier successful authentication. A session token is a secret identifier, not the password itself. Anyone holding a usable bearer token may be able to act as its owner.

Framework's UmiWebSession structure contains an identifier, a principal, creation and expiry times, and an active flag. A principal is the identity represented by the session. The in-memory store exposes put, get and revoke operations. These storage operations do not themselves verify a password, issue a random token, configure HTTPS or implement a complete login endpoint.

## Design the request journey

~~~text
browser submits credentials over HTTPS
server verifies credentials and applies attempt controls
server creates a fresh unpredictable session token
server sends a protected cookie
later request presents cookie
server checks session validity AND action permission
~~~

1. Draw one box for credential verification and another for session storage.
2. Add an expiry check on every protected request.
3. Add session revocation when the user logs out.
4. Add a permission check for the requested record or action.

Cookies normally need Secure and HttpOnly attributes and an appropriate SameSite policy. State-changing browser requests also need a considered cross-site-request-forgery defence. Token generation, renewal and expiry must follow a reviewed design. Read the [OWASP session-management guidance](https://cheatsheetseries.owasp.org/cheatsheets/Session_Management_Cheat_Sheet.html) before implementing a public service.

## Paper lab

Create a table with rows “no token”, “expired token”, “revoked token”, “valid token, wrong record owner”, and “valid token, allowed action”. Only the final row should perform the action. Decide what response the user sees without exposing sensitive internal details.

For registration, also plan duplicate-name handling, account recovery, verification of contact details when required, and abuse controls. Do not use the desktop credential vault as a multi-user web account database without a separate server architecture.

## Check that account-wide sign-out took effect

The Framework authenticated registry in `umicom/security/session.h` issues opaque handles after the host has authenticated the account. After authorizing an account-wide sign-out, call `umi_session_registry_revoke_principal`. It marks every active session for that exact principal inactive under one lock. A lock gives one operation exclusive access while it finishes the change. A repeat request succeeds and reports zero new revocations.

The Framework UAT exercise creates two sessions for a fixture account and one for a different account. It confirms that both sessions for the first account are refused and that the other account retains its session. A second case checks that the report keeps an assertion failure even when cleanup succeeds. The fixture owns only an in-memory registry.

From a Framework source checkout with a C23 compiler, CMake and Ninja on `PATH`, run each command in order and stop if any command fails.

```powershell
cmake -S tests/uat -B build/session-policy -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/session-policy --target umicom-uat-session-policy-tests
ctest --test-dir build/session-policy --output-on-failure --no-tests=error -R '^framework[.]uat[.]session_policy[.]'
```

Expect two passing regression cases. If CTest finds no matches, check that the source checkout contains `tests/uat/test_session_policy.c`. The `UmiWebSessionStore` can separately hold view state, such as a draft form or a dashboard selection. Use its time bounds and `umi_web_session_prune` to retire expired state. Keep protected actions tied to the authenticated registry and the current access policy.

## Pair an authenticator with an account

1. Ask the signed-in account holder to confirm their first factor. Generate a
   new secret with the platform's secure random source and keep the pending
   enrollment tied to that account.
2. Use Framework's `UmiTotpBuildEnrollmentUri` with your issuer name, the
   account label, algorithm and digit count. Its Key URI gives the
   authenticator the shared secret in Base32. Percent encoding keeps spaces,
   punctuation and international names inside their intended URI fields.
3. Show the enrollment only to the account holder. Enter a code from the
   authenticator and verify it with the same algorithm and digit count.
   Activate the credential and its replay record only after that check.
   Clear the temporary URI when enrollment ends.

The URI carries the same secret as the credential. Keep it out of logs and
support screenshots. An authenticator may support fewer profiles than the
server. Check the first code with the configured profile before beginning a
sign-in test.

To practice with published fixture keys, build
`umicom-totp-enrollment-test` and run `ctest -R '^framework[.]totp_enrollment[.]'`
from the configured Framework build directory. Compare the issuer and
account in the test with the URI and find the stated time step. The Windows
provider check decodes the staged secret and verifies a published code.
[RFC 4648 Base32](https://www.rfc-editor.org/rfc/rfc4648.html#section-6)
[Authenticator Key URI format](https://github.com/google/google-authenticator/wiki/Key-Uri-Format)

## Verify a time-based authenticator code

A time-based one-time password (TOTP) combines the credential's shared secret
with the current time step to produce a short decimal code. The phone and
server agree on the algorithm, digit count and 30-second step. The incoming
code is text, so a leading zero is part of the value the person enters.

Framework's `UmiTotpVerify` supports six or eight digits, SHA-1 or SHA-256,
and the current or immediately previous step. It rejects a code from a step
already consumed for that credential. On Windows, `UmiTotpPlatformMac`
supplies the keyed hash through Windows CNG. The standard defines the
truncation and includes public test vectors. [RFC 6238](https://www.rfc-editor.org/rfc/rfc6238.html)

1. Check the first authentication factor and limit attempts before accepting a code.
2. Use the enrolled credential's recorded algorithm and digits. Read its secret from protected storage.
3. Hold one per-credential transaction while reading the last step and calling the verifier.
4. Commit the accepted step before creating the authenticated session. An unsuccessful commit leaves the session unissued.

For the lab, use the public vector tests supplied in Framework. Run these
commands from its Windows source checkout after configuring the
`windows-ucrt64-debug` preset.

```powershell
cmake --build --preset windows-ucrt64-debug --target umicom-security-totp-tests
ctest --test-dir build/windows-ucrt64-debug --output-on-failure --no-tests=error -R '^framework[.]security_totp[.]'
```

The cases exercise the published codes, clock boundaries, conflicting replay
and a failing cryptographic provider. Enrolment, recovery and app sign-in
require their own checks. A credential's shared secret and accepted codes
belong outside screenshots, reports and application logs.

## Compose both factors before issuing a session

Use `UmiLocalProfileMfaSignIn` where an application requires both a local
password and an enrolled authenticator. It checks the password before opening
the authenticator credential for the same canonical profile. A canonical
profile has one spelling, so `Classroom` and `classroom` resolve to the same
verified local account.

1. Return the active authenticator's revision and saved replay position from
   a secure backend. A revision identifies one enrolled version of the
   credential. Store the shared key separately from logs and editable project
   files.
2. In the backend, compare the prior replay position and the active
   credential revision in the same durable transaction. If another sign-in
   consumes the step or the credential changes, refuse the commit.
3. Grant the existing Framework session only after that commit succeeds.
   If session issuance fails after the commit, wait for the next code. The
   accepted step has already been consumed.

From the Framework source folder, configure and run the isolated cases.

```powershell
$mfaBuild = Join-Path $PWD 'build/local-mfa-check'
cmake -S tests/local_mfa -B $mfaBuild -G Ninja
cmake --build $mfaBuild
ctest --test-dir $mfaBuild --output-on-failure --no-tests=error -R '^framework[.]local_profile_mfa[.]'
```

Expect 13 cases. Start with `sign-in` and `rotation`. A correct code issues a
session for the canonical profile after one replay write. A credential that
rotates before the write produces a refusal and a fresh sign-in is required.
Then run `registry-full` to see the consumed step survive a failed session
issue. The fixture uses a disposable password store. On Windows it checks the
published authenticator vector through CNG. A product supplies its own secure
credential backend, rate limits, enrolment, recovery and first sign-in tests.

## Confirm an authenticator before activating it

Use `UmiLocalProfileMfaConfirmEnrollment` when the user returns a code after
adding a pending credential to an authenticator. The backend owns the pending
key, its expiration time and the revision the application showed to the user.

1. Verify the password before reading the pending key. Match the requested
   revision to the one actually stored and check its expiration.
2. Verify the code with the pending key. The confirmation records the accepted
   time step so a subsequent sign-in must use a later code.
3. In one durable operation, compare both the pending revision and the active
   credential revision observed when enrolment began. Activate the new
   credential with its saved time step and remove the pending record.

Run the confirmation cases in the same configured directory.

```powershell
ctest --test-dir $mfaBuild --output-on-failure --no-tests=error -R '^framework[.]local_profile_mfa_enrollment[.]'
```

Expect 14 cases. The confirmation and sign-in case refuses the already
accepted code and accepts a later published test vector. The conflict cases
change the pending or active revision just before writing and preserve
the current credential. On a stale revision, reload the enrolment view and
have the user confirm the current attempt.

## Summary and limitation

This lesson provides an implementation map and review cases, not a production login server. A stored principal is not an authorisation decision. An in-memory session disappears on process restart unless a separate persistence policy is deliberately supplied.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/session.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Understand local password verification](05-passwords-and-local-profiles.md) · [Next: Keep desktop, mobile and broker identity separate](07-desktop-mobile-and-broker-login.md)
