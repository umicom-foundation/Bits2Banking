<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/07-from-name-check-to-registration.md

PURPOSE:
Plan registration and login beyond a name checker

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan registration and login beyond a name checker

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.

[Open the complete lab guide](../../../../labs/framework/wt-profile/README.md).

## Distinguish the operations

Validation asks whether input follows a rule. Registration creates an account record. Authentication checks a claimed identity. Authorisation decides whether that identity may perform an operation. A session maintains the result of an interaction over time. These are different responsibilities.

~~~text
registration -> durable account record
login        -> verified identity -> session
request      -> session + permission check -> permitted operation
~~~

The lab implements only the first, narrow input-validation step. It deliberately does not display a fake logged-in state.

## A registration design exercise

1. Describe the identity being created: local device profile or server-managed account.
2. Choose the authoritative account store and its ownership.
3. Specify name uniqueness and duplicate handling.
4. Use a reviewed password-verifier design or approved identity provider.
5. Define verification, recovery and session-expiry workflows.
6. Add rate limits, safe error responses and audit events without passwords.
7. Define authorisation for every protected action.
8. Test failure, cancellation, replay and concurrent requests.

Umicom's local-profile service has a specific native-backend contract. Its existence does not automatically supply a web account system. Read platform support and storage semantics before deciding whether that service fits a new use case.

## Why not put credentials in a URL?

URLs can appear in browser history, server logs and intermediary records. Credentials need an appropriate protected request path and transport. A production web deployment also needs HTTPS, secure session handling and operational review. This loopback lab does not configure those production controls.

## Share policy without sharing secrets

A desktop, mobile and web interface can reuse a documented account contract. They should not each invent their own password storage. They also must not assume that every frontend can use the same native credential-vault adapter.

## Exercise

Write acceptance criteria for registration without implementing it yet. Include successful creation, duplicate name, invalid input, unavailable storage, cancelled request and a second user's attempt to access the account. For each case state what the user sees and what durable state should remain.

[Learning Cybersecurity](../../../courses/learning-cyber-security/index.html) develops the boundary and ownership ideas used in this design.

## Read the source

[Open the example source](../../../../labs/framework/wt-profile/profile_application.cpp).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Test a local web workflow and record outcomes](06-test-a-local-web-workflow.md) · [Next: Share Framework services across web and desktop](08-share-framework-services-across-frontends.md)
