<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/10-check-the-whole-native-path.md

PURPOSE:
Explain the lesson: Check the complete Swift-to-C workflow.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the complete Swift-to-C workflow

## Prepare a reproducible check
Follow the iPhone activity lab setup on a Mac with Xcode and an iOS Simulator runtime. Record the source revision, Xcode version, destination and configuration. Begin with the default count of 0.

A **regression check** repeats an important behaviour after a change to discover whether something previously supported has broken.

## Check the ordinary workflow
1. Launch the application.
2. Confirm the initial count and Ready message.
3. Press Complete exercise.
4. Expect 1 and Exercise recorded.
5. Press twice more and expect 3.
6. Close and relaunch; record the in-memory reset behaviour.

Check native boundary values using the existing host bridge tests as well. A screen workflow and a C test complement each other.

## Classify a failure
If the button appears but does nothing, locate the action closure. If the closure runs but the C function is unavailable, inspect import/linking. If C returns -1, inspect its input and model rule. If C returns 1 but the display remains 0, inspect state assignment and presentation.

This sequence follows the evidence in order. It avoids replacing a working core function because a control was unwired.

## Exercise
Write an expected/observed table for the six steps. Add one row for a refused completion at full capacity in an isolated test setup. Expected behaviour: the old count remains visible and an explanation appears.

## Finish responsibly
Record skipped device or accessibility checks explicitly. Do not label the application release-ready because a single simulator press worked. The lab teaches a reusable integration boundary; further Framework services, durable project storage and lifecycle behaviour need their own checks.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-accessible-actions-and-messages.md)

