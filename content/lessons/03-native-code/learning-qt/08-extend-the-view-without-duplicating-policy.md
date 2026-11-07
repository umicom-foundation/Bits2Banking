<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/08-extend-the-view-without-duplicating-policy.md

PURPOSE:
Extend the view while keeping Framework authoritative

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Extend the view while keeping Framework authoritative

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](../../../../labs/framework/qt-profile/README.md).

## Separate the responsibilities

The view collects input and presents results. Framework owns the profile-name contract. A backend owns durable storage or external communication. Keeping these responsibilities explicit lets a desktop view and a web view agree about the same input.

~~~text
Qt desktop ----+
               +-> Framework C name service
Wt web --------+
~~~

The same architecture does not mean every application needs the same layout. A trading workspace, editor and media timeline have different tasks. They can still use common validation, document ownership and persistence services.

## Plan a real extension

Suppose the next feature is local profile registration. A name checker alone is insufficient. Registration also needs a password policy, secure randomness, a password verifier, a storage backend, duplicate handling, asynchronous UI work and failure presentation. The Framework header exposes local-profile operations, but its platform support and ownership contract must be checked before wiring them into a view.

1. Write the user workflow and its expected outcomes.
2. Identify the existing Framework service for each operation.
3. Read its input, output, lifetime and platform requirements.
4. Keep slow work off the GUI event loop.
5. Decide what happens if the window closes while work is pending.
6. Add service tests and event-path tests.
7. Qualify the actual installed workflow.

Do not add a working-looking Register button that simply changes a status label without creating a profile. Do not label this lab as authentication: it validates a name and stops there.

## Practice extension

Add a short help label and a Clear input button in your practice copy. Clear should empty the input, restore the initial result text and return keyboard focus to the input. This is view behaviour, so it does not require another C validation function. Test that Clear neither creates a profile nor changes an accepted name elsewhere.

For a web presentation of the same C service, continue with [Learning Wt](../../../courses/learning-wt/index.html). For the shared C boundary rules, continue with [Learning Cybersecurity](../../../courses/learning-cyber-security/index.html).

## Completion check

You should now be able to identify the event loop, ownership tree, callback, C service call, status check and test assertion. Explain each in your own words before adapting the pattern to a larger application.

## Read the source

[Open the example source](../../../../labs/framework/qt-profile/profile_window.cpp).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Troubleshoot a desktop adapter with evidence](07-troubleshoot-with-evidence.md)
