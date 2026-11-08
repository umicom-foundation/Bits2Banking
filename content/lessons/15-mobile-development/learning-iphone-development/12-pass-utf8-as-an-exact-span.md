<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/12-pass-utf8-as-an-exact-span.md

PURPOSE:
Teach pass swift text as an exact utf-8 span through the existing Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Pass Swift text as an exact UTF-8 span

## Prepare the lab

Use a Mac with Xcode, an iOS Simulator runtime and a C23-capable toolchain. Create an iOS App named ProfilePolicyLab and run its unchanged template. Add NativeProfile.swift, profile_bridge.c and Framework src/security/profile_name.c to the application target; set Profile-Bridging-Header.h and the Framework include path. Add NativeProfileTests.swift only to an XCTest Unit Testing Bundle named ProfilePolicyLabTests. Keep the existing screens unchanged. The linked lab README gives the exact target settings and recovery steps.

[Complete Xcode lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-profile/README.md)

## Choose the representation deliberately

A Swift String is Unicode text. Its character count is not the byte count expected by a C span API. NativeProfile reads input.utf8 and collects at most the Framework capacity, which is one byte beyond the largest accepted name. The scratch array is bounded even when the caller supplies a long string. The original input remains owned by the caller.

## Use the extra byte to refuse long input

The accepted maximum is 48 bytes; the scratch input can contain 49. Passing 49 makes the shared policy refuse the candidate. Copying only 48 would be wrong: a longer name beginning with a valid prefix could be accepted as a different value. Explain this difference before running testLongInputIsNotTruncatedIntoAValidName.

## Keep embedded NUL visible

The string abc, a NUL and tail is a full value. Passing its pointer through a C string API might stop at the NUL. This lab passes the exact array count, so Framework sees the zero byte and rejects the whole candidate. The output is read only after success. The test checks that a shortened valid prefix never escapes.

## Distinguish Unicode refusal from broken text

Accented letters, combining sequences and emoji are valid Swift text. They are outside this ASCII identifier policy. Run the Unicode case and expect nil without changing the display text or inventing ASCII substitutions. A future internationalised display-name feature needs its own shared contract; it should not silently change this identifier API.

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

[Course contents](index.md) · [Previous lesson](11-share-the-profile-policy-with-swift.md) · [Next lesson](13-borrow-pointers-within-one-call.md)
