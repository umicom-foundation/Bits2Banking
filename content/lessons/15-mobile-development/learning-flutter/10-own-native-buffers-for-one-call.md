<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/10-own-native-buffers-for-one-call.md

PURPOSE:
Own native buffers for one synchronous call

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Own native buffers for one synchronous call

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

## Identify the allocations

normalizeProfileName allocates an input byte buffer and an output buffer through an arena. The caller copies bytes into the input, the C adapter writes a bounded result, and Dart copies the resulting text into a managed String. No native pointer is exposed by ProfileNameResult.

## Follow the release boundary

The using scope releases arena allocations when its callback returns or throws. Decoding happens inside that scope. Returning a typed view into the native output instead would leave a view whose backing memory had already been freed. A structure or list reference is not automatically an owned copy of the bytes it points to.

## Exercise

Trace the accepted-name and refused-name branches separately. Mark where each allocation is made, which branch reads output and when release occurs. Read the retained-result test: it keeps the first Dart result while later calls allocate and free their own buffers. Explain why the first string must remain unchanged.

## Respect synchronous ownership

The C function retains no pointer and finishes before the Dart scope closes. An asynchronous native API would need a different ownership protocol, completion notification and disposal rule. Do not reuse this one-call arena pattern by handing its pointers to a background worker that may outlive the call.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](09-count-encoded-bytes-explicitly.md) · [Next lesson](11-review-output-capacity-and-failure-atomicity.md)
