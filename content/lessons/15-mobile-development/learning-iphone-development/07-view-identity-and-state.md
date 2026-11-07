<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/07-view-identity-and-state.md

PURPOSE:
Explain the lesson: Understand a SwiftUI view's state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand a SwiftUI view's state

## Prepare
Create and run the iPhone activity lab in Xcode using the setup in its README. Start with the default `completed` value of 0. A **view** describes what should appear; **state** holds values that can change and cause the presentation to be updated.

## Locate the state
The source declares:
~~~swift
@State private var completed: CInt = 0
@State private var message = "Ready"
~~~
The button calls the shared C function, then assigns successful results to those values. The text uses the current values when the view is presented.

## Observe a short session
1. Launch the app.
2. Press Complete exercise three times.
3. Record the count and message.
4. Change the simulator orientation.
5. End the app session and launch again.
6. Record the result, distinguishing recreation from a new session.

The lab has no durable progress file. A screen value existing during a session should not be advertised as a saved learning record.

## Design a future save operation
**Exercise:** write three requirements for saving progress: choose or identify the destination, report success/failure, and restore a validated value later. Add a requirement to preserve the visible state when saving fails. Those requirements guide a shared persistence service rather than a hidden write inside every button handler.

## Recover from unexpected behaviour
First confirm that the app entry point presents `ActivityView()`. Keep the generated `App` entry point and replace only its view expression as the README explains. Two competing entry points cause a build problem, not a state-management feature.

The expected workflow is deliberately small: one screen, one count and one C transition. Use it to learn ownership before adding project documents, accounts or background jobs.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/ActivityView.swift). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-cint-and-result-checks.md) · [Next lesson](08-simulator-and-device-builds.md)

