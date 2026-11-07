<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/06-cint-and-result-checks.md

PURPOSE:
Explain the lesson: Use CInt and check the returned value.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use CInt and check the returned value

## Set up
Use Xcode on a Mac with an iOS Simulator runtime. Integrate the iPhone activity lab's SwiftUI view, bridging header, C bridge and activity source following its README. The reading trace can be completed without running Xcode.

`CInt` is the Swift spelling used here for the C `int` boundary. Choosing a compatible type makes the interface easier to understand; it does not eliminate the need to validate values.

## Read the action
~~~swift
let next = BtbActivityNext(completed)
if next >= 0 {
    completed = next
    message = "Exercise recorded"
}
~~~
The full source also handles a negative result. The bridge returns -1 when the request is refused. The screen must preserve its previous count on that path.

## Trace before running
Write these cases on paper:
- 0 becomes 1.
- 999 becomes 1000.
- 1000 cannot advance.
- A negative input is rejected before an unsigned conversion.

For each case, write the returned value and the visible value. They are not always the same: -1 is a failure signal, not the new activity count.

## Extend the interface
**Exercise:** propose how the screen could distinguish “activity full” from “invalid input.” Describe a typed result with a status and count. Keep the underlying decision in shared C/Framework behaviour; a thin Swift adapter should translate it for presentation.

## Troubleshoot
If the number changes unexpectedly, inspect the argument and return value before investigating colours or view spacing. If no C call occurs, return to the declaration/linking lesson. When logging, use these harmless integers; do not generalise the exercise into logging private application data.

Simulator execution, device execution and host bridge tests cover different boundaries. Keep their results separate and label a paper trace as a prediction.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/ActivityView.swift). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-declaration-and-definition.md) · [Next lesson](07-view-identity-and-state.md)

