<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/16-qualify-an-android-native-asset.md

PURPOSE:
Qualify the native asset on Android

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify the native asset on Android

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

## Select the actual target

Use flutter doctor to inspect Android tooling and flutter devices to identify an available native target. Run the supplied integration test with that exact device identifier. A host Dart VM test exercises the host library; an Android run exercises a separately compiled and packaged native asset.

## Track architecture and packaging

The same C source can produce different binaries for different ABIs. The hook receives the requested target configuration and uses its toolchain. A desktop library cannot be copied into an Android package merely because its exported function names match. Retain the device or emulator identity and architecture with the result.

## Exercise

Run the three device cases and record normalization, invalid-byte refusal and retained-result behavior separately. Compare the output with the host cases. If you use an emulator, label it as such. A physical-device run is additional evidence, not an automatic consequence of the emulator pass.

## Diagnose before changing policy

A missing shared library or symbol is a build/package problem. An invalid result for a correctly encoded accepted name is a service or binding observation. Preserve the first diagnostic and target configuration before editing the C rule. This headless test does not cover permissions, visible controls, lifecycle restoration or store distribution.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](15-integrate-a-framework-path-dependency.md) · [Next lesson](17-qualify-apple-simulator-and-device.md)
