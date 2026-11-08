<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/14-match-native-method-identity.md

PURPOSE:
Teach match android package and native method identity through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Match Android package and native method identity

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## Locate four different names

The Kotlin package is org.umicom.learning.profile. Its object is NativeProfile, its external method is canonical, and its library name is btb_profile. The C export combines the package, object and method into Java_org_umicom_learning_profile_NativeProfile_canonical. The shared-library file name is a separate loading decision. Write all four names before renaming any of them.

## Trace loading before calling

System.loadLibrary runs when the Kotlin object is initialised. A library-loading failure prevents the native method from running at all. A method-resolution failure can occur after the library loads. Distinguish the two diagnostics by the name in UnsatisfiedLinkError and the call stack. A null result from a successfully called method is a different outcome: the input was refused, or the VM returned an allocation failure.

## Try a reversible mismatch

In a disposable copy, rename only the method declaration and its test call, leaving the C export unchanged. Build and run one test, then retain the resulting method-resolution diagnostic. Restore both names together and run again. This experiment changes the binding identity without changing the C policy; it shows why editing validation is not a remedy for a missing native method.

## Check release assumptions

The lab qualifies a debug test target. If a later release build enables name shrinking or obfuscation, review the native-method preservation rules and test that release variant separately. Do not infer release lookup from a debug pass. Keep the JNI export and the Kotlin declaration together in code review, while keeping reusable conversion inside Framework.

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

[Course contents](index.md) · [Previous lesson](13-build-c-for-the-android-target.md) · [Next lesson](15-distinguish-refusal-and-vm-failure.md)
