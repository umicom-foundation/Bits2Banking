<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/07-follow-native-asset-identities.md

PURPOSE:
Follow a native asset from build hook to symbol

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a native asset from build hook to symbol

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

## Name two different identities

The asset ID identifies the native library supplied by the package. A symbol identifies a function inside that library. This binding uses package:umicom_profile_name/src/native_bindings.dart as its asset ID and UmiInteropProfileNameNormalize as one symbol. A correct library with the wrong symbol name still cannot satisfy the declaration.

## Read the hook and declaration together

Open hook/build.dart beside lib/src/native_bindings.dart. The builder names src/native_bindings.dart as the asset and uses a stable library basename. The Native annotations explicitly select that asset and each exported C symbol. Windows exports are enabled by UMICOM_PROFILE_FFI_BUILD; the ordinary CMake static target needs no DLL-import declaration.

## Exercise

Write a small identity table containing the package name, asset name, complete asset ID, native library basename and three exported symbols. Trace how each value is produced. Predict the diagnostic category for a missing package, a missing code asset and a missing symbol. These failures occur at different boundaries.

## Keep target names stable

Architecture and Apple SDK selection belong to the build output configuration. Do not append arbitrary arm64 or simulator suffixes to this shared asset identity. The compiled bytes may differ per target while the consumer contract stays stable. Real packaging and loading still require target-specific qualification.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](06-read-a-native-package-graph.md) · [Next lesson](08-match-c-and-dart-abi-types.md)
