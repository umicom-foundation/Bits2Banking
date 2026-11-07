# Flutter lesson counter

Learn how a visible screen responds to button actions and how its temporary state survives a rebuild. This introductory Dart widget is not a persistent progress service. A real Umicom client should use Framework services for shared progress and storage.

## Setup

Install Flutter and the tools for your chosen target. In a new terminal run `flutter doctor` and resolve the reported requirements for that target. Run `flutter devices` to see available targets. The [first Flutter chapter](../../../content/lessons/15-mobile-development/learning-flutter/01-install-and-run.md) explains installation and the project structure.

Choose an empty working directory. In PowerShell:

~~~powershell
flutter create --project-name lesson_counter lesson_counter
Set-Location "./lesson_counter"
Copy-Item "C:/umicom/Umicom-Bits2Banking/labs/mobile/flutter-lesson-counter/main.dart" "./lib/main.dart"
Copy-Item "C:/umicom/Umicom-Bits2Banking/labs/mobile/flutter-lesson-counter/counter_test.dart" "./test/counter_test.dart"
Copy-Item "C:/umicom/Umicom-Bits2Banking/labs/mobile/flutter-lesson-counter/lifetime_test.dart" "./test/lifetime_test.dart"
flutter test test/counter_test.dart test/lifetime_test.dart
flutter devices
~~~

The copies replace only the generated main.dart in this new practice project. Keep your own projects separate. In bash use `cd lesson_counter` and `cp` with the actual paths to the three supplied files. The project name matters because tests import `package:lesson_counter/main.dart`.

Launch with `flutter run -d DEVICE_ID`, replacing DEVICE_ID with one listed by `flutter devices`. Do not copy the placeholder literally. iPhone builds require a macOS/Xcode environment; choosing a browser target does not qualify an iPhone release.

## Expected behaviour

1. The initial label reads Completed: 0 of 3 and Reset practice is disabled.
2. Activate Complete a practice lesson three times.
3. The count reaches three and the completion button becomes disabled.
4. Activate Reset practice; the count returns to zero and completion is enabled.

The explicit test paths avoid running the untouched generated template's counter test, whose assumptions describe a different screen. Retain that generated test as an example until you deliberately replace it in your practice project.

counter_test.dart checks the button journey. lifetime_test.dart checks two different situations: a theme rebuild retains the same mounted state; removing that widget and creating a new application starts a fresh count. A hot reload is not a storage test.

If a test cannot find a label, confirm main.dart was copied and the import package matches. If the test finds stale text after an action, check whether a frame was pumped before reading the result. See the [Flutter interaction test guide](https://docs.flutter.dev/cookbook/testing/widget/tap-drag) for the test API. These checks are authored examples and need to be run on your toolchain.
