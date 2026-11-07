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

## Summary and limitation

This lesson provides an implementation map and review cases, not a production login server. A stored principal is not an authorisation decision. An in-memory session disappears on process restart unless a separate persistence policy is deliberately supplied.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/session.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Understand local password verification](05-passwords-and-local-profiles.md) · [Next: Keep desktop, mobile and broker identity separate](07-desktop-mobile-and-broker-login.md)
