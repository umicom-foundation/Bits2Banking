<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/13-package-the-android-lab.md

PURPOSE:
Package the same Qt lab for Android

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Package the same Qt lab for Android

## Before starting

Prepare a Qt Android kit, its supported Android SDK, NDK and Java toolchain, and the Framework source checkout. Use the kit documentation to select matching versions; do not reuse the desktop compiler. Start with one ABI, the binary calling convention and CPU target used by a device. Reading is possible without an Android device; installation and touch checks require an emulator or device you control.

## Use the target wrapper

Run from the profile lab. Replace every example SDK, NDK and Qt path with an installed matching path. The Qt helper creates the Android application target; the view and C policy are built as relocatable static libraries for that target.

~~~powershell
& 'C:/Qt/your-version/android_arm64_v8a/bin/qt-cmake.bat' -S . -B build-android -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DANDROID_SDK_ROOT=C:/Android/Sdk' '-DANDROID_NDK_ROOT=C:/Android/Sdk/ndk/your-ndk-version' '-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework' -DBUILD_TESTING=OFF
cmake --build build-android --parallel 2
cmake --build build-android --target apk
~~~

## Inspect the package stage

Compilation produces native code; the apk target also packages the Android application. Keep the packaging output and locate the exact APK it reports. If Gradle or a Java tool fails, preserve that error separately from a successful C compilation. Do not claim that a produced APK has been installed or launched. Qt also provides an aab target for an Android App Bundle; distribution and signing need their own review.

## Install and observe deliberately

Use Qt Creator with the configured Android kit and a selected test device, or your established Android deployment process. Confirm which device receives the package before installing. Launch the lab, enter Alice_7 with the on-screen keyboard, tap Check name and record the lowercase result. Repeat invalid input, rotation and returning from the background. No password or broker connection belongs in this exercise.

## Exercise and worked answer

The APK was produced for arm64-v8a, but the chosen emulator expects a different ABI. Is renaming the APK a fix? No. Select a matching device or build with the appropriate Qt kit in a separate folder. The policy source stays the same; the compiled libraries and package are target-specific.

## Recover from build failure

Check the selected Qt kit, SDK and NDK together before changing source. For a failure that names a missing Framework module, verify BTB_FRAMEWORK_SOURCE points to the same revision used by the desktop source lab. A desktop SDK path cannot replace that target compilation.

## Reference

[Qt Android command-line build and package targets](https://doc.qt.io/qt-6.8/android-building-projects-from-commandline.html). Consult the documentation for the exact kit you install.

## Read the source

[labs/framework/qt-profile/CMakeLists.txt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/CMakeLists.txt). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Separate browser validation from server authority](12-browser-boundaries-and-trust.md) · [Next: Build and observe the lab on iOS](14-build-and-observe-on-ios.md)
