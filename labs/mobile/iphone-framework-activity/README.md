# iPhone screen with a shared C activity

This example uses SwiftUI to display the existing C activity model. Swift is the native screen adapter; the count rule remains in `labs/native/framework-activity/activity.c`.

## Set up on a Mac

1. Install a supported Xcode release and its iOS Simulator runtime. Open Xcode once to finish installation.
2. Create an iOS App project named ActivityLab. Choose Swift and SwiftUI. Select an iPhone simulator and run the unchanged template.
3. Make both the Bits2Banking and Framework source checkouts available on the Mac. A Windows SDK archive cannot be linked into an iPhone target.
4. Add `ActivityView.swift`, `../../native/activity-adapters/bridge.c`, and `../../native/framework-activity/activity.c` to the application target, keeping their original relative source locations. Ensure both C files have app target membership. Do not add a second copy of their functions.
5. Set the target's **Objective-C Bridging Header** build setting to the absolute path of `Activity-Bridging-Header.h`. This header exposes a C declaration. Add the Framework `include` directory to Header Search Paths.
6. Use C23 (or the compiler's corresponding draft C2x option) for the C files. This lab uses only the Framework status header; no desktop Framework library is required.
7. In the generated App type, replace the default view expression inside `WindowGroup` with `ActivityView()`. Keep the generated app entry point.
8. Build and run on the simulator. Press Complete exercise and expect the count to increase by one.

Apple documents the [bridging-header mechanism](https://developer.apple.com/documentation/swift/importing-objective-c-into-swift). The example header includes the C adapter directly.

## Follow the call

`Button` calls `BtbActivityNext`. A nonnegative result updates `@State`; -1 leaves the count unchanged and displays a message. `CInt` keeps the view's value aligned with the C `int` boundary. The bridge validates it before converting to unsigned.

## Check and troubleshoot

- Build for an iPhone simulator before attempting a device.
- If Swift cannot find the function, check the bridging-header setting for the active configuration.
- If the linker cannot find it, check the C source target membership.
- For a real device, select that device, configure your development team/signing, and follow Xcode's device trust instructions.
- Device and simulator binaries are distinct targets even when both use Arm64. Build each with its own SDK.
- Press the button three times; rotate the device; check the accessibility label. Relaunching resets this in-memory activity; durable saving is a later exercise.

This is a source integration lab, not a distributable signed app or a claim that the entire Framework SDK has been ported to iOS.

