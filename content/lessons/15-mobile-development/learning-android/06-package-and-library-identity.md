<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/06-package-and-library-identity.md

PURPOSE:
Explain the lesson: Match package, method and library names.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Match package, method and library names

## Set up
Use the Android activity lab in an Empty Activity Compose project. Install its required NDK and CMake from SDK Manager, merge the documented native-build settings into the existing Gradle block, then sync. Begin with the generated template if Android development is new.

An Android project has several names. A package names a group of Kotlin declarations. A shared-library name identifies compiled native code. A native method name identifies one callable function. Similar spelling does not make these names interchangeable.

## Read the three connections
1. Open `NativeActivity.kt` and note the package `org.umicom.learning.activity`.
2. Locate the `System.loadLibrary` argument and compare it with the native target in the lab's `CMakeLists.txt`.
3. Locate `external fun next`.
4. Compare the C export `Java_org_umicom_learning_activity_NativeActivity_next` character by character with the package, object and method.

The symbol is the C function's linker-visible name. This example uses conventional JNI naming. Keep its declarations together during a rename.

## Make a diagnostic table
Write two rows:
- Library cannot load: inspect the built library's name and the APK's matching architecture.
- Method cannot resolve: inspect the package, class/object, method and exported symbol.

In a disposable copy, change only the Kotlin package, rebuild and record the resulting diagnostic. Then restore the declaration or make the corresponding C export consistent. Do not change the original working lab merely to manufacture an error.

## Check understanding
Why might a library be present but a method still unavailable? Expected answer: finding the container does not guarantee that the expected symbol exists inside it.

If a native build fails first, repair that error before diagnosing runtime loading. Keep the first compiler diagnostic and exact target architecture. A successful Gradle sync alone does not show that the native library was compiled, packaged or loaded.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/NativeActivity.kt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-follow-the-call-across-jni.md) · [Next lesson](07-check-values-before-conversion.md)

