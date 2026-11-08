<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/11-review-output-capacity-and-failure-atomicity.md

PURPOSE:
Review output capacity and failure atomicity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Review output capacity and failure atomicity

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

## Read the C adapter first

The underlying profile function expects a fixed-capacity output array. A foreign caller can supply any pointer, so the adapter adds an explicit capacity parameter. It rejects null pointers and insufficient capacity before calling the policy. The policy validates the entire name before copying any successful result.

## Understand unchanged output

On refusal, every output byte stays unchanged. On success, exactly the required capacity is written, including the terminator and zero padding. Extra caller capacity is not filled. This lets a client preserve earlier state until validation succeeds and makes buffer boundaries observable in a regression test.

## Exercise

Read the small-capacity, excess-capacity, partial-overlap and failure-unchanged C cases. Each starts with recognizable surrounding bytes. Predict which bytes may change and which must remain identical. Compare this with a Dart-level result test: the latter proves presentation behavior but cannot replace the lower-level guard-byte check.

## Do not infer pointer safety from a count

A capacity value is a caller promise that the pointer designates that much writable storage. The adapter cannot discover the true size of an arbitrary foreign allocation. Correct type declarations and scoped allocation remain necessary even when the C interface validates its numeric bounds.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](10-own-native-buffers-for-one-call.md) · [Next lesson](12-return-owned-results-and-visible-errors.md)
