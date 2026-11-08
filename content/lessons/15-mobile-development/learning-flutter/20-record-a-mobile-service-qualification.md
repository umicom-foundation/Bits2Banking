<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/20-record-a-mobile-service-qualification.md

PURPOSE:
Record a mobile service qualification honestly

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record a mobile service qualification honestly

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

## Assemble separate evidence rows

A useful qualification record distinguishes C contract tests, Framework Dart tests, independent consumer tests and Flutter device tests. Each row needs source identity, command, environment, observed result and uncovered behavior. Do not collapse these into one green status because they exercise different ownership boundaries.

## Use the current coverage deliberately

The C suite checks capacity and unchanged output. Dart tests add encoding, temporary allocation lifetime and native resolution. The consumer verifies public-package use. Device tests add target compilation and packaging. None of these creates an account or proves a visible form’s accessibility, persistence or authentication security.

## Exercise

Build your record from the commands you actually ran. Include a failed or skipped row when applicable, and leave unavailable targets unexecuted. Add the exact package versions resolved for the run. Compare the retained-result observation across host and device without assuming equal binaries or environments.

## Plan the next product step

Before adding a profile screen, choose an approved layout and define its real user journey: input, validation message, cancellation and recovery. Reuse this shared service for naming and identify separate services for storage or authentication. Keep those future tasks open until their implementation and appropriate native evidence exist.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](19-diagnose-the-first-failed-boundary.md)
