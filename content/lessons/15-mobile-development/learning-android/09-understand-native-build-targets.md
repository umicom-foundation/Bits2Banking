<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/09-understand-native-build-targets.md

PURPOSE:
Explain the lesson: Understand the Android native build target.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand the Android native build target

## Set up
Install the Android SDK, a simulator image, NDK and CMake through Android Studio. Create and run an Empty Activity template. The lab README shows how to connect the existing native CMake file through Gradle.

A **target** is a named result that the build system produces. In this lab the result is a shared library loaded by Android. An **ABI** is a set of binary calling and data-layout rules for an architecture and platform.

## Follow the inputs
Open the lab's `CMakeLists.txt`. Locate the JNI adapter, shared bridge and activity model in its source list. These files are compiled for the selected Android target. The Framework include directory supplies declarations used by the model.

The project does not copy a Windows Framework archive into an Android application. Reusing source and API contracts still requires a build appropriate to the destination platform.

## Build a map
Draw:
~~~text
Kotlin screen -> packaged Android native library
                    <- JNI adapter
                    <- shared bridge
                    <- activity C source
~~~
Then add the NDK toolchain and selected ABI as inputs to the compilation box.

**Exercise:** your emulator expects one ABI, but the APK contains only another. At what stage could the failure appear? Expected answer: packaging or native loading can fail even if an unrelated library build succeeded.

## Check and recover
After building, inspect the build output and APK contents using Android Studio's tools. Record the ABI and library name. If CMake cannot find Framework headers, correct the configured include path. If a source path is missing, keep the documented repository structure instead of duplicating the activity rule in the app.

Use [Android's native-build integration guide](https://developer.android.com/studio/projects/gradle-external-native-builds) when matching the generated project settings. This exercise's build, emulator and device results must each be recorded separately.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/CMakeLists.txt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-state-through-screen-recreation.md) · [Next lesson](10-check-a-mobile-workflow.md)

