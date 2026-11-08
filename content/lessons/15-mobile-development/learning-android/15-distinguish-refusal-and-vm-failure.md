<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/15-distinguish-refusal-and-vm-failure.md

PURPOSE:
Teach distinguish invalid input from a vm failure through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish invalid input from a VM failure

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## A nullable result has a narrow meaning

The method accepts a nullable String and normally returns null for a refused name. That is useful for form feedback because invalid input is expected. It does not make every failure an invalid name. A missing library is a linkage error; a VM allocation problem may throw; the JNI specification also permits some allocation failures to return null without an exception. Do not promise more detail than the boundary supplies.

## Preserve an existing exception

The Framework adapter checks for a pending VM exception before reading the string, and after JNI reads. It stops without clearing the exception. Continuing to call arbitrary JNI functions while an exception is pending can obscure the original cause. The host fixture has controlled pending, length-read, region-read and allocation failures so these paths can be inspected independently.

## Exercise recovery after ordinary refusal

Run refusalDoesNotPoisonNextCall. The first invalid input must return null; SECOND must then return second. There is no global error flag or retained Java reference in this adapter. Compare this with a broad catch of Throwable in Kotlin: such a catch could disguise a loading failure and prevent useful diagnosis. Keep ordinary validation handling separate from operational error reporting.

## Explain ownership in your own words

JNIEnv belongs to the currently attached thread. The input is borrowed for the call; the returned string is a new local reference managed by the VM. The adapter stores neither. Add a short review note identifying why no character-buffer release call is needed: GetStringRegion copies into caller-owned stack storage. Do not apply this conclusion to APIs that return pinned or borrowed character pointers.

## Build and observe

Run each command separately and stop on errors. The instrumented task installs and runs test APKs on connected targets. Keep the ten named results and target identity; no result is implied by these instructions.

~~~powershell
Set-Location C:\umicom\projects\NativeProfileLab
.\gradlew.bat :app:assembleDebug :app:assembleDebugAndroidTest
.\gradlew.bat :app:connectedDebugAndroidTest -Pandroid.testInstrumentationRunnerArguments.class=org.umicom.learning.profile.NativeProfileInstrumentedTest
~~~

Native Umicom CLI CMake/CTest commands do not replace this Gradle workflow. Review app/build/reports/androidTests/connected for the actual result. Keep host, emulator and device evidence separate.

## Read the implementation

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/NativeProfile.kt) · [Android JNI guidance](https://developer.android.com/ndk/guides/jni-tips) · [Instrumented test setup](https://developer.android.com/training/testing/instrumented-tests)

[Course contents](index.md) · [Previous lesson](14-match-native-method-identity.md) · [Next lesson](16-run-android-native-contract-tests.md)
