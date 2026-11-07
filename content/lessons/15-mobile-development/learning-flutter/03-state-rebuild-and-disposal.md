<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/03-state-rebuild-and-disposal.md

PURPOSE:
Explain the lesson: Understand state, rebuilds and disposal.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand state, rebuilds and disposal

## A screen description can be rebuilt

Flutter describes an interface with widgets. A StatefulWidget has a separate State object that can hold temporary values between rebuilds. Calling setState tells Flutter that the interface should be rebuilt using the updated state.

The lesson counter holds a completed count. Its buttons change that count, and the displayed text is derived from it. This is temporary practice state, not a saved learner record.

## Setup recap

Install Flutter and the tools required for your target platform. Run `flutter doctor` and `flutter devices`. Follow the [counter lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/README.md), which creates a practice project and identifies the exact files to copy. iPhone builds require the Apple development environment on a Mac.

## Follow one activation

~~~text
button activated
      |
validate current count
      |
setState changes completed
      |
build reads completed
      |
new visible count and button state
~~~

The button becomes unavailable at the practice limit. Reset becomes available only when there is something to reset. The callback and the visible control state should agree.

## Lab

1. Launch the practice application on your selected device.
2. Complete one practice lesson and read the count.
3. Continue to the limit and confirm that another activation cannot advance it.
4. Reset and confirm zero is shown.
5. Restart the application and observe that the count starts again.
6. Explain which behaviour would need a storage service if progress had to survive restarts.

A rebuild of the same mounted State object is different from disposing it and creating a new object. Changing a theme can rebuild the widget tree without resetting that state. Removing the screen and later creating a fresh one can reset it.

## Exercise and explanation

Should the count be changed inside build? No. Building describes the current interface. User actions or other explicit events should cause state changes; otherwise a redraw could change progress unexpectedly.

## Connect to Umicom

This small Dart exercise teaches interface state. It is not yet a Framework binding. A production Umicom client should call the shared Framework model through an appropriate native boundary and keep storage, validation and permissions in reusable services.

## Troubleshooting

If text does not update after a click, inspect whether the change is inside setState and whether the callback is enabled. If state unexpectedly resets, inspect widget identity, placement and disposal before adding global variables.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/main.dart). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](02-widgets-state-and-tests.md) · [Next lesson](04-test-widget-lifetime.md)

