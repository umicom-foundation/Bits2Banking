<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/13-test-the-native-binding-on-the-host.md

PURPOSE:
Test the real native binding on the host

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test the real native binding on the host

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

## Know what runs

The Framework Dart test imports the public package and calls the actual native asset. It is not a mock of the naming policy. Its cases cover valid bounds, encoded invalid text, retained results, repeated calls and use from another isolate. The C suite separately checks raw pointer and capacity contracts.

## Build before trusting a result

Package resolution, native compilation, asset resolution and test execution are distinct steps. A successful pub get does not establish any of the later steps. Keep the selected Dart SDK, native compiler, Framework revision and resolved package versions with the test output. An authored case has no observed result until you run it.

## Exercise

Run the Framework package tests, then the independent consumer tests. Compare their imports and coverage. The consumer checks that the public package can be used from another project; the Framework suite exercises more input boundaries. Record a separate result for each command and preserve skipped or failed coverage honestly.

## Interpret repeated calls carefully

The repeated-call case checks independent results across many allocations. It is useful lifetime evidence, but it does not prove the absence of every memory leak. Use suitable native memory tooling for that separate claim, and do not substitute a loop count for a measured resource result.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](12-return-owned-results-and-visible-errors.md) · [Next lesson](14-use-a-native-service-from-an-isolate.md)
