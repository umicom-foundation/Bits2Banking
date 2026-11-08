<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/19-diagnose-the-first-failed-boundary.md

PURPOSE:
Diagnose the first failed native integration boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Diagnose the first failed native integration boundary

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

## Classify the observation

Native integration has several independent boundaries: package resolution, compiler invocation, library construction, asset packaging, symbol binding, ABI metadata and policy execution. The first demonstrated failure determines what to inspect next. A later test assertion may never run when an earlier library load fails.

## Keep evidence specific

Capture the exact command, source revision, dependency lockfile, Dart/Flutter version, native compiler, target and diagnostic. A generic statement that Flutter is broken hides the information needed to reproduce the problem. Keep expected outputs separate from observed outputs and retain earlier attempts rather than overwriting them.

## Exercise

Make a diagnosis table for five hypothetical failures: missing path dependency, unsupported compiler standard flag, missing native symbol, ABI version mismatch and invalid user name. For each, name the owning file or tool and the next read-only inspection. Do not deliberately damage your shared checkout to simulate the failure.

## Change one cause at a time

Fix a path problem before changing compiler flags, and confirm matching C/Dart source before changing a declaration. Broadly catching native exceptions as invalid names obscures real defects. Re-run the narrow failed boundary, then the appropriate consumer and target integration checks before broadening the claim.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](18-separate-native-and-browser-clients.md) · [Next lesson](20-record-a-mobile-service-qualification.md)
