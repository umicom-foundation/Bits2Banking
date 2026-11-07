<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/16-design-registration-and-web-login.md

PURPOSE:
Plan registration and web login around trusted services

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan registration and web login around trusted services

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## Begin with a flow

Registration creates an account according to a policy. Login checks evidence for an existing account. A session links later requests to the authenticated identity. These are related operations with different failure cases.

For a first design, draw:

```text
registration form -> validated request -> identity provider -> account result
login form -> authentication provider -> verified identity -> session
request + session -> current policy -> protected operation
```

An arrow represents a message. Label which component owns each piece of data and where it crosses from a user's device to a service.

## Registration steps

1. Choose the identity provider and the fields genuinely needed.
2. Validate field shape and size before parsing or storage.
3. Apply uniqueness and verification rules at the authoritative service.
4. Return a useful result without disclosing another person's private account details.
5. Record an audit event without passwords, verification codes or session handles.

If the service owns passwords, use a reviewed password-hashing library and a deployment-specific policy. Ordinary fast hashes are not a substitute for password hashing. See the [OWASP password storage guidance](https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html).

## Browser adapter

The browser sends requests over HTTPS. The host establishes and checks the session; client-side state alone is insufficient. Cookie transport needs appropriate Secure, HttpOnly and SameSite settings, with CSRF protection designed for the application's request flows. See [OWASP session management](https://cheatsheetseries.owasp.org/cheatsheets/Session_Management_Cheat_Sheet.html).

## Connect this to Framework

The lab's `register` calls demonstrate metadata admission, not a complete registration endpoint. Keep reusable validation, identity and session logic in Framework. Add the selected provider and HTTP adapter only with a clear contract and meaningful integration tests.

## Exercise

List expected outcomes for malformed input, a duplicate registration, failed verification, unavailable provider and a successful login. For each, state whether any identity or session record may be created. Do not implement a fallback that treats provider failure as success.

## Read the source

[Open the example source](../../../../labs/framework/identity-lifecycle/README.md).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Test expiry, logout and cleanup precisely](15-expiry-logout-and-cleanup.md) · [Next: Use the same security boundary from desktop and mobile](17-desktop-and-mobile-sign-in.md)
