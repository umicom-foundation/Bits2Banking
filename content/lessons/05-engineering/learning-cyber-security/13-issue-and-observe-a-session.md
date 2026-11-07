<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/13-issue-and-observe-a-session.md

PURPOSE:
Issue and observe a session without exposing its handle

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Issue and observe a session without exposing its handle

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## A session is a temporary association

The session registry associates an opaque handle with a principal and a lifetime. Opaque means the caller must not depend on how the handle is formatted. The Framework obtains randomness through its platform service; callers must handle an issuance failure rather than substitute a predictable identifier.

The production host authenticates the principal before calling `umi_session_registry_issue`. The registry itself does not verify a password or check whether an identity is enabled.

## Read the example call

```c
umi_session_registry_issue(sessions, learner.identity_id,
                           100U, 50U, &issued);
```

The arguments are the registry, principal ID, current clock value, lifetime and destination record. The declared time unit is nanoseconds. The lab uses tiny synthetic values so the arithmetic is easy to inspect; it is not recommending a fifty-nanosecond user session.

1. Check the return status.
2. Keep the resulting handle private.
3. Pass it to `umi_session_registry_validate` at a later trusted clock value.
4. Use the returned principal only after validation succeeds.

A copied record is an observation, not a permanent permission. A later request must check again.

## Avoid accidental disclosure

The lab prints descriptive milestones but never prints `session_id`. Logging a valid handle could let someone reuse it. Keep handles out of URLs, screenshots, diagnostics and teaching fixtures that leave your device.

## Failed outputs

Before a negative check, the lab copies the output record to a second object. After refusal it compares all bytes to verify that the failed call did not publish a partial result. This protects the caller from using data left over from an incomplete operation.

## Exercise

Write down the earliest valid time and the first expired time for issuance at 100 with lifetime 50. Then inspect the expiry comparison in the implementation. Explain why accepting a caller-supplied clock from a browser request would defeat a timeout policy.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/session.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Keep credential references inside their buffers](12-reference-fields-and-string-bounds.md) · [Next: Check current identity state before a protected action](14-disabled-identity-and-authorization.md)
