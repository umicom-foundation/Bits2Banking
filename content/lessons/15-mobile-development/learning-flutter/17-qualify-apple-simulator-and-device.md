<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/17-qualify-apple-simulator-and-device.md

PURPOSE:
Keep Apple simulator and device evidence separate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep Apple simulator and device evidence separate

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

## Use an Apple development environment

Run Apple-target qualification in a suitable macOS/Xcode setup. A Windows host result does not qualify an iPhone library. Simulator and physical-device builds use different SDK contexts even when both involve an arm64 architecture. Keep the SDK and destination in the evidence record.

## Preserve a stable native identity

The package uses one asset ID and library basename across Apple SDK variants. Architecture-specific bytes belong in separate build outputs, not ad hoc public names. A stable identity lets the application bind the same declared functions while the build system selects the correct target artifact.

## Exercise

Run the copied integration test on an available simulator and record the destination, SDK, source revision and observed result. If physical-device qualification is available, record it as a separate run. Leave it unexecuted when it is not available rather than relabeling the simulator result.

## Bound the conclusion

The test checks three native service behaviors. It does not establish distribution signing, provisioning, App Store acceptance or a responsive profile screen. A native loading failure needs the packaged asset and symbol evidence. A signing failure belongs to the application’s target configuration and cannot be repaired by changing the profile-name rule.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](16-qualify-an-android-native-asset.md) · [Next lesson](18-separate-native-and-browser-clients.md)
