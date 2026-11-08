<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/14-build-and-observe-on-ios.md

PURPOSE:
Build and observe the lab on iOS

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build and observe the lab on iOS

## Before starting

This practical step requires a Mac with Xcode and a compatible Qt iOS kit. Windows can be used to study and edit the source, but it cannot perform this Xcode workflow. Copy or check out the same reviewed Bits2Banking and Framework revisions on the Mac. Simulator and physical-device qualification are separate records.

## Generate the target project

Run these shell commands from the profile lab on the Mac. Replace the example directories with your actual checkout and kit. The C source is compiled for the selected iOS target; no Windows or Android archive is imported.

~~~bash
/path/to/Qt/your-version/ios/bin/qt-cmake -S . -B build-ios -G Xcode -DCMAKE_BUILD_TYPE=Debug -DBTB_FRAMEWORK_SOURCE=/path/to/umicom-framework -DBUILD_TESTING=OFF
cmake --build build-ios --config Debug
~~~

## Understand the bundle

The lab marks the Apple application as a bundle with an educational identifier. A bundle groups the program and platform metadata. That identifier is not an entitlement, a signing identity or proof of store approval. Physical-device deployment needs the appropriate certificates and provisioning configured in the owner’s Xcode environment. Keep secrets and signing material out of lesson source.

## Choose a destination

Open the generated Xcode project, select a destination supported by the installed Qt kit, and resolve its signing requirements for your own test account. Run the existing form. Enter an accepted name, then an invalid one. Check keyboard visibility and reachability of the button and result. Record simulator or device explicitly; do not combine those outcomes into one generic mobile pass.

## Exercise and worked answer

A simulator run works, but the device build reports a provisioning error. Should the C validator change? No. The failed boundary is device deployment authorization. Correct the project’s signing setup through the established Xcode process and rerun that stage. Retain the simulator observation and the device failure as separate evidence.

## Recovery and limits

When a library architecture is rejected, inspect the selected destination and the Qt kit’s supported architectures before rebuilding. Preserve the failed build directory and use a new one if changing the target setup. This laboratory does not establish background persistence, store distribution or production account security. Continue with the lifecycle lesson to examine what the simple form actually retains.

## Reference

[Qt iOS toolchain, build and deployment reference](https://doc.qt.io/qt-6.8/ios.html). Consult the documentation for the exact kit you install.

## Read the source

[labs/framework/qt-profile/CMakeLists.txt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/CMakeLists.txt). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Package the same Qt lab for Android](13-package-the-android-lab.md) · [Next: Observe mobile input and application lifetime](15-observe-mobile-lifecycle-and-input.md)
