<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/03-controls-layouts-and-ownership.md

PURPOSE:
Controls, layouts and ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Controls, layouts and ownership

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the profile_name component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/README.md).

## A window is a tree of objects

The example has one parent window and several child controls. Ownership answers who is responsible for destroying an object. A layout controls geometry: where controls appear and how available space is shared.

~~~text
window
  layout
  instruction label
  input box
  check button
  result label
~~~

QVBoxLayout arranges its items vertically. The application adds controls to the layout instead of assigning a fixed pixel position to every control. This lets longer text and a resized window use available space.

## Trace the construction

1. Locate new QVBoxLayout(window). The layout is installed on the window.
2. Locate each control constructor ending with window. The parent is explicit.
3. Match every layout->addWidget call to its control.
4. Find setWordWrap(true) on the instruction and result labels. Wrapping allows a long sentence to occupy more than one line.
5. Find setAccessibleName on the input. An accessible name describes a control to assistive technology; a test object name serves a different purpose.

The pointers input, check and result refer to controls owned by the window. They are not invitations to delete those controls from an unrelated callback. Closing a window and destroying a window are also distinct operations: an application may hide a reusable window before its owner eventually destroys it.

## Resize experiment

Launch the example. Make the window narrow and then wide. The input and button should remain reachable, and the labels should wrap instead of overlapping them. Try keyboard navigation with Tab and Shift+Tab. Record clipping or inaccessible controls as defects, even if the program compiles.

## Extend carefully

In a practice copy, add a label describing an example valid name. Give it the same parent and add it through the layout. Do not change the C validation service for this presentation-only addition. If the layout is crowded, adjust grouping or margins rather than repeatedly setting fixed sizes.

## Common ownership mistake

A pointer can outlive its object. Such a pointer is dangling: it still contains an address, but that address no longer identifies a usable object. The callback lifetime in the next lesson is tied to the owning window to avoid keeping an event connection alive after the view is destroyed. This protects this connection; it does not make every pointer in an application automatically safe.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/profile_window.cpp).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Build a small Qt consumer of the Framework SDK](02-build-a-small-qt-consumer.md) · [Next: Connect clicks and keyboard actions to Framework](04-connect-clicks-to-framework.md)

<!-- The original out-of-docs lab routes are retained for review: (../../../../labs/framework/qt-profile/README.md) (../../../../labs/framework/qt-profile/profile_window.cpp). Published manuscripts use repository source links because the site does not copy the labs directory. -->

<!-- The earlier setup required an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. The profile_name component now supplies the same policy without account-storage dependencies; the previous requirement is retained here for review. -->
