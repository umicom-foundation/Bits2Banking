<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/09-accessible-actions-and-messages.md

PURPOSE:
Explain the lesson: Check accessible actions and feedback.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check accessible actions and feedback

## Prepare
Run the iPhone activity lab on a simulator or device configured through its README. The screen uses a text label on its button and displays both a count and a result message. Accessibility means that people can understand and operate the workflow through more than one input or presentation method.

## Review the interaction
1. Read the button's label without surrounding explanation. Does it describe the action?
2. Activate it once and confirm the count changes.
3. Find the count using the platform's accessibility tools.
4. Check that the result message remains understandable without relying on colour.
5. Increase text size and inspect whether the action and result are still reachable.

Record what was observed rather than assuming that using a native control proves every accessibility requirement.

## Study failure feedback
The rejected path leaves the count unchanged and displays a message. A person should not need to inspect a debugger to learn that an action was refused. Conversely, the interface should not claim an exercise was recorded when the C bridge returned -1.

**Exercise:** write a clearer message for a future typed “capacity reached” result. It should explain the next useful action without exposing internal function names. Keep the general fallback for unknown failures.

## Connect to Umicom
A shared C/Framework service owns the operation's meaning. Each platform translates its result into accessible local controls and messages. This allows different screen technologies while preserving one application contract.

## Recover from layout problems
Test large text and orientation separately. If content clips, inspect layout constraints and available space before reducing the user's chosen text size. If a button is unreachable, record the input method and exact screen state. Those observations become concrete regression cases rather than a vague claim that the interface is usable.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/ActivityView.swift). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-simulator-and-device-builds.md) · [Next lesson](10-check-the-whole-native-path.md)

