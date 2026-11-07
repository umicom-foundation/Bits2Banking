<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/17-desktop-and-mobile-sign-in.md

PURPOSE:
Use the same security boundary from desktop and mobile

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Use the same security boundary from desktop and mobile

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## Different screens, shared rules

A desktop window, a phone screen and a web page can represent the same account lifecycle. The presentation changes; the authoritative authentication and authorization decisions still belong to trusted services.

Begin by separating UI state from security state. A selected Live or Paper tab is a user preference. It is not evidence that a broker authenticated the account. Likewise, a successful-looking button animation is not a successful login.

## Trace a provider result

1. The user chooses a connection mode.
2. The client starts the supported provider flow.
3. The provider reports a result through its documented channel.
4. The client validates that result using the selected integration contract.
5. Framework services expose the resulting connection and permissions to the application.
6. On failure, the UI explains the problem and retains only non-secret input that is safe to keep.

A guest or local simulation mode should be clearly labelled and should not inherit live permissions.

## Credential references

The credential registry stores a provider ID and a reference. A platform adapter may resolve a reference using the operating system's protected secret store. That adapter must verify ownership and access policy. Recording a reference alone does not encrypt anything or guarantee its storage provider exists.

Do not place client secrets in a distributed mobile or desktop binary and assume they remain private. Select an authentication integration suitable for a public client, and follow the provider's supported browser or application flow.

## Keep lessons reproducible

The local identity lab requires no real credentials. It teaches lifecycle behaviour with synthetic records so learners can inspect and modify the code without an external account.

## Exercise

Sketch the desktop and mobile screens for connecting, waiting, failed login, connected and disconnected states. Next to each screen list the actual service event that permits the transition. Add a cancel path that releases pending resources and never publishes a partly authenticated state.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/credential.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Plan registration and web login around trusted services](16-design-registration-and-web-login.md) · [Next: Review security changes with tests and explicit limits](18-review-security-evidence.md)
