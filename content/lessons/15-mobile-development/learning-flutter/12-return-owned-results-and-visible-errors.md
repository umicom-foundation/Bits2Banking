<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/12-return-owned-results-and-visible-errors.md

PURPOSE:
Return owned results and visible errors

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Return owned results and visible errors

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

## Separate refusal from infrastructure failure

An invalid name is an ordinary policy result: status 1, accepted false and no canonical text. A missing native asset, incompatible ABI or allocation failure is an integration problem. The wrapper keeps those failures visible instead of converting every exception into an invalid-name message.

## Inspect the result model

ProfileNameResult is immutable. Its canonicalName is a Dart-owned string for success and null for refusal. The public accepted getter derives from status zero. No mutable output buffer or stale text from a previous request survives as a successful response after validation fails.

## Exercise

Run a valid input followed by no/slash. Retain the first result in a local variable and inspect it after the failed call. Then review the public consumer test that checks a refused result has no text. Explain why clearing a visible form field is a frontend choice while returning null is part of the service contract.

## Present errors at the right layer

A future approved Flutter screen should distinguish a user-correctable name from a native loading failure that needs environment repair. Do not catch all errors and display success or silently retry indefinitely. Keep source revision, target and diagnostics available when investigating an integration failure.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](11-review-output-capacity-and-failure-atomicity.md) · [Next lesson](13-test-the-native-binding-on-the-host.md)
