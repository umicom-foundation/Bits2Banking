<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/18-compare-one-policy-across-clients.md

PURPOSE:
Teach compare one c policy across mobile and desktop clients through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare one C policy across mobile and desktop clients

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Build a common value table

List Sam_007, ABC, 48 letters, 49 letters, a leading digit, embedded NUL and a non-ASCII name. Predict canonical output or refusal from the Framework contract. Map each row to the Android instrumented test and the Swift XCTest method; include the Qt or Wt event case when one exists.

## Compare meaning rather than UI labels

Android returns null for ordinary refusal; Swift returns nil; the C API returns a status while preserving output. These are different representations of the same decision. Compare accepted canonical bytes and refused whole values. Do not require the adapters to expose identical language syntax or error widgets.

## Record source and binary uncertainty

Keep the Framework revision and source digest with each client result. If a compiled library cannot be tied to that source, record the uncertainty instead of blaming the shared rule. A header match alone cannot identify a library definition. Rebuild and rerun only through the appropriate owner workflow.

## Choose the next product workflow

The lab deliberately stops at validation. An approved application screen could use the result for local feedback, while account storage and authentication remain separate services. Define that user journey and its acceptance steps before editing the layout. Retain these boundary checks so later presentation work does not silently change the shared rule.

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

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/NativeProfileTests.swift) · [Swift temporary-pointer guidance](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/)

[Course contents](index.md) · [Previous lesson](17-keep-simulator-and-device-evidence-separate.md)
