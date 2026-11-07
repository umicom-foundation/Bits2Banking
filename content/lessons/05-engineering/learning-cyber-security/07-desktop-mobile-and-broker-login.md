<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/07-desktop-mobile-and-broker-login.md

PURPOSE:
Keep desktop, mobile and broker identity separate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep desktop, mobile and broker identity separate

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


## One application can have several identities

A user may unlock a local profile, connect to a remote service and choose a broker account in the same application. These are different events. Their credentials and sessions should not be stored in one undifferentiated “logged in” flag.

A desktop application runs on the user's machine. A mobile application runs on a phone or tablet under that platform's lifecycle and storage rules. A remote API still needs to authenticate and authorise requests from either client. Keeping a button disabled on a phone cannot protect an unguarded server operation.

## Build an identity table

| Identity | What it permits | What it does not establish |
| --- | --- | --- |
| Local profile | Access to the profile's local application state | Broker authentication |
| Web service session | Requests allowed by the server policy | Ownership of every record |
| Broker connection | Operations allowed by the broker and account | Permission to use another environment |
| Guest simulation | Local demonstration workflows | A live market-data subscription |

1. Trace the local-profile functions in Framework.
2. Identify where the application connects to a broker service separately.
3. Label paper and live environments distinctly in your flow diagram.
4. Decide how a disconnect changes displayed state and command availability.

For the TWS socket API path, the user authenticates in TWS or IB Gateway; the client connects to that authenticated application. Do not invent a password-submission method in the socket adapter. Use the broker's documented authentication path for the selected API.

## Mobile lifecycle lab

Write this sequence: open login; start request; put application in background; operating system terminates it; reopen application. Which state is durable? Which token must be revalidated? Which screen may safely show cached data? Mark cached information as such and do not mistake it for a new server response.

## Summary

Use platform-protected secret storage where supported and follow each provider's documented authorisation flow. Avoid putting credentials in project files or screenshots. The local-profile example does not implement mobile secure storage or third-party identity registration; those require their own adapters and verified integration tests.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/local_profile.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Design a web login without confusing sessions and passwords](06-web-login-and-session-boundaries.md) · [Next: Write coding rules that can be checked](08-standards-that-prevent-memory-bugs.md)
