# iPhone strings with the shared Framework C policy

This laboratory adds a Swift-to-C text boundary and XCTest coverage to a separate Xcode project. It leaves the existing activity-counter screen unchanged. The same Framework profile-name implementation is used by Android, Qt and Wt; there is no Swift regular-expression copy of the naming rule.

## Prepare on a Mac

1. Install Xcode with an iOS Simulator runtime and a C23-capable Apple toolchain. Record the actual Xcode, SDK and compiler versions. Windows host archives cannot be linked into an iOS target.
2. Create a new iOS App project named ProfilePolicyLab using Swift and SwiftUI. Use an explicit directory such as ~/umicom/projects/ProfilePolicyLab. Run the generated template on a selected simulator before adding this lab. Keep the generated Activity/App entry and screen.
3. Make the primary Framework and Bits2Banking source checkouts available on the Mac. Add NativeProfile.swift, profile_bridge.c and Framework's src/security/profile_name.c to the application target by reference. Keep one definition of each function; do not also link another profile-name archive.
4. Set the application's Objective-C Bridging Header build setting to the absolute path of Profile-Bridging-Header.h. Add the Framework include directory to Header Search Paths, retaining inherited entries. The bridge includes profile_bridge.h from its own directory, so keep both headers together.
5. Select ISO C23 for the C sources when the toolchain offers it. If the selected compiler rejects the mode, inspect or update the toolchain; do not describe a failed or different language-mode build as C23 qualification.
6. Add an iOS Unit Testing Bundle target named ProfilePolicyLabTests using XCTest, or use the generated XCTest target if present. Add NativeProfileTests.swift to that test target only. It imports the application module using @testable import ProfilePolicyLab. Keep Enable Testability enabled for the Debug application configuration. Do not add the C implementations to both targets.
7. In the scheme's Test action, select ProfilePolicyLabTests. Choose the intended simulator destination and run the ten NativeProfileTests methods. A template launch alone is not a native interop test result.

The [bridging-header guide](https://developer.apple.com/documentation/swift/importing-objective-c-into-swift) describes how C-family declarations become visible in the Swift target. The laboratory uses plain C; it does not require writing Objective-C or C++ implementations.

## Inspect and run from Terminal

From the directory containing ProfilePolicyLab.xcodeproj, inspect available schemes and destinations first:

~~~sh
xcodebuild -list -project ProfilePolicyLab.xcodeproj
xcodebuild -showdestinations -project ProfilePolicyLab.xcodeproj -scheme ProfilePolicyLab
~~~

Choose an available simulator identifier from that output. Replace SIMULATOR_UDID below before executing. Use a new result bundle path for each run; preserve an earlier result rather than overwriting it.

~~~sh
mkdir -p TestResults
xcodebuild -project ProfilePolicyLab.xcodeproj -scheme ProfilePolicyLab -destination 'platform=iOS Simulator,id=SIMULATOR_UDID' -only-testing:ProfilePolicyLabTests/NativeProfileTests -resultBundlePath TestResults/profile-simulator.xcresult test
~~~

Stop on an error. Open the resulting xcresult bundle in Xcode and inspect the individual method results. The expected class has ten tests, including long input, embedded NUL, Unicode refusal and independent results. These commands are instructions; no test pass is implied.

A physical-device run needs its own destination, supported SDK, development team and signing configuration. Select the device in Xcode and review its trust/signing instructions before running. Keep simulator and device evidence separate, even when both CPUs are Arm64. This lab does not archive, upload or sign a production distribution.

## Follow storage ownership

NativeProfile.canonical creates at most 49 UTF-8 bytes of scratch input: one more than the permitted 48-byte name. That extra byte ensures overlong input is refused instead of silently shortened. It allocates a separate output buffer with the capacity declared by Framework. Nested withUnsafeBufferPointer and withUnsafeMutableBufferPointer calls keep both addresses valid only around the synchronous C call.

BtbProfileCanonical forwards the exact span to UmiLocalProfileNameBytes and maps its success status to 1. On refusal it returns 0 and preserves output. Swift reads the result only after success and copies the canonical ASCII bytes into a new String. No pointer escapes a closure or reaches a later task. See Swift's [temporary-pointer diagnostics](https://docs.swift.org/latest/documentation/diagnostics/temporary-pointers/) for why a saved pointer would be invalid.

An embedded NUL remains in the span and is rejected. Accented, combining and emoji input is rejected by the existing ASCII naming policy. This does not mean those strings are invalid Swift text. Name validation is separate from user authentication, storage and internationalised display names.

## Diagnose the boundary

- Swift cannot find BtbProfileCanonical: inspect the active application's bridging-header setting and header search path.
- The linker cannot find UmiLocalProfileNameBytes: check that Framework profile_name.c belongs to the application target, or use one correctly built target library instead; do not add two implementations.
- The test cannot import ProfilePolicyLab: compare the application module name, test host and Debug testability setting.
- Tests are absent: inspect the scheme Test action and the class filter. A successful build without the intended tests is incomplete evidence.
- A valid result differs between platforms: compare the shared Framework source identity and selected binaries before changing an adapter.

The existing Framework tests/profile_name project checks the C policy on its declared target. This XCTest suite adds the Swift compiler, imported declaration, pointer borrowing and application linkage. It does not qualify a mobile UI, process restoration, persistence or a complete iOS Framework SDK.
