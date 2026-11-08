<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/18-separate-native-and-browser-clients.md

PURPOSE:
Separate native and browser integration paths

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate native and browser integration paths

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

## Recognize the unsupported boundary

This package imports dart:ffi and supplies native machine-code assets. It does not implement a browser binding. The earlier Flutter counter can run on a browser because it has no such native dependency, but adding this package changes the target requirements. A shared UI framework does not remove every platform boundary.

## Reuse rules through an appropriate adapter

A browser client needs a separately designed web interface, such as the existing Framework web path, with its own transport and memory ownership. That adapter should still reuse canonical rules where technically supported. It must not pretend that a desktop dynamic library can be loaded by a browser as though it were a native process.

## Exercise

Create a target table for the original counter, the standalone Dart profile lab and the Flutter native integration harness. Mark what is authored, what you have executed and what remains unsupported. Explain why a browser counter test cannot establish C ABI correctness or mobile native packaging.

## Communicate limits clearly

Keep unsupported browser execution visible in documentation and product capability checks. Do not silently replace the native service with a permissive Dart validator just to make a demo run. A fallback is a new behavior contract requiring its own design, tests and explanation.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](17-qualify-apple-simulator-and-device.md) · [Next lesson](19-diagnose-the-first-failed-boundary.md)
