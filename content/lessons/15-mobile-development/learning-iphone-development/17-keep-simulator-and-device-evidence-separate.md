<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/17-keep-simulator-and-device-evidence-separate.md

PURPOSE:
Teach keep simulator and device evidence separate through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep simulator and device evidence separate

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Inspect the destination instead of guessing

Use Xcode or xcodebuild -showdestinations to identify a specific available simulator. Keep its identifier, runtime and architecture in the test record. The word simulator does not imply one CPU architecture. A real iPhone uses a device SDK, signing and trust path that the simulator does not establish.

## Preserve each result bundle

Use a distinct xcresult path for each target and run. Inspect the class and method outcomes before comparing records. If one target was unavailable, record that absence explicitly. Reusing a previous bundle or quoting a desktop C test count would hide the missing target coverage.

## Move to a device deliberately

Choose a supported connected device, configure the development team and follow Xcode trust instructions. Run the same class against that destination, keeping the result separate from simulator evidence. A signing failure is not a name-policy regression; retain it as a deployment/setup failure until the test can actually run.

## Bound the release claim

Debug integration tests do not establish a production archive, store submission, upgrade behavior or a complete mobile interface. Run a separate release workflow before distributing an application. The useful result here is narrower: identified Swift and C sources exercised through a particular compiled target and test class.

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

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md) · [Swift temporary-pointer guidance](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/)

[Course contents](index.md) · [Previous lesson](16-diagnose-swift-c-linkage.md) · [Next lesson](18-compare-one-policy-across-clients.md)
