<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/48-share-a-model-with-a-microdevice.md

PURPOSE:
Explain the lesson: Share a C model with a microdevice.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Share a C model with a microdevice

A microdevice often has a small processor, limited memory and physical inputs instead of desktop windows. The same application rule can still be shared when it does not depend on a windowing system.

This lab connects the existing activity model to an original non-wireless RP2040 Pico. A sampled button increases a bounded count. The LED shows whether the count is odd.

## Setup recap

Use the complete README and WIRING.md in labs/microdevices/pico-activity. You need the Pico SDK, a compatible Arm cross-compiler with C23 support, CMake, Ninja and the matching Framework headers. The host activity-adapter checks are a separate exercise.

## 1. Locate the shared rule

The build includes activity.c from the Framework activity laboratory and button.c from activity-adapters. main.c contains the hardware loop. It does not introduce another copy of the counting rule.

The teaching model uses Framework's UmiStatus contract. This small firmware does not link the entire desktop Framework or claim that every Framework service is available on the board.

## 2. Translate the input

The button connects GP15 to ground. The input has an internal pull-up, so an open button reads high and a pressed button reads low. The expression `!gpio_get(15)` translates that electrical reading into the application's pressed value.

BtbActivityButtonSample remembers the last sample and counts a sampled rise. It is not a physical-button debounce algorithm.

## 3. Translate the output

The expression `completed & 1U` selects the least significant bit. It is 1 for odd counts and 0 for even counts. gpio_put sends that value to the onboard LED.

The LED is a limited display. It does not show the complete count or identify saturation. Use that limitation when deciding what the interface can communicate.

## Exercise and recovery

Trace samples false, true, true, false, true. Starting from zero, the count should end at 2 and the LED should be off. Explain why the held true sample does not add another event.

If the LED changes more than once per press on a physical board, investigate contact bounce. Keep the model, sampling policy and electrical observation separate while diagnosing the result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/microdevices/pico-activity/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](47-test-adapters-and-user-journeys.md) · [Next lesson](49-understand-a-cross-compiled-build.md)

