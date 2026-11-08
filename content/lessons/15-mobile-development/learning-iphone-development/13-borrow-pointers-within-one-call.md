<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/13-borrow-pointers-within-one-call.md

PURPOSE:
Teach borrow swift buffers only for one c call through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Borrow Swift buffers only for one C call

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Find the two owners

The bytes array owns the input storage. The output array owns the writable result storage. Each scoped buffer method supplies a temporary pointer into its respective array. The inner closure calls C while both borrows are alive. Once the closures return, Swift owns values again; the application has saved no raw address.

## Read the C lifetime promise

The bridge header says the call is synchronous and retains neither pointer. That promise is part of the API, not a property that Swift can infer from the function name. A service that queued work would need a different ownership contract and an owned copy. Do not move this pointer into a task, callback or stored property merely because the original code compiled.

## Avoid overlapping access in Swift

Inside the mutable output-buffer closure, use outputBuffer rather than reaching back into the output array. Capacity is computed before the borrow. After the call, the guard checks the result, and only then does Swift inspect the owned output value. Trace this order and identify where simultaneous mutable access would become ambiguous.

## Review an unsafe alternative

Sketch a function that returns inputBuffer.baseAddress from the closure, but do not execute the dangling pointer. Explain why the address outlives its valid borrow. Compare that sketch with the production adapter, which returns an integer decision from the nested closures and later constructs a fresh String. Tests can catch examples of misuse; the lifetime contract still requires source review.

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

[Lesson source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/NativeProfile.swift) · [Swift temporary-pointer guidance](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/)

[Course contents](index.md) · [Previous lesson](12-pass-utf8-as-an-exact-span.md) · [Next lesson](14-connect-xcode-target-membership.md)
