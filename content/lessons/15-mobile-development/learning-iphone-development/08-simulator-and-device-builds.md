<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/08-simulator-and-device-builds.md

PURPOSE:
Explain the lesson: Distinguish simulator and device builds.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish simulator and device builds

## Set up
On a Mac, install Xcode and the required simulator runtime. Create an iOS SwiftUI application and run the unchanged template. Then integrate the existing activity example using the documented source paths and Framework headers.

A **build destination** tells Xcode which platform environment will run the result. The iPhone simulator and a physical iPhone are distinct destinations. A shared processor-family name alone does not make their binaries interchangeable.

## Check one destination at a time
1. Select an iPhone simulator.
2. Build and run the activity lab.
3. Record the destination, configuration and observed button result.
4. Select a physical device only when it is connected and ready for development.
5. Follow Xcode's signing and device-trust setup.
6. Build for that destination and repeat the same workflow check.

Do not copy a simulator executable onto a phone and call that a device installation procedure.

## Understand the source boundary
The same `bridge.c` and `activity.c` can be compiled for each destination. Headers describe interfaces. Object files and libraries contain code built for a particular target. Keeping the source shared avoids duplicating the application rule while allowing appropriate platform builds.

## Exercise
Create a two-row evidence table: simulator and device. Include build status, launch status and observed count. Leave a row “not run” if that destination is unavailable. Expected result: the table makes unsupported claims difficult to hide.

## Troubleshooting
An unavailable simulator runtime, missing signing setup and an undefined C symbol have different causes. Read the first diagnostic, identify its stage, and repair that stage. Changing the count function is not a remedy for a device provisioning error.

This lab is a source integration exercise. Store distribution, signing policy and complete Framework platform qualification require their own work.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-view-identity-and-state.md) · [Next lesson](09-accessible-actions-and-messages.md)

