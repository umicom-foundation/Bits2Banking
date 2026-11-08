<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/05-trace-dart-to-the-c-policy.md

PURPOSE:
Trace a Dart call to the shared C policy

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a Dart call to the shared C policy

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

## Start with a concrete result

The counter project taught widget state. The native profile exercise introduces a different boundary: a Dart caller asks Framework to normalize a local profile name. Run the host example with Course_User and expect course_user. This is name validation only. There is no account, password, database or sign-in session behind that output.

## Follow the ownership chain

Read bin/profile.dart, then normalizeProfileName in the Framework Dart package. The public function calls a native binding declaration, which resolves the exported UmiInteropProfileNameNormalize symbol. That C adapter checks capacity and delegates to UmiLocalProfileNameBytes. All letter, digit, separator and leading-letter rules remain in the existing policy.

## Exercise

Draw five boxes for the consumer, Dart wrapper, native declaration, C adapter and policy. Add one arrow per real function call. For each box, record whether it owns validation rules, temporary memory or presentation. Then run no/slash and explain why the consumer reports refusal instead of repairing the name silently.

## Extend without duplicating rules

A Flutter form can present the returned result, but it should not grow a second regular expression that can drift from C. Keep product text and interaction in the frontend, shared decisions in Framework, and platform transport in a narrow adapter. This exercise supplies no new screen or approved form layout.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](04-test-widget-lifetime.md) · [Next lesson](06-read-a-native-package-graph.md)
