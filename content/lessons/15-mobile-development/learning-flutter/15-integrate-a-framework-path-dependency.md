<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/15-integrate-a-framework-path-dependency.md

PURPOSE:
Integrate the Framework package into a Flutter harness

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Integrate the Framework package into a Flutter harness

## Prepare the native exercise

Use a compatible Dart SDK and native compiler, with Bits2Banking beside the primary Framework checkout. Keep the complete Framework source tree: the local package builds its canonical C implementation. Read the lab README before resolving packages, then run each command separately and stop on an unexpected error. These host commands do not run an Android or Apple device test.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\mobile\flutter-framework-profile"
dart --version
dart pub get
dart analyze
dart run bin/profile.dart Course_User
dart test test/profile_consumer_test.dart
```

The valid example should print canonical: course_user. The four consumer cases should exercise real native calls. These are expected outcomes to verify; no executed result is implied. Follow the separate device steps in the README when the lesson asks for target qualification.

## Use a fresh practice application

Create a separate Flutter practice app and keep your product sources untouched. Add the local umicom_profile_name path dependency to its existing pubspec. The path must point to the Framework package inside a complete matching checkout. Keep generated Flutter dependencies and add the integration_test SDK dependency under the existing development section.

## Preserve the native source boundary

The Flutter harness consumes the same package as the standalone Dart exercise. It does not copy profile_name.c or implement a second validator in a widget. The build hook compiles the canonical source for the selected target, while Flutter supplies the application and test runner environment.

## Exercise

Follow the lab README to copy device/profile_name_test.dart into the new app’s integration_test folder. Inspect the imports before running it. Explain why copying this test does not replace lib/main.dart and why a headless native-call check does not establish that a future form is usable.

## Recover from dependency mistakes

If resolution selects the wrong checkout, fix the explicit path and retain the previous diagnostic and lockfile. If the package directory was copied without the rest of Framework, restore the complete source layout. Do not hide missing C inputs by adding a divergent local implementation to the harness.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](14-use-a-native-service-from-an-isolate.md) · [Next lesson](16-qualify-an-android-native-asset.md)
