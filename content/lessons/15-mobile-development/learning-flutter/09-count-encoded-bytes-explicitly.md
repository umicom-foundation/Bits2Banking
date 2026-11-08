<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/09-count-encoded-bytes-explicitly.md

PURPOSE:
Count encoded bytes rather than displayed characters

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count encoded bytes rather than displayed characters

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

## Distinguish text representations

Dart String length counts UTF-16 code units. The native service accepts a byte span. The wrapper encodes input to UTF-8, copies the resulting bytes and passes that byte count. A non-ASCII character can occupy several bytes even when a user sees one character on screen.

## Preserve refused input

This policy accepts ASCII profile names, so accented characters and supplementary characters are refused. The wrapper does not strip accents, trim spaces or stop at an embedded zero. The explicit length lets C inspect the entire selected span. An unpaired surrogate becomes invalid non-ASCII encoded input rather than an accepted shortened name.

## Exercise

Compare Course_User, Useré and a string containing an embedded zero in the supplied tests. Record Dart code-unit length, UTF-8 byte length and expected policy status. Explain why using a zero-terminated conversion followed by strlen could hide bytes after the embedded zero. Run the actual binding cases before recording observed results.

## Keep allocation bounded

The wrapper rejects a Dart input whose code-unit length cannot fit the ABI capacity. Accepted ASCII names use one code unit per byte, so this early allocation bound cannot discard a valid longer spelling. Character rules still belong to C. Do not generalize this shortcut to an unrelated Unicode naming policy.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](08-match-c-and-dart-abi-types.md) · [Next lesson](10-own-native-buffers-for-one-call.md)
