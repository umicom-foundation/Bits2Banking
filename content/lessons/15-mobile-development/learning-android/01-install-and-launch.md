# Set up Android development and launch a small app

An Android application is a program that runs in the Android operating system. In this course you will build a screen that records practice-lesson clicks. You will learn how a project becomes an app before studying more complex features.

No previous Android course is required. You need a Windows or Linux computer supported by Android Studio, internet access for tools and dependencies, and enough free disk space for the Android SDK and an emulator image. An SDK is a software development kit: libraries and tools for a platform. An emulator runs a virtual Android device on your development computer. Reading these lessons does not require installation.

## Setup recap: Install and verify the environment

1. Download Android Studio from its official site and follow [the installation instructions](https://developer.android.com/studio/install). Check the current hardware requirements before downloading an emulator image.
2. Start Android Studio and complete its setup wizard. Install the recommended Android SDK tools and platform. Use the bundled Java runtime initially; changing Java versions is unnecessary for this first project.
3. Open **Device Manager**. Create a virtual device, choose a supported phone profile, download an appropriate system image, and start the device. Hardware virtualisation must be available for an accelerated emulator. If the computer cannot run one, follow the official connected-device guide to use your own Android phone with USB debugging enabled.
4. Wait for the Android home screen. A device entry alone does not mean that the emulator has started.

The longer [Android beginner learning route](https://developer.android.com/courses/android-basics-compose/course) explains the tools. For command-line basics in this library, see [Open a terminal](../../08-system-administration/03-open-powershell-or-linux-terminal.md).

## 2. Create a project in a folder you choose

1. Select **New Project**, then **Empty Activity**, the template using Jetpack Compose. Compose describes a screen using Kotlin functions.
2. Name the project `Umicom Learning Practice`. Set the package name to `org.umicom.learning` and choose your own save folder, for example `C:\umicom-learning\android-practice` on Windows.
3. Keep the template's supported minimum SDK and build settings. Note the minimum SDK you selected; your virtual device must support it.
4. Finish and allow the initial Gradle synchronisation to complete. Gradle is the build tool. Synchronisation resolves the project's configuration and dependencies.
5. Find `app/src/main/java/org/umicom/learning/MainActivity.kt` in the project. Some templates organise source under `kotlin` instead of `java`; use the path actually created.

Do not create a second `MainActivity` in another source folder. One activity class is the Android entry point for this example.

## 3. Run the unchanged template first

Choose the virtual device in the device selector and click **Run** for the `app` configuration. The template's greeting should appear on that device. This establishes that installation, the SDK and the initial project can work together. If the build fails, open Build Output and read the first error before changing application source.

To build from the project's terminal without launching a device, use:

```powershell
# PowerShell, in the project folder containing gradlew.bat
.\gradlew.bat assembleDebug
```

```bash
# bash, in the project folder containing gradlew
./gradlew assembleDebug
```

The wrapper downloads the project's declared Gradle version when required. `assembleDebug` builds a debug package; it does not install or launch it. The generated project supplies this wrapper. There is no need to write a separate shell script for the lesson.

## 4. Understand the project map

| File or folder | Purpose |
| --- | --- |
| `MainActivity.kt` | Activity and initial screen code |
| `AndroidManifest.xml` | Declares application components and permissions |
| `app/build.gradle.kts` | Module build settings and dependencies |
| `app/src/main/res` | Android resources such as text and images |
| `gradlew` / `gradlew.bat` | Starts the project's build-tool version |

The sequence is **source and resources → Gradle build → app package → device installation → activity → visible screen**. A successful build and a working screen are separate observations.

## Exercise and recovery

Close the app on the virtual device, then use Run again. Confirm that the expected app launches. If the device list is empty, start or connect a device. If the first build cannot download dependencies, check connectivity and the first Gradle error. If Android Studio points to an unavailable SDK, correct the SDK location through its settings rather than copying another computer's build cache.

The next lesson replaces the greeting with [Umicom's learning counter](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-lesson-counter/MainActivity.kt). This is an educational frontend example, not an Android release of Umicom Studio or a connection to a production learning database.

[Course contents](index.md) · [Next: screen state and button events](02-state-events-and-checks.md)
