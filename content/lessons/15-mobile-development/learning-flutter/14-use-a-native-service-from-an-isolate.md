<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/14-use-a-native-service-from-an-isolate.md

PURPOSE:
Use a native service from another isolate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use a native service from another isolate

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

## Understand the boundary

An isolate has its own Dart execution state. The supplied test calls normalizeProfileName through Isolate.run and returns an owned string. The native policy is synchronous, uses local temporary storage and retains no pointer. The exercise does not share an arena or a mutable native buffer between isolates.

## Keep the payload owned

The closure creates its own native allocations inside the worker call. It returns managed text after decoding, so the caller receives a value independent of the freed temporary buffers. Sending a raw address to another isolate would introduce a different lifetime and synchronization problem that this package does not support.

## Exercise

Read the isolate test and identify the values captured and returned. Extend the exercise with two independent calls using distinct names and compare their results. Record whether execution used the actual native binding. Explain why a thread-safe policy alone would not make an arbitrary stateful native database connection safe to share.

## Choose work size deliberately

Name validation is tiny and does not require a worker for responsiveness. The isolate example teaches ownership, not a performance recommendation. For larger future services, measure cost and define cancellation, errors and disposal before moving work away from the UI isolate.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](13-test-the-native-binding-on-the-host.md) · [Next lesson](15-integrate-a-framework-path-dependency.md)
