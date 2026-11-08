<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/11-share-the-profile-policy-with-swift.md

PURPOSE:
Teach share the framework name policy with swift through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Share the Framework name policy with Swift

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Keep the policy in one place

The earlier iPhone lab sends an integer through a C bridge. This module sends a text value. Framework already defines profile-name validation in UmiLocalProfileNameBytes; the iPhone lab forwards to that function instead of adding a Swift regular expression. The same name should therefore receive the same policy decision in the Android, Qt, Wt and Swift consumers when they use the same Framework source.

## Read the application bridge

BtbProfileCanonical accepts an unsigned-byte pointer, its length and caller-owned output. It maps Framework success to 1 and refusal to 0. That small result makes the Swift boundary explicit without moving the naming algorithm into the application. Find the Framework call and verify that no character loop, lowercase rule or account lookup has appeared in the bridge.

## Predict and observe

Predict the results for Sam_007, 1Sam and Sam Smith, then run the XCTest class. Expect sam_007 for the first value and nil for the others. Read NativeProfile.swift to locate the point where a successful C result becomes an owned Swift String. A canonical name is only a validated identifier; it does not create, authenticate or save an account.

## Recover from a difference

If an iPhone result differs from the desktop lab, first compare the linked Framework source and build target. An imported header can be current while an old library still supplies the definition. Preserve that distinction in the failure record. Update the shared policy and its regression coverage only when the requirement itself changes.

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

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/profile_bridge.c) · [Swift temporary-pointer guidance](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/)

[Course contents](index.md) · [Previous lesson](10-check-the-whole-native-path.md) · [Next lesson](12-pass-utf8-as-an-exact-span.md)
