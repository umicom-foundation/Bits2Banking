<!--
Umicom Bits2Banking
File: labs/mobile/flutter-framework-profile/README.md

PURPOSE:
Teach a real Framework native binding and distinguish host Dart from Flutter device qualification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Framework profile names from a mobile client

This headless exercise calls Framework through its local Dart native-assets package. Dart owns temporary buffers; C owns the naming policy. No screen, account, database or authentication flow is created. The existing Flutter counter lab remains a separate introduction to widgets.

## Run the host exercise

Keep Bits2Banking beside Umicom-Applications, whose framework directory contains the matching binding. The supplied path dependency resolves that primary checkout. If your layout differs, edit only the dependency path in this practice package; retain the Framework package inside its complete source tree.

Install a Dart SDK compatible with the package and a native compiler. From this directory, run each command separately and stop on an unexpected error:

```powershell
dart --version
dart pub get
dart analyze
dart run bin/profile.dart Course_User
dart test test/profile_consumer_test.dart
```

The valid command should print canonical: course_user. Running with no/slash should print a refusal and return exit code 1; that is an intentional invalid-name observation. Zero arguments return usage and exit code 2. Native load or ABI errors are not converted into a successful name. The consumer tests are expected checks, not claimed results.

## Qualify a Flutter device separately

1. Create a fresh Flutter practice app named framework_profile_app outside your product sources. Run flutter doctor and flutter devices; resolve requirements for the actual Android or Apple target.
2. In that app’s pubspec.yaml, add the following dependency, using your actual Framework path. Under its existing dev_dependencies, add integration_test from the Flutter SDK. Keep generated flutter_test and other existing entries.

```yaml
dependencies:
  # Keep existing entries here.
  umicom_profile_name:
    path: C:/umicom/Umicom-Applications/framework/bindings/dart/umicom_profile_name
dev_dependencies:
  # Keep existing entries here.
  integration_test:
    sdk: flutter
```

3. Create integration_test in the new app and copy device/profile_name_test.dart into it. This is a test entry point; it adds no product layout and does not replace lib/main.dart. On macOS use the actual POSIX paths.
4. From the new app, resolve packages and run the test against an available native device. Replace DEVICE_ID with the exact identifier reported by flutter devices.

```powershell
flutter pub get
flutter devices
flutter test integration_test/profile_name_test.dart -d DEVICE_ID
```

The three device cases call the actual packaged native asset. They check canonicalization, refused bytes and retained Dart text. They do not test a visible form, accessibility, signing, store distribution or persistence. An emulator result is not a physical-device result; an Android result is not an iPhone result. Apple builds require a matching macOS/Xcode setup.

## Read the boundary

Follow bin/profile.dart into Framework’s lib/umicom_profile_name.dart, then lib/src/native_bindings.dart and adapters/ffi/profile_name.c. The adapter checks output capacity before calling the existing UmiLocalProfileNameBytes. Native status numbers are carried as int32_t, and byte counts use the target size_t type. A Dart string may contain more than one byte per character, so the native call receives an explicit UTF-8 byte length.

The Framework build hook compiles its canonical source for the requested target. A desktop static archive is not reused as an Android or iPhone library. Browser dart:ffi is outside this exercise. Keep browser integration on its separate web path.

## Recover from the first failure

A missing local package points to the dependency path. A package-resolution error needs the Dart version and full diagnostic. A compiler error needs the compiler identity and selected target. A missing asset/symbol needs the hook output, stable asset ID and exported C names. Preserve these observations before changing more than one variable.

The device supplement is excluded from this standalone Dart package’s analysis because its Flutter SDK imports belong to the generated Flutter harness. That exclusion is not a test pass; run the copied file in the Flutter app explicitly.

Read the [Framework package guide](../../../../Umicom-Applications/framework/bindings/dart/umicom_profile_name/README.md), [Flutter native-assets guide](https://docs.flutter.dev/interop/bind-native-code) and [Flutter integration testing guide](https://docs.flutter.dev/testing/integration-tests). Continue in [Learning Flutter](../../../content/courses/learning-flutter/index.html).
