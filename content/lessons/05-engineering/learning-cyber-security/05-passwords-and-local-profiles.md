<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/05-passwords-and-local-profiles.md

PURPOSE:
Understand local password verification

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand local password verification

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


## Authentication is evidence of identity

Registration creates an identity record. Authentication checks evidence that a caller controls that identity. Authorisation decides what that identity may do. These are separate responsibilities.

A password verifier is a value derived from a password using a deliberately expensive password-hashing process. A salt is random input that makes separately created records differ even when their passwords match. A plain fast checksum is not a suitable password-storage scheme. See the [OWASP password-storage guidance](https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html).

## Inspect the local-profile service

1. Read UmiLocalProfileRecord. It contains a version, iteration count, salt and verifier.
2. Follow Register: validate inputs, check whether a record exists, obtain random bytes, derive a verifier and create the record.
3. Follow Verify: load the record, check its supported version and parameters, derive a candidate verifier and compare it.
4. Find umi_secret_clear calls on temporary records and derived bytes.

The production backend contract uses PBKDF2-HMAC-SHA256 and operating-system randomness. The current Windows adapter uses the user's credential vault. The header explicitly says unavailable platforms return UNAVAILABLE instead of storing plaintext. Do not turn that result into an unencrypted fallback.

## Tests are not cryptography

FixtureDerive in the test fixture is deliberately cheap, deterministic and non-cryptographic. It lets tests exercise duplicate registration, read failures and removal conflicts. It must never be copied into a real login backend. Passing those tests establishes policy behaviour only; it does not certify the platform vault or password algorithm.

## Password handling exercise

Write a data-flow list for a password: input control -> temporary owned buffer -> synchronous verification -> buffer clearing. Keep it out of logs, exception text and filenames. The service's input buffer belongs to its caller; the caller must clear and release it after verification. Expensive verification belongs off the GUI thread so the window can remain responsive.

## Summary

Use an established password-storage implementation. Keep verification separate from account permissions. A local Umicom profile is not an IBKR login or a banking-server identity, and it does not grant those systems' permissions.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/security/local_profile.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Keep failed input from changing valid state](04-validate-before-publishing-state.md) · [Next: Design a web login without confusing sessions and passwords](06-web-login-and-session-boundaries.md)
