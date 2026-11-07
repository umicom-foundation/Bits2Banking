<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/42-desktop-events-and-state.md

PURPOSE:
Explain the lesson: Connect a desktop event to owned state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect a desktop event to owned state

## Before you begin

This lab uses the existing GTK4 activity window. A window is a visible container. A widget is a component such as a button or label. An event reports an interaction. A callback is a function called when that event occurs.

For execution, prepare a C toolchain, CMake, GTK4 development files and a matching installed Framework SDK. The activity README contains the configure and build commands. Start with its unchanged console example before the window.

## Read the path

Open `window.c` and find the Record one exercise button, its signal connection, the callback and the displayed count. Follow the callback to `BtbActivityAdvance`.

~~~text
click -> callback -> checked rule -> update owned count -> refresh label
~~~

The callback receives access to window state. That state must remain alive for every callback that uses it. The example attaches its state lifetime to the window and uses a connection that is tied to the receiving object.

## Perform a focused review

1. Find where the state is allocated.
2. Find where the initial count is set.
3. Find the object responsible for releasing state.
4. Find which connection prevents a destroyed receiver from being called later.
5. Trace the successful and rejected status paths.

A pointer is an address, not a promise that the object still exists. Keeping the lifetime visible is part of making events reliable.

## Lab and expected result

Build the example using its README. Open the window, press the button three times and expect 3. Open a second independent window if you extend the launcher; it should own its own state unless sharing is an explicit requirement. Close a window and check that no later callback refers to its released state.

Record compiler output and observed UI behavior separately. A passing model test does not prove that the button was connected.

## If a button appears inactive

Check that the widget is sensitive, the signal is connected, the callback is reached and the returned status is handled. Also check the event loop is not blocked by long synchronous work. Change one condition at a time so the explanation remains testable.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](41-signed-values-at-a-platform-boundary.md) · [Next lesson](43-call-c-from-a-browser.md)

