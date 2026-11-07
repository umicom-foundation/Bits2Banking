<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/05-follow-the-call-across-jni.md

PURPOSE:
Explain the lesson: Follow one button press across JNI.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow one button press across JNI

## Prepare the screen
Install Android Studio, an Android emulator image, the NDK and CMake. Create an Empty Activity with Kotlin and Compose and run its unchanged template first. The [Android activity lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/mobile/android-framework-activity) contains the complete source-integration steps. Keep the Framework include directory available.

A **boundary** is a point where one part of a program calls another part with different rules. Here Kotlin calls C through JNI, the Java Native Interface.

## Trace the path
1. Open `ActivityScreen.kt`. Find `Button(onClick = ...)`. The braces contain the work requested by a press.
2. Follow `NativeActivity.next(completed)` into the declaration in `NativeActivity.kt`.
3. Find `Java_org_umicom_learning_activity_NativeActivity_next` in `activity_jni.c`.
4. Follow its call to `BtbActivityNext`, then to `BtbActivityAdvance` in the shared C example.
5. Follow the integer result back to the screen.

For an initial count of 4, the successful result is 5. The Kotlin screen displays that result; it does not calculate a second count independently.

## Work on paper
Draw five boxes for those five source locations. Label each arrow with the value crossing it. Repeat with 1000: the C model refuses another completion, the bridge returns -1, and the screen retains 1000 while changing its message.

**Exercise:** explain why the screen checks `next >= 0` before assigning `completed`. Expected explanation: a negative value reports failure and must not become the visible count.

## Diagnose a break
A missing function error before entering C is a linkage problem. A -1 returned from C is an application result. Record which box was reached before changing the code. Rebuilding the screen cannot repair an incorrectly named native symbol unless the declaration or export is corrected.

This lab uses Framework status types and the existing C teaching model. It does not establish that every Framework service runs on Android.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/activity_jni.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-state-lifetime-and-accessibility.md) · [Next lesson](06-package-and-library-identity.md)

