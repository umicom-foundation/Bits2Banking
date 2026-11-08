# Learning iPhone Development

Create a small iPhone screen and connect it to an existing C application model. Learn each boundary before adding storage or networking.

## Start here

A Mac with Xcode and an iOS Simulator runtime is required for the practical exercises. Reading is available on any platform.

## Lesson sequence

1. [Create and run your first iPhone screen](01-create-and-run-a-screen.md)
1. [Call an existing C model from Swift](02-call-the-shared-c-model.md)
1. [Keep screen state and feedback understandable](03-state-feedback-and-accessibility.md)
1. [Distinguish simulator, device and release evidence](04-simulator-device-and-evidence.md)

## Continue learning

[Learning C](../../learning-c/index.md) introduces functions, values and checks. [Learning Umicom Framework](../../umicom-development/index.md) connects those ideas to shared application services. Each example is a bounded teaching project; the source does not establish device or production qualification.


- [Connect a C declaration to its implementation](05-declaration-and-definition.md)

- [Use CInt and check the returned value](06-cint-and-result-checks.md)

- [Understand a SwiftUI view's state](07-view-identity-and-state.md)

- [Distinguish simulator and device builds](08-simulator-and-device-builds.md)

- [Check accessible actions and feedback](09-accessible-actions-and-messages.md)

- [Check the complete Swift-to-C workflow](10-check-the-whole-native-path.md)

## Share C text policy with Swift

Use a separate Xcode lab to examine exact byte spans, pointer borrowing, native linkage and independent target evidence.

1. [Share the Framework name policy with Swift](11-share-the-profile-policy-with-swift.md)
2. [Pass Swift text as an exact UTF-8 span](12-pass-utf8-as-an-exact-span.md)
3. [Borrow Swift buffers only for one C call](13-borrow-pointers-within-one-call.md)
4. [Connect declarations and implementations in Xcode](14-connect-xcode-target-membership.md)
5. [Exercise the actual Swift-to-C test target](15-exercise-the-swift-c-test-target.md)
6. [Diagnose the first failing Swift-to-C boundary](16-diagnose-swift-c-linkage.md)
7. [Keep simulator and device evidence separate](17-keep-simulator-and-device-evidence-separate.md)
8. [Compare one C policy across mobile and desktop clients](18-compare-one-policy-across-clients.md)
