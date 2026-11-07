<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/04-simulator-device-and-evidence.md

PURPOSE:
Explain the lesson: Distinguish simulator, device and release evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish simulator, device and release evidence

## Setup recap
Use Xcode on a Mac and the ActivityLab project. Complete the simulator path before attempting a physical phone. Device testing requires the appropriate signing configuration and a trusted connected device.

## Why the target matters
An architecture describes the processor instruction family. A platform also defines operating-system services, binary format details and libraries. Two targets can both use Arm64 and still require different builds.

~~~text
C source -> iOS Simulator build -> simulator
C source -> iOS device build    -> iPhone
~~~
Selecting the destination is part of the build configuration. Do not rename or copy a desktop archive and assume it becomes a phone library.

## Device exercise
1. Connect a supported device and follow Xcode's trust/setup instructions.
2. Select the device as the run destination.
3. Configure the project's development team and signing.
4. Build for that destination.
5. Repeat the count, rejection, rotation and accessibility observations.
6. Record device model, OS, target and the source revision.

A successful simulator run and a successful device run are separate records.

## Plan a release checklist
Describe what the application currently does: an in-memory exercise counter calling shared C. List what it does not yet provide: durable progress, account synchronization and background work. Add these as later features with observable acceptance criteria.

## Useful regression task
Change only the C bridge's error handling in a practice copy. Confirm that the host boundary checks detect invalid-result changes. Then verify that the screen displays rejection without losing the previous count. The two layers answer different questions.

## Troubleshooting
Signing failures belong to device provisioning. Undefined symbols belong to linkage. A missing header belongs to source include configuration. Classifying the error prevents random setting changes.

## Next project
Add an explicit Save action using a target-supported Framework persistence service after checking its dependencies. Keep the user in control of the saved location or the platform's document picker. Do not add a hidden hard-coded desktop path to the mobile adapter.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-state-feedback-and-accessibility.md)


[Next: Connect a C declaration to its implementation](05-declaration-and-definition.md)
