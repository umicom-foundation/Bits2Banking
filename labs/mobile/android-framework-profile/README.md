# Android strings with a shared C policy

This laboratory connects an Android Kotlin method to Framework's existing C profile-name service. It adds no screen and does not replace the earlier activity-counter lab. Kotlin declares the platform method; the application C export forwards to Framework; Framework converts the Java string and applies the same rule used by the Qt and Wt labs.

## Prepare a separate Android project

1. Install Android Studio and a supported Android SDK. In SDK Manager install NDK (Side by side), CMake 3.26 or newer, and an emulator image. Select a C23-capable NDK. Record the actual versions; this guide does not select a universal NDK/API/Gradle combination.
2. Create an Empty Activity project named NativeProfileLab in C:\umicom\projects\NativeProfileLab. Keep the generated Kotlin, Android Gradle Plugin, Compose and dependency versions. Run the unchanged template on one emulator before adding native code. This establishes only the template baseline.
3. Integrate the Framework adapter sources into C:\umicom\Umicom-Applications\framework and the lab into C:\umicom\Umicom-Bits2Banking. The adapter module is cmake/UmicomAndroidProfileName.cmake. Do not substitute an installed Windows library for NDK-produced objects.
4. Copy NativeProfile.kt into app/src/main/java/org/umicom/learning/profile. Copy NativeProfileInstrumentedTest.kt into app/src/androidTest/java/org/umicom/learning/profile. Preserve the declared package. Leave the generated Activity and theme unchanged.
5. In the existing app/build.gradle.kts android block, merge the following configuration. Keep one externalNativeBuild entry; if another native project is already configured, use a new lab project or deliberately compose both targets in one top-level CMake file.

~~~kotlin
android {
    defaultConfig {
        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                arguments += "-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework"
            }
        }
    }
    externalNativeBuild {
        cmake {
            path = file("C:/umicom/Umicom-Bits2Banking/labs/mobile/android-framework-profile/CMakeLists.txt")
            version = "3.26.4"
        }
    }
}
~~~

The CMake version above is an example: select the installed SDK CMake version if different, provided it is at least 3.26. Keep the generated AndroidX JUnit extension and runner dependencies, or add compatible androidTestImplementation entries through the project's version catalogue. The test imports AndroidJUnit4 and JUnit 4 assertions. See the [Android instrumented-test setup](https://developer.android.com/training/testing/instrumented-tests).

## Build, install tests and inspect results

Use Android Studio's Gradle sync first. In PowerShell, with one intended emulator/device selected:

~~~powershell
Set-Location C:\umicom\projects\NativeProfileLab
.\gradlew.bat :app:assembleDebug :app:assembleDebugAndroidTest
.\gradlew.bat :app:connectedDebugAndroidTest -Pandroid.testInstrumentationRunnerArguments.class=org.umicom.learning.profile.NativeProfileInstrumentedTest
~~~

Stop after an error. The second command installs and runs the test APKs on connected targets. Review each target in app/build/reports/androidTests/connected and the corresponding XML under app/build/outputs/androidTest-results/connected; exact report subdirectories depend on the generated plugin version. Expect ten named tests. A build that did not run the instrumented class is not a JNI execution pass. Physical device, emulator and CPU ABI results are separate evidence.

The native umicom configure/build/test commands currently supervise CMake and CTest. Use the Gradle commands above for this Android project; they are not interchangeable with desktop CTest.

## Follow one call

NativeProfile.canonical("Sam_007") returns "sam_007". Null, short strings, whitespace, leading digits, Unicode outside the ASCII policy, embedded NUL and overlong strings return null. A refusal does not change another value or write storage. A subsequent valid call still succeeds. VM allocation or linkage exceptions remain exceptions; do not catch every Throwable and label it an invalid name.

Framework reads the Java string length before copying at most 48 UTF-16 units. It rejects units that cannot be represented as ASCII, then delegates the exact byte span to UmiLocalProfileNameBytes. This preserves embedded NUL for policy rejection. It uses NewStringUTF only for the already validated ASCII output; it does not mistake arbitrary modified UTF-8 for ordinary UTF-8. No JNIEnv, Java reference or character pointer is retained. See [JNI guidance](https://developer.android.com/ndk/guides/jni-tips) and the [JNI function contracts](https://docs.oracle.com/en/java/javase/25/docs/specs/jni/functions.html).

## Diagnose the first failing boundary

- CMake cannot find the adapter: check the absolute Framework source root and that the new files were integrated together.
- C23 is rejected: inspect the selected NDK compiler and native CMake version before changing language flags.
- The library cannot load: inspect the APK with Android Studio's APK Analyzer and verify lib/<ABI>/libbtb_profile.so matches the target ABI.
- The native method cannot be found: compare package org.umicom.learning.profile, object NativeProfile, method canonical and the Java_org_umicom_learning_profile_NativeProfile_canonical export.
- The test class is not found: check androidTest source placement and the package/class filter; ordinary local JVM tests do not load this Android library.
- A valid name is refused: inspect the exact string, length and code points. Keep the ASCII rule shared; do not create a second Kotlin regex with different semantics.

## Host contracts are a separate check

Framework has optional 19-case host coverage using real JDK JNI declarations and a controlled function table. Enable UMICOM_BUILD_ANDROID_JNI_TESTS in a native Framework build with an installed JDK; no JVM runs in that fixture. Those checks cover call bounds and exception preservation. The ten Android tests cover real library loading and string values. Neither proves login, persistence, accessibility, a complete mobile SDK or store-release readiness.
