<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/17-inspect-apk-native-abis.md

PURPOSE:
Teach inspect the native libraries packaged in an apk through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect the native libraries packaged in an APK

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## A built library must reach the package

CMake producing a shared library is only one step. Gradle must package that output for the application variant and target ABI. In Android Studio, open the debug APK with APK Analyzer and inspect the lib directory. Locate libbtb_profile.so below the relevant ABI directory. Record the file path and APK variant you inspected.

## Compare emulator and device targets

An emulator may use x86_64 while a physical phone uses arm64-v8a. Another emulator can use Arm64. Read the actual target rather than guessing from the word emulator. When a selected ABI is missing, inspect Gradle ABI filters and native build outputs. Adding a different architecture file under the desired folder name cannot change its machine code.

## Exercise one packaging hypothesis

First build the debug app and its test APK. Inspect the app APK for the library, then run the instrumented suite on the matching target. If loading fails despite a present file, preserve the full error and inspect dependent libraries and platform requirements. Presence, successful loading and correct function results are three separate observations.

## Keep release delivery separate

The laboratory does not sign a production release, upload a store package or manage upgrades. A release variant can differ in optimisation, shrinking, native symbols and signing. Record debug evidence accurately and plan release checks against the actual release artefact. Keep symbols with their matching build for diagnosis; do not publish private device logs as course content.

## Build and observe

Run each command separately and stop on errors. The instrumented task installs and runs test APKs on connected targets. Keep the ten named results and target identity; no result is implied by these instructions.

~~~powershell
Set-Location C:\umicom\projects\NativeProfileLab
.\gradlew.bat :app:assembleDebug :app:assembleDebugAndroidTest
.\gradlew.bat :app:connectedDebugAndroidTest -Pandroid.testInstrumentationRunnerArguments.class=org.umicom.learning.profile.NativeProfileInstrumentedTest
~~~

Native Umicom CLI CMake/CTest commands do not replace this Gradle workflow. Review app/build/reports/androidTests/connected for the actual result. Keep host, emulator and device evidence separate.

## Read the implementation

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/CMakeLists.txt) · [Android JNI guidance](https://developer.android.com/ndk/guides/jni-tips) · [Instrumented test setup](https://developer.android.com/training/testing/instrumented-tests)

[Course contents](index.md) · [Previous lesson](16-run-android-native-contract-tests.md) · [Next lesson](18-record-mobile-evidence-by-layer.md)
