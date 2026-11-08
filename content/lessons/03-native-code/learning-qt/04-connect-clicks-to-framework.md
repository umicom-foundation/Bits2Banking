<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/04-connect-clicks-to-framework.md

PURPOSE:
Connect clicks and keyboard actions to Framework

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect clicks and keyboard actions to Framework

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the profile_name component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/README.md).

## Signals and callbacks

A signal announces that something happened. A callback is a function registered to run in response. In this example, the button's clicked signal invokes a small function that obtains text, calls Framework and updates the result label.

~~~text
click or Enter
    -> callback
    -> UmiLocalProfileNameBytes
    -> UmiStatus
    -> result label
~~~

The lambda expression beginning with [input, result] is an unnamed C++ function. The names in brackets are values it captures for later use. Here those values are pointers to controls, not copies of all their text.

## Follow the connection

1. Locate QObject::connect(check, &QPushButton::clicked, window, ...).
2. Identify check as the signal sender.
3. Identify window as the connection context. Its lifetime bounds this callback connection.
4. Read the callback until the UmiLocalProfileNameBytes call.
5. Find the status comparison with UMI_STATUS_OK. The application must check the result before using canonical output.
6. Locate the returnPressed connection. It invokes the same button action when the user presses Enter in the input.

Using one action path keeps the mouse and keyboard behaviours consistent. There is no second copy of the name policy in a key handler.

## Try both routes

Enter Alice_7 and click Check name. Expect Accepted name: alice_7. Replace it with the same input and press Enter. Expect the same result. Enter ../../other and try both routes again. Both should reject it.

## Diagnose a silent button

First verify the control is enabled and receives the event. Then check that the connection is created, its sender still exists, and the callback reaches the service. Finally inspect the returned status and result update. A screenshot of a button alone proves none of these steps.

Avoid adding password derivation or network requests directly to this callback. Name validation is short and local. Slow operations need a worker, cancellation and a lifetime-safe result handoff so the event loop remains responsive.

## Exercise

Add a keyboard-only check to your manual checklist. State the input, the action and the exact visible result. A statement such as 'the window opened' is not enough to demonstrate that the command is wired.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/profile_window.cpp).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Controls, layouts and ownership](03-controls-layouts-and-ownership.md) · [Next: Pass text safely from Qt to a C function](05-text-bytes-and-c-boundaries.md)

<!-- The original out-of-docs lab routes are retained for review: (../../../../labs/framework/qt-profile/README.md) (../../../../labs/framework/qt-profile/profile_window.cpp). Published manuscripts use repository source links because the site does not copy the labs directory. -->

<!-- The earlier setup required an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. The profile_name component now supplies the same policy without account-storage dependencies; the previous requirement is retained here for review. -->
