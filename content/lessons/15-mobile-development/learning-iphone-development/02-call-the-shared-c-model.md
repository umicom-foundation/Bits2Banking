<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/02-call-the-shared-c-model.md

PURPOSE:
Explain the lesson: Call an existing C model from Swift.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Call an existing C model from Swift

## Setup recap
Create and run a SwiftUI iOS App in Xcode on a Mac. Have the Bits2Banking and Umicom Framework source checkouts available locally. The detailed source-integration steps are in `labs/mobile/iphone-framework-activity/README.md`.

## What crosses the boundary
Our C function accepts one integer and returns one integer:
~~~c
int BtbActivityNext(int current);
~~~
A nonnegative return is the updated count. A return of -1 means the update was rejected. No pointer to a Swift object crosses this boundary.

A bridging header makes C declarations visible to Swift in this target. Apple describes the [bridging-header mechanism](https://developer.apple.com/documentation/swift/importing-objective-c-into-swift).

## Add the sources
1. Add the supplied ActivityView.swift to the app target.
2. Add the existing bridge.c and activity.c from their repository locations. Keep their relative includes intact.
3. Set Objective-C Bridging Header to Activity-Bridging-Header.h.
4. Add Framework's include directory to Header Search Paths.
5. Select the C23 language mode supported by your Xcode compiler.
6. Change the generated WindowGroup's view to ActivityView().
7. Build for the same simulator used by the unchanged template.

The two C files use Framework's status declaration. This first exercise does not link a prebuilt desktop SDK archive. A later library integration must use binaries built for the actual iOS target.

## Follow a value
~~~text
Swift CInt 0 -> BtbActivityNext -> BtbActivityAdvance -> UMI_STATUS_OK
                                                      |
display 1 <------------ return 1 <---------------------+
~~~
CInt represents the imported C integer type. The C bridge checks signed input before calling the existing rule. Swift does not repeat that rule.

## Diagnose the layer
If Swift cannot see the name, inspect the bridging header. If the linker cannot find the implementation, inspect target membership for the C files. These errors occur at different stages and need different corrections.

## Exercise
Set a breakpoint at BtbActivityNext. Press Complete exercise and observe current. Step into BtbActivityAdvance and locate the return status. Continue to Swift and identify the assignment that updates the screen. Do not infer a native call from a screen change alone.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/Activity-Bridging-Header.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](01-create-and-run-a-screen.md) · [Next lesson](03-state-feedback-and-accessibility.md)

