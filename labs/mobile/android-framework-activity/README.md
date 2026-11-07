# Android screen with a shared C activity

Use Kotlin for the Android screen and C for the existing application rule. The Java Native Interface (JNI) carries one integer each way. See the [Android JNI guide](https://developer.android.com/ndk/guides/jni-tips) for the platform boundary.

## Prepare the project

1. Install Android Studio. In SDK Manager install a supported Android SDK, an emulator image, NDK (Side by side), and CMake. Use an NDK/CMake combination that accepts C23.
2. Create an Empty Activity project using Kotlin and Compose. Keep its generated Gradle/plugin versions. Run the unchanged template on the emulator first.
3. Keep this Bits2Banking checkout and the Framework checkout available. This lab's CMake paths refer back to the existing C files; do not copy their implementation into Kotlin.
4. Add `NativeActivity.kt` and `ActivityScreen.kt` to the app's Kotlin sources. Preserve their package `org.umicom.learning.activity`. In the generated activity, import `org.umicom.learning.activity.ActivityScreen` and call `ActivityScreen()` inside its existing `setContent` and theme.
5. Edit the existing `android` block in the app module's `build.gradle.kts`. Merge these settings with that block; do not create a second competing block.

~~~kotlin
android {
    defaultConfig {
        externalNativeBuild {
            cmake {
                arguments += "-DUMICOM_FRAMEWORK_INCLUDE_DIR=C:/umicom/Umicom-Applications/framework/include"
            }
        }
    }
    externalNativeBuild {
        cmake {
            path = file("C:/umicom/Umicom-Bits2Banking/labs/mobile/android-framework-activity/CMakeLists.txt")
        }
    }
}
~~~

These are example Windows locations. On another machine substitute the two real checkout paths. Gradle uses the NDK toolchain and packages the shared library for the selected Android ABI. See [linking a native library](https://developer.android.com/studio/projects/gradle-external-native-builds).

## Observe and diagnose

Sync Gradle, then Run. Press Complete exercise: 0 should become 1. Rotate the emulator: `rememberSaveable` should retain the value through activity recreation. It is not a long-term database.

If `UnsatisfiedLinkError` names `btb_activity`, inspect the build and APK ABI contents. If it names `NativeActivity.next`, compare the Kotlin package/class/method with the exported C symbol. Renaming the package requires changing both declarations.

The JNI function never stores `JNIEnv`, a Java object or user data. It checks the signed input before calling the C bridge. All count decisions remain in the existing model. This lab uses Framework status declarations only; it does not link a Windows SDK into Android.

## Checks to perform

- Tap three times and expect 3.
- Rotate and expect 3.
- Restart a new activity session and distinguish restoration from durable persistence.
- Exercise 999, 1000, negative and excessive inputs through the host bridge tests.
- Use a screen reader to find the labelled button and count.

Emulator, device and UI results must be recorded separately from host C checks.

