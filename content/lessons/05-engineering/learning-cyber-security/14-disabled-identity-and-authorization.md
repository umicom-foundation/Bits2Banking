<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/14-disabled-identity-and-authorization.md

PURPOSE:
Check current identity state before a protected action

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check current identity state before a protected action

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## Separate the decisions

A valid session answers whether a handle is active at the observed time. It does not answer whether the identity may still use the application, own a particular document or submit a payment.

Consider a user who was allowed to sign in yesterday but whose account is disabled now. A previously issued session must not silently override that administrative decision.

## Follow the lab

1. Validate the synthetic session.
2. Disable its identity with `umi_identity_registry_set_enabled`.
3. Retrieve the current identity using `umi_identity_registry_get`.
4. Observe that `enabled` is false.
5. Revoke the session and refuse further use.

The lab performs no protected action. It demonstrates why a host must combine these checks with its operation policy. A Bank transfer additionally needs the correct account, permitted action, limits and approval state. A Studio document operation needs the intended workspace and file permissions.

## Fresh state and concurrency

An observation can become stale. If one thread checks identity state while another disables the user, an operation must define where the decision becomes authoritative. Separate registry calls alone do not form a transaction across an entire application.

For the local lab, all calls run sequentially in one process. A production service should centralize policy enforcement at the operation boundary and define its concurrency rules. Do not infer distributed or transactional guarantees from this demonstration.

## A small decision table

| Session valid | Identity enabled | Operation policy permits | Decision |
|---|---|---|---|
| No | Any | Any | Refuse |
| Yes | No | Any | Refuse |
| Yes | Yes | No | Refuse |
| Yes | Yes | Yes | Continue through the operation's remaining checks |

## Exercise

Describe two actions an application reader may perform and one reserved for an editor. State where the policy is checked. Hiding a button is useful presentation, but the command handler or service must also enforce the permission.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/identity.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Issue and observe a session without exposing its handle](13-issue-and-observe-a-session.md) · [Next: Test expiry, logout and cleanup precisely](15-expiry-logout-and-cleanup.md)
