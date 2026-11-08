<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/06-read-a-native-package-graph.md

PURPOSE:
Read a native package and its dependency graph

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a native package and its dependency graph

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

## Identify the local dependency

The exercise pubspec points to the primary Framework package using a relative path. The Framework package stays inside a complete checkout because its hook refers to canonical C source elsewhere in that tree. Moving only the Dart directory loses those inputs. A path dependency is a source location, not an installed mobile SDK.

## Separate resolution from execution

dart pub get resolves Dart packages and writes dependency state. A later native run or test invokes the build hook and compiler. The hook helper packages are normal dependencies because applications consuming this package must resolve them too. The test package belongs to development dependencies. Read the resolved lockfile before treating two runs as the same environment.

## Exercise

Open both pubspec files and mark the local package edge, runtime allocation helper, hook helpers and test dependency. Calculate the local path from the lab directory instead of assuming the current terminal folder controls it. Record the resolved Framework revision and dependency versions with your first successful run.

## Recover from resolution failure

For a missing path, fix the selected checkout location while preserving the package’s source-tree position. For a version conflict, retain the exact solver diagnostic and Dart SDK version. Do not copy the policy into the lab or claim a dependency download proves that a native function was executed.

## Review and recover

Record the exact failing boundary, source revision, SDK/compiler versions and output. Fix package resolution before diagnosing native execution. Host, emulator, physical-device and browser evidence remain distinct; this native package does not support browser FFI.

[Exercise setup and device commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-framework-profile/README.md) · [Framework binding contract](https://github.com/umicom-foundation/umicom-framework/blob/main/bindings/dart/umicom_profile_name/README.md)

[Course contents](index.md) · [Previous lesson](05-trace-dart-to-the-c-policy.md) · [Next lesson](07-follow-native-asset-identities.md)
