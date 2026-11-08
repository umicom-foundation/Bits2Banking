<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/13-build-c-for-the-android-target.md

PURPOSE:
Teach compile shared c for the android target through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compile shared C for the Android target

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## A source file is portable before its object file is

The profile-name source has a small standard-C dependency surface. Its compiled object still belongs to a specific target. A Windows archive cannot become an Android archive by changing its extension. In this lab Gradle invokes the NDK toolchain, which compiles the same source for the selected Android ABI and links it into libbtb_profile.so.

## Inspect the dependency graph

Read the lab CMake file. BTB_FRAMEWORK_SOURCE identifies an absolute checkout, and UmicomAndroidProfileName.cmake creates the adapter target. That target links Umicom::profile_name. The application shared library links the adapter. No step configures the complete Framework root. Position-independent code on the static inputs permits their inclusion in the shared library.

## Perform a clean comparison

Use the Gradle build command from the setup, then inspect its native compiler and ABI output. Compare the source paths with your intended Framework checkout. Record the NDK version, CMake version, target ABI and build variant. Rebuilding for another ABI requires target-specific outputs; do not reuse a host build directory as an Android native directory.

## Recover at the dependency boundary

A missing adapter module means the source path or integrated files are wrong. A C23 diagnostic means the selected compiler or CMake language mode needs investigation. An incompatible-object linker error points to target mismatch. Fix the earliest failing boundary, then rebuild. Reducing warning levels or copying a desktop DLL into the APK does not address any of these causes.

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

[Course contents](index.md) · [Previous lesson](12-read-bounded-java-strings.md) · [Next lesson](14-match-native-method-identity.md)
