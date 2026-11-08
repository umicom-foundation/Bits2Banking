<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/16-diagnose-swift-c-linkage.md

PURPOSE:
Teach diagnose the first failing swift-to-c boundary through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Diagnose the first failing Swift-to-C boundary

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Separate four stages

The Swift compiler needs a declaration; the C compiler needs the correct headers and language mode; the linker needs one matching definition; the test runner needs the correct target and destination. Write these stages in order. The earliest failing stage usually explains why later behavior has not occurred.

## Use the symbol in the diagnostic

If Swift cannot find BtbProfileCanonical, inspect the bridging header. If the linker cannot find UmiLocalProfileNameBytes, inspect the Framework source membership or selected target library. A duplicate symbol suggests two owners. Preserve the exact symbol and the active build configuration instead of treating every message as a generic C integration problem.

## Keep target identity with the error

Record the SDK, architecture and source locations from the build. An Arm64 simulator object and an Arm64 device object still target different platforms. Do not copy an object from another output directory to silence a missing-file error. Rebuild the selected source with the correct target configuration.

## Make one change and recheck

Restore one missing declaration, definition or path at a time in a disposable project. Rebuild after each correction and note whether the failure moved to a later stage. Finally run the intended XCTest class. Reaching the linker or launching the test host is progress, but only the actual method results establish the exercised integration behavior.

## Build and observe

Run from the directory containing ProfilePolicyLab.xcodeproj. Inspect the first two commands, replace SIMULATOR_UDID with an available simulator identifier, and choose a new result bundle path before testing. Run each command separately and stop on errors. Expect ten NativeProfileTests methods; inspect actual outcomes in the xcresult bundle. These are instructions for your selected target, not recorded passes.

~~~sh
xcodebuild -list -project ProfilePolicyLab.xcodeproj
xcodebuild -showdestinations -project ProfilePolicyLab.xcodeproj -scheme ProfilePolicyLab
mkdir -p TestResults
xcodebuild -project ProfilePolicyLab.xcodeproj -scheme ProfilePolicyLab -destination 'platform=iOS Simulator,id=SIMULATOR_UDID' -only-testing:ProfilePolicyLabTests/NativeProfileTests -resultBundlePath TestResults/profile-simulator.xcresult test
~~~

Use Xcode/xcodebuild for this generated Apple project. Native Umicom CLI CMake/CTest commands do not replace its target, signing and test workflow.

## Read the implementation

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/profile_bridge.h) · [Swift temporary-pointer guidance](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/)

[Course contents](index.md) · [Previous lesson](15-exercise-the-swift-c-test-target.md) · [Next lesson](17-keep-simulator-and-device-evidence-separate.md)
