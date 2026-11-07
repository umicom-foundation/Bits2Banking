<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/15-expiry-logout-and-cleanup.md

PURPOSE:
Test expiry, logout and cleanup precisely

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test expiry, logout and cleanup precisely

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## The exact boundary

If a session is issued at 200 with lifetime 50, its expiration is 250. Validation at 249 can succeed; validation at 250 must fail. Writing down the equality case prevents a common off-by-one error.

The Framework rejects an expiration addition that cannot fit its unsigned integer. It also refuses observations before issuance or before the previous successful observation. The host remains responsible for supplying a suitable trusted clock.

## Work through three operations

`validate` checks a handle and updates its last-seen value on success. `revoke` marks an existing session inactive. `cleanup` removes inactive or expired records from the bounded collection.

Logout should revoke the server-side session before clearing the client view. Closing a window alone does not necessarily revoke a remote session.

1. Run the unmodified local lab.
2. Read the validation calls at 249 and 250.
3. Add an observation at 251 and require refusal.
4. Check the output record remains unchanged after each failed validation.
5. Inspect the cleanup count. The earlier revoked session and the newly expired session are both removed.

## Capacity is a resource limit

A bounded registry has a maximum number of records. Cleanup makes room by removing retired records; it does not extend an active session's lifetime. Applications need a deliberate cleanup policy and useful handling of capacity failures.

## Do not reuse stale positions

Cleanup may compact the internal collection. A row index is not a durable identity. Keep the opaque handle when a handle is needed and use the registry API rather than retaining pointers into private storage.

## Exercise

Draw a timeline with issuance, successful request, logout and an attempted request after logout. Label the expected result at each point. Then draw a separate expiry-only timeline. Explain why these are two distinct paths even though both ultimately deny access.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/security/session.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Check current identity state before a protected action](14-disabled-identity-and-authorization.md) · [Next: Plan registration and web login around trusted services](16-design-registration-and-web-login.md)
