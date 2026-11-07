<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/03-state-feedback-and-accessibility.md

PURPOSE:
Explain the lesson: Keep screen state and feedback understandable.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep screen state and feedback understandable

## Before you begin
Use the ActivityLab project connected to the supplied C sources. Run it on an iPhone simulator. A state value belongs to the screen while that screen exists. Persistence means storing a value so it can survive a later launch; this example has not added persistence.

## Read the event
~~~swift
let next = BtbActivityNext(completed)
if next >= 0 {
    completed = next
    message = "Exercise recorded"
} else {
    message = "No change: check the count or begin another activity"
}
~~~
The button asks the model for a result. The screen changes its count only after acceptance. On rejection, the previous count remains visible and a message explains what happened.

## Check a normal interaction
1. Launch with zero completed exercises.
2. Press Complete exercise once. Expect 1.
3. Press it twice more. Expect 3.
4. Rotate the simulator and inspect the layout.
5. Increase the simulator's text size and check that the button and feedback remain understandable.
6. Use an accessibility reader to find the labelled button and count.

Record each observed result. A C unit test cannot establish text readability or focus order.

## Explore state lifetime
Stop and relaunch the app. This view initializes its state to zero. A fresh zero is consistent with its current design. If the product should resume progress tomorrow, specify when and where it is saved, how errors appear, and which version of the data is supported before adding storage.

## Boundary exercise
In a practice copy initialize completed to 999. The next press should show 1000; a further press should retain 1000 and display the rejection message. Restore zero afterwards. The model's host checks cover these values without needing a thousand taps.

## Connect to other Umicom screens
A UI should show both accepted changes and rejected operations. Silent failure makes a working rule appear broken. Follow that principle when adding file saving, media rendering or a build action to a Framework-backed application.

## Recovery
If tapping changes nothing, first inspect the event breakpoint, then the native return value, then the state assignment. Investigate one boundary at a time.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/ActivityView.swift). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](02-call-the-shared-c-model.md) · [Next lesson](04-simulator-device-and-evidence.md)

