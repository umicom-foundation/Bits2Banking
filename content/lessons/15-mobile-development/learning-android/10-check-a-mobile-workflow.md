<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/10-check-a-mobile-workflow.md

PURPOSE:
Explain the lesson: Check a complete mobile activity workflow.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a complete mobile activity workflow

## Prepare
Use a fresh Android activity lab project configured with the documented Kotlin screen, JNI bridge and shared C source. Record the repository revision, Android SDK, NDK, emulator/device and build configuration. These identify what was checked.

A workflow check follows a person's goal from start to finish. For this example the goal is to record exercises and see an accurate count, including after a refused update.

## Run the ordinary path
1. Launch and expect a count of 0.
2. Find Complete exercise using touch.
3. Tap once; expect 1 and a success message.
4. Tap twice more; expect 3.
5. Rotate the emulator; record the restored value.
6. Navigate with accessibility support and locate the labelled action.

Use the lab's native bridge tests for boundary inputs. Do not require a beginner to tap a button a thousand times to establish a model property.

## Run the failure path
In a disposable instrumented copy, arrange a valid full count. Attempt another completion. Expect the previous value to remain and a visible explanation. Restore the normal initial state afterward.

Write a check for each layer: the model's capacity rule, the JNI result, and the screen's presentation. A passed host test cannot establish that the screen's click listener is wired.

## Investigate a nonresponsive button
Ask in order: is the control enabled; did the handler run; did the native library load; what result returned; did state change; did the screen redraw? Record evidence at the earliest failing boundary. Avoid repeatedly changing unrelated layouts.

## Finish
Keep observed results beside expected results, including failures and skipped checks. This is a small teaching workflow, not full mobile Framework qualification or a release checklist for an unrelated application.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-understand-native-build-targets.md)

