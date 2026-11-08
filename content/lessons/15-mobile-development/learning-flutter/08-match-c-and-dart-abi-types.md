<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/08-match-c-and-dart-abi-types.md

PURPOSE:
Match C and Dart ABI types exactly

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Match C and Dart ABI types exactly

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

## Understand the binary contract

An application binary interface describes how values cross a native call boundary. Source-language types that sound similar are not automatically interchangeable. The C adapter returns int32_t status, exposes uint32_t metadata, and accepts size_t byte counts. Dart declares Int32, Uint32 and Size in the corresponding native signatures.

## Avoid enum assumptions

The underlying Framework service returns UmiStatus, a C enum. The FFI adapter converts that result to a fixed-width integer so Dart does not guess the compiler’s enum representation. The adapter also exposes an ABI version and required output capacity. The Dart wrapper checks both before allocating buffers or invoking normalization.

## Exercise

Annotate every parameter in UmiInteropProfileNameNormalize with direction, byte width rule and owner. Explain why Size follows the target ABI while Int32 remains fixed width. Compare an Android 32-bit target with a 64-bit desktop without assuming that a desktop test covers both calling conventions.

## Diagnose a mismatch

An ABI version refusal is a source/package consistency problem, not an invalid user name. Use matching C and Dart revisions. Never work around a missing symbol by changing the declared return type until a call stops crashing; that can conceal a binary mismatch while corrupting later values.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](07-follow-native-asset-identities.md) · [Next lesson](09-count-encoded-bytes-explicitly.md)
