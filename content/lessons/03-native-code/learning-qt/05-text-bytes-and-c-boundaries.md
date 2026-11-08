<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/05-text-bytes-and-c-boundaries.md

PURPOSE:
Pass text safely from Qt to a C function

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Pass text safely from Qt to a C function

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the profile_name component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/README.md).

## Characters and bytes

Text shown on screen is not necessarily one byte per visible character. UTF-8 represents some characters using several bytes. The Framework name contract deliberately accepts a small ASCII set, so the adapter passes the actual UTF-8 byte count and lets Framework enforce that rule.

The expression input->text().toUtf8() creates a QByteArray. That object owns the bytes for the duration of the callback. bytes.constData() points to them; bytes.size() reports their count. The pointer must not be stored for use after bytes is destroyed.

## Read the call

~~~cpp
const QByteArray bytes = input->text().toUtf8();
char canonical[UMI_LOCAL_PROFILE_NAME_CAPACITY];
const UmiStatus status = UmiLocalProfileNameBytes(
    bytes.constData(), static_cast<size_t>(bytes.size()), canonical);
~~~

The array has capacity for the maximum accepted name plus its terminating zero byte. The function validates an exact span instead of searching beyond that span for a terminator. The output is valid for display only when the status is OK.

## Boundary experiment

1. Enter a three-letter ASCII name. Expect acceptance.
2. Enter two letters. Expect rejection.
3. Enter 48 letters. Expect acceptance and lower-case output.
4. Enter 49 letters. Expect rejection.
5. Enter a name beginning with a digit. Expect rejection.
6. Enter a name containing an accented character. Expect rejection under this particular name contract.

A product may later choose a broader international name policy. That would be a change to the shared contract, its storage rules and its tests, not a silent workaround in one frontend.

## Output must be treated as data

The result label uses Qt::PlainText. It should display text rather than interpret input as rich markup. Input validation and safe presentation are separate responsibilities: a future service may accept text with angle brackets, so the view should still choose the correct rendering mode.

## Check your understanding

Why pass a length? It identifies the readable input boundary. Why not display canonical after failure? The service promises not to publish a valid result on failure; using an uninitialised output array would be a separate bug. Why keep bytes alive during the call? The C function reads memory owned by that object.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/profile_window.cpp).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Connect clicks and keyboard actions to Framework](04-connect-clicks-to-framework.md) · [Next: Test the real widget event path](06-widget-event-tests.md)

<!-- The original out-of-docs lab routes are retained for review: (../../../../labs/framework/qt-profile/README.md) (../../../../labs/framework/qt-profile/profile_window.cpp). Published manuscripts use repository source links because the site does not copy the labs directory. -->

<!-- The earlier setup required an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. The profile_name component now supplies the same policy without account-storage dependencies; the previous requirement is retained here for review. -->
