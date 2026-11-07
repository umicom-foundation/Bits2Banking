<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/05-declaration-and-definition.md

PURPOSE:
Explain the lesson: Connect a C declaration to its implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect a C declaration to its implementation

## Prepare on a Mac
Install Xcode and an iOS Simulator runtime. Create an iOS App using SwiftUI and run the unchanged template. Make the Bits2Banking and Framework source checkouts available. Follow the iPhone activity lab README to add its Swift view and the two existing C sources.

A **declaration** describes a function's name and parameter/result types. A **definition** contains the instructions that implement it. Swift needs the declaration while compiling; the final application also needs the definition while linking.

## Follow the header
1. Open `Activity-Bridging-Header.h`.
2. Follow its include to the shared `bridge.h`.
3. Find `int BtbActivityNext(int current);`.
4. Open `bridge.c` to see the implementation.
5. Confirm that both `bridge.c` and `activity.c` belong to the application target.

The bridging-header build setting tells Swift which C declarations to import. Adding only a header does not compile the C implementation.

## Diagnose by stage
If Swift says the function is unavailable, inspect the bridging-header setting and header search paths. If compilation succeeds but linking cannot find the symbol, inspect C source target membership. Do not “fix” either failure by adding another copy of the count algorithm to Swift.

**Exercise:** draw two arrows from `bridge.h`: one to the Swift compiler and one to the C compiler. Then draw `bridge.c` into the linker. Label which arrow explains each failure above.

## Check the result
Build for the selected simulator, launch, and press Complete exercise. Expected result: 0 becomes 1. Record the actual result and source revision. The exercise establishes this specific source integration; it does not imply that a desktop Framework binary can run on iOS.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/Activity-Bridging-Header.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-simulator-device-and-evidence.md) · [Next lesson](06-cint-and-result-checks.md)

