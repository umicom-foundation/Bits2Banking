<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/04-state-lifetime-and-accessibility.md

PURPOSE:
Explain the lesson: Check Android screen lifetime and accessible feedback.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check Android screen lifetime and accessible feedback

## Before you begin

Use the native activity screen from the previous lesson or follow its README from a fresh Empty Activity project. Run it once on an emulator. A screen can be recreated when the system changes configuration, so displayed state needs a clear owner.

## Identify each kind of state

The count is the application's current value. A status message explains the last action. A saved-state mechanism can help restore a small value during screen recreation. Long-term persistence is a separate responsibility.

The example uses `rememberSaveable` for screen values. Do not infer that it is a database or that it preserves every session indefinitely. An intentionally cleared app, a new installation and a recreated activity are different events.

## Follow an update

~~~text
old count -> native request -> result
                          -> accepted: replace count
                          -> refused: keep count, show explanation
~~~

A failed request should not erase useful progress. The message explains the refusal without presenting a negative number as completed work.

## Lab

1. Start a fresh activity and record its count.
2. Tap three times and expect three accepted increments.
3. Rotate the emulator and observe whether saved state is restored.
4. Close and relaunch using the same steps each time; record how that differs from rotation.
5. Enable the platform screen reader and find the button by its label.
6. Increase system font size and check that the count and action remain readable.

## What a model test misses

The C bridge tests do not inspect touch targets, text clipping, focus order or screen-reader output. Those require interface evidence. Conversely, tapping a few times does not cover every invalid C input.

## Debug one boundary at a time

If rotation loses progress, inspect state ownership and restoration. If a tap does nothing, inspect the event handler and native call. If the library fails to load, investigate packaging before changing the UI layout.

## Extension exercise

Design an explicit Save progress feature. Choose its location and lifecycle, define recovery after a failed write, and keep the reusable persistence service in Framework. Do not hide that policy inside a button callback.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/ActivityScreen.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-connect-an-existing-c-model.md)


[Next: Follow one button press across JNI](05-follow-the-call-across-jni.md)
