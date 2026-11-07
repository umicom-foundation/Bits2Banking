<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/08-state-through-screen-recreation.md

PURPOSE:
Explain the lesson: Follow state through screen recreation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow state through screen recreation

## Prepare the experiment
Set up the Android activity lab with Android Studio, Compose, the NDK and the Framework headers as described in its README. Run on an emulator. The initial count should be 0. Keep a small table with columns for action, count and observation.

**State** means values the application retains while it works. This example keeps a count and a message. The C function calculates a transition; the screen owns the currently displayed values.

## Read and observe
1. Find `rememberSaveable { mutableStateOf(0) }`.
2. Tap Complete exercise three times. Expect 3.
3. Rotate the emulator and wait for the screen to settle.
4. Record whether the count remains 3.
5. Compare this with starting a genuinely new session.

Saved screen state supports recreation. It is not a project file that a learner can choose, copy to another device or inspect as durable course progress. Do not describe a rotation check as proof of long-term saving.

## Separate two requirements
Write one requirement for restoring a temporary screen and another for saving a named learning project. The second needs an explicit format, location or storage service, error reporting and recovery. It should use the relevant shared Framework persistence contract when introduced.

**Exercise:** explain where the count resides while the C call runs. Expected answer: Kotlin owns the screen value, passes a copy of it to C, and assigns the successful result back.

## Troubleshooting
If rotation resets the count, first check that the application is using `ActivityScreen()` and the intended state declaration. If a completely new launch restores a value, record the launch and lifecycle conditions rather than concluding that the example has a database.

The experiment should use harmless learning data. Do not add an account password, private file contents or a device identifier to logs merely to track recreation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/ActivityScreen.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-check-values-before-conversion.md) · [Next lesson](09-understand-native-build-targets.md)

