<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/15-exercise-the-swift-c-test-target.md

PURPOSE:
Teach exercise the actual swift-to-c test target through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Exercise the actual Swift-to-C test target

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Select XCTest deliberately

The supplied class uses XCTestCase and ten test-prefixed methods. Add an iOS Unit Testing Bundle using XCTest and ensure the scheme Test action includes it. If a generated project uses a different test framework, create the matching target rather than assuming the source will be discovered automatically. Keep the test host set to the application.

## Read what the class covers

The suite crosses the actual compiled Swift adapter and C bridge into Framework. It covers minimum and maximum names, overlong input, invalid ASCII, Unicode, embedded NUL, valid separators and independent returned values. It does not click a screen or check process restoration. The existing pure-C suite and this integration suite supply different evidence.

## Run one identified class

Use xcodebuild -showdestinations to select an available simulator, then the class-filtered test command in the README. Save a new xcresult bundle. Inspect each of the ten method results and the selected destination. A successful application build or an empty test action cannot establish that this class ran.

## Recover from an absent test

Check test source membership, the XCTest target, module import, Debug testability and scheme selection in that order. Preserve compilation and execution errors separately. Do not delete the class filter merely to obtain a passing result from unrelated template tests. When the class runs, compare its actual methods with the intended coverage before accepting the record.

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

[Course contents](index.md) · [Previous lesson](14-connect-xcode-target-membership.md) · [Next lesson](16-diagnose-swift-c-linkage.md)
