<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/14-connect-xcode-target-membership.md

PURPOSE:
Teach connect declarations and implementations in xcode through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect declarations and implementations in Xcode

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## A header is a declaration route

The application bridging header includes profile_bridge.h, which declares the C function and imports the Framework capacity constant. This lets Swift type-check its call. It does not compile profile_bridge.c or profile_name.c. Locate the application build setting, then separately locate both C files under the application target Compile Sources list.

## Give each definition one owner

Add NativeProfile.swift, the application C bridge and Framework profile_name.c to the application target. Add NativeProfileTests.swift to the unit-test target. The test imports the application module rather than compiling a second copy of its C functions. Linking both the source and another archive containing the same definition can produce duplicate-symbol failures.

## Check the active configuration

A correct Debug bridging-header path does not prove the Release configuration has the same setting. Preserve inherited header-search paths and inspect the selected configuration. Use absolute source locations for the lab or deliberate project-relative references that resolve on the Mac. A Windows checkout path cannot be used as a Mac filesystem path.

## Exercise a diagnosis safely

In a disposable project copy, remove only the bridge C file from application target membership. Keep the declaration. Build and retain the unresolved-symbol error, then restore membership. The exercise separates successful Swift type-checking from successful linking. Do not fix it by pasting a second implementation into the Swift test target.

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

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/Profile-Bridging-Header.h) · [Swift temporary-pointer guidance](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/)

[Course contents](index.md) · [Previous lesson](13-borrow-pointers-within-one-call.md) · [Next lesson](15-exercise-the-swift-c-test-target.md)
