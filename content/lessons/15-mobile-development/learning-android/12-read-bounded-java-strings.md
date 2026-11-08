<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/12-read-bounded-java-strings.md

PURPOSE:
Teach read bounded java strings without truncation through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read bounded Java strings without truncation

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## Count code units before copying

Java strings expose UTF-16 code units to JNI. A displayed character and a code unit are not always the same thing. This naming policy allows only ASCII, so the adapter can first bound the number of code units to 3 through 48. It then reads no more than 48 units into local storage. An overlong string is refused before its contents are copied.

## Preserve the full input meaning

Consider abc followed by a NUL and tail. A C string scan could see only abc and accidentally accept a different name. The adapter copies all selected units and passes an explicit length to UmiLocalProfileNameBytes. The embedded NUL therefore remains part of the value and is rejected. Write down the input length and the visible prefix separately; they answer different questions.

## Distinguish representation from policy

A non-ASCII unit, such as an accented letter or a surrogate, cannot be narrowed into this ASCII representation. The adapter refuses it before casting. The C policy still owns decisions about digits, separators and the first character. GetStringUTFChars uses modified UTF-8, so replacing this path with that API requires reviewing the encoding contract rather than assuming every byte sequence is ordinary UTF-8.

## Exercise the boundary

Run maximumLength, refusesLongValues, refusesEmbeddedNul and refusesUnicodeOutsidePolicy. Inspect their literal escaped inputs in the Kotlin source. The expected maximum-length result is 48 lowercase a characters; none of the invalid cases returns a shortened accepted prefix. If a test accepts a prefix, inspect every implicit terminator conversion in the call chain. Keep the original failing value in the regression.

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

[Course contents](index.md) · [Previous lesson](11-share-profile-policy-with-android.md) · [Next lesson](13-build-c-for-the-android-target.md)
