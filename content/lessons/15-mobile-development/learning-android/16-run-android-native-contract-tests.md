<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/16-run-android-native-contract-tests.md

PURPOSE:
Teach run the android native contract tests through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Run the Android native contract tests

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## Choose the execution layer

The optional Framework host suite compiles against real JDK JNI declarations and substitutes a controlled function table. It can check admission and exception paths without launching a JVM. The Android instrumented suite loads the actual target library through NativeProfile on an emulator or device. These suites answer different questions and should have separate result records.

## Place and select the test class

Keep NativeProfileInstrumentedTest.kt under app/src/androidTest/java/org/umicom/learning/profile. The generated project needs AndroidJUnitRunner and compatible AndroidX JUnit test dependencies. Run the class-filtered connectedDebugAndroidTest command from the README. A similarly named class under src/test would be a local JVM test and would not establish Android library loading.

## Read individual outcomes

Expect ten test methods, including valid minimum and maximum values, invalid ASCII and Unicode, embedded NUL, and recovery after refusal. Open the report for each connected target. Verify the class name and method names rather than treating a successful task exit as proof that the intended class ran. Preserve failed, skipped and absent tests distinctly.

## Diagnose a missing result

If no device is selected, establish the emulator/device connection first. If the class is absent, check source placement, package spelling and the filter. If a native crash occurs, retain Logcat and the matching native build identity. Do not repeatedly change assertions until the test becomes green; first confirm that the intended library and method are the ones being exercised.

## Build and observe

Run each command separately and stop on errors. The instrumented task installs and runs test APKs on connected targets. Keep the ten named results and target identity; no result is implied by these instructions.

~~~powershell
Set-Location C:\umicom\projects\NativeProfileLab
.\gradlew.bat :app:assembleDebug :app:assembleDebugAndroidTest
.\gradlew.bat :app:connectedDebugAndroidTest -Pandroid.testInstrumentationRunnerArguments.class=org.umicom.learning.profile.NativeProfileInstrumentedTest
~~~

Native Umicom CLI CMake/CTest commands do not replace this Gradle workflow. Review app/build/reports/androidTests/connected for the actual result. Keep host, emulator and device evidence separate.

## Read the implementation

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/NativeProfileInstrumentedTest.kt) · [Android JNI guidance](https://developer.android.com/ndk/guides/jni-tips) · [Instrumented test setup](https://developer.android.com/training/testing/instrumented-tests)

[Course contents](index.md) · [Previous lesson](15-distinguish-refusal-and-vm-failure.md) · [Next lesson](17-inspect-apk-native-abis.md)
