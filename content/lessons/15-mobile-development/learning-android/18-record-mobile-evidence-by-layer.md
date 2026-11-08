<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/18-record-mobile-evidence-by-layer.md

PURPOSE:
Teach record mobile evidence without overstating coverage through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Record mobile evidence without overstating coverage

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## Start with an evidence table

Create columns for layer, source identity, target, command, expected result, observed result and limitations. Add rows for pure C policy, controlled host JNI calls, Android instrumented tests and manual application behavior. Mark a row unexecuted until it has an actual result. A source review can explain what should happen, but it cannot fill an execution row.

## Connect each failure to one boundary

Use the call graph from lesson 11. A compiler rejection belongs before packaging; a missing shared library belongs at loading; a wrong canonical name belongs at conversion or policy. Link the diagnostic to the exact command and source checkout. If the binary identity is unknown, say so. This keeps a later repair from being credited against an older or different executable.

## Compare targets deliberately

Run the same instrumented class on a supported emulator and, when available, a physical device. Keep their results separate even if both pass. Record Android API level, ABI, NDK/compiler and variant. For untested targets, write not tested. The same source file and passing desktop tests do not establish device lifecycle, accessibility, background operation or release readiness.

## Plan the next useful extension

Choose one missing user workflow, such as applying the validated name to an approved existing screen, and define acceptance steps before editing it. Keep account creation, durable storage and authentication outside this small naming service. Reuse Framework for new shared behavior, retain the instrumented boundary checks, and review any new layout against the product design before presenting it as complete.

## Build and observe

Run each command separately and stop on errors. The instrumented task installs and runs test APKs on connected targets. Keep the ten named results and target identity; no result is implied by these instructions.

~~~powershell
Set-Location C:\umicom\projects\NativeProfileLab
.\gradlew.bat :app:assembleDebug :app:assembleDebugAndroidTest
.\gradlew.bat :app:connectedDebugAndroidTest -Pandroid.testInstrumentationRunnerArguments.class=org.umicom.learning.profile.NativeProfileInstrumentedTest
~~~

Native Umicom CLI CMake/CTest commands do not replace this Gradle workflow. Review app/build/reports/androidTests/connected for the actual result. Keep host, emulator and device evidence separate.

## Read the implementation

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md) · [Android JNI guidance](https://developer.android.com/ndk/guides/jni-tips) · [Instrumented test setup](https://developer.android.com/training/testing/instrumented-tests)

[Course contents](index.md) · [Previous lesson](17-inspect-apk-native-abis.md)
