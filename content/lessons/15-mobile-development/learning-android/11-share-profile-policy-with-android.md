<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/11-share-profile-policy-with-android.md

PURPOSE:
Teach share one c name policy with android through the shared Framework JNI lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Share one C name policy with Android

## Prepare the lab

Install Android Studio, a C23-capable NDK, CMake 3.26 or newer and one emulator image. Create a separate Empty Activity project named NativeProfileLab under C:\umicom\projects, retain its generated tool versions, and run the unchanged template first. Integrate the primary Framework sources and Bits2Banking lab, then follow the lab README to place the Kotlin and instrumented-test files and merge externalNativeBuild into the existing Gradle block. This text module does not change the activity-counter screen.

[Complete lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/README.md)

## Separate the three responsibilities

The Kotlin object declares a platform call and loads its library. The application C file supplies the method name required by JNI. Framework handles string conversion and validation. Draw those three boxes and add the portable profile-name function beneath Framework. Only that final function decides allowed characters and canonical lowercase output. This separation makes the Android rule the same rule used by the Qt and Wt labs.

## Follow a successful value

Begin with Sam_007. The Java string reaches Java_org_umicom_learning_profile_NativeProfile_canonical, which forwards to UmiAndroidProfileNameCanonical. The adapter creates an exact ASCII span and calls UmiLocalProfileNameBytes. The expected result is sam_007. Read each function in that order before building; identify where data is borrowed and where a new result is created.

## Exercise a refusal without changing policy

Compare Sam_007, 1Sam and Sam Smith in the instrumented tests. The first succeeds; the latter two are refused. Do not add a Kotlin regular expression to make a rejected value pass: that would create another policy. If the requirements change, change the shared C contract and its tests first, then review every consumer. A canonical name does not establish account ownership or authenticate anyone.

## Check and recover

Build the lab and run canonicalisesAscii and refusesInvalidAscii through the instrumented class. Record the actual outcomes beside the predictions. If a native method cannot be resolved, inspect package and symbol identity before changing validation. If both desktop and Android disagree with the documented policy, inspect the selected Framework revisions; an old binary may be loading a different implementation.

## Build and observe

Run each command separately and stop on errors. The instrumented task installs and runs test APKs on connected targets. Keep the ten named results and target identity; no result is implied by these instructions.

~~~powershell
Set-Location C:\umicom\projects\NativeProfileLab
.\gradlew.bat :app:assembleDebug :app:assembleDebugAndroidTest
.\gradlew.bat :app:connectedDebugAndroidTest -Pandroid.testInstrumentationRunnerArguments.class=org.umicom.learning.profile.NativeProfileInstrumentedTest
~~~

Native Umicom CLI CMake/CTest commands do not replace this Gradle workflow. Review app/build/reports/androidTests/connected for the actual result. Keep host, emulator and device evidence separate.

## Read the implementation

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-profile/profile_jni.c) · [Android JNI guidance](https://developer.android.com/ndk/guides/jni-tips) · [Instrumented test setup](https://developer.android.com/training/testing/instrumented-tests)

[Course contents](index.md) · [Previous lesson](10-check-a-mobile-workflow.md) · [Next lesson](12-read-bounded-java-strings.md)
