<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/03-connect-an-existing-c-model.md

PURPOSE:
Explain the lesson: Connect an Android screen to an existing C model.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect an Android screen to an existing C model

## Prepare a working Android project

Install Android Studio, an Android SDK, an emulator image, NDK and CMake through SDK Manager. Create an Empty Activity project using Kotlin and Compose, then run the unchanged template. If it does not launch, resolve that setup before adding native code.

The complete integration steps are in `labs/mobile/android-framework-activity/README.md`. Keep the Bits2Banking and Framework source checkouts available.

## Introduce the native boundary

Kotlin describes the screen. The existing C activity rule decides whether a count can advance. JNI is the interface connecting a JVM-language declaration to a native function. Here it carries a single integer, so no text buffers or object ownership cross the boundary.

~~~text
Complete exercise -> NativeActivity.next -> JNI -> BtbActivityNext
~~~

## Add the example

1. Add the supplied Kotlin files while retaining their package name.
2. Call `ActivityScreen()` inside the generated activity's existing content and theme.
3. Merge the README's external-native-build settings into the existing Gradle android block.
4. Point CMake at the real Framework include directory.
5. Sync, build and run.

The CMake file compiles the existing C implementation directly. Do not paste the rule into a new Kotlin function.

## Understand a loading failure

`System.loadLibrary("btb_activity")` requests the library by its logical name. If it cannot be loaded, check the selected ABI and packaged library. If loading succeeds but the native method cannot be found, compare package, class and method names with the C symbol.

## Check the result

Tap once and expect 1. Tap twice more and expect 3. Trace a rejected input through the C bridge tests. The UI should update its count only on an accepted result.

This example uses Framework status declarations; broader Framework services need their own Android port and dependencies. A working small binding is a starting point for that work, not a claim that the full SDK is already available.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/activity_jni.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](04-state-lifetime-and-accessibility.md)


[Previous lesson](02-state-events-and-checks.md)
