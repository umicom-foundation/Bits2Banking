<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/15-observe-mobile-lifecycle-and-input.md

PURPOSE:
Observe mobile input and application lifetime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Observe mobile input and application lifetime

## Before starting

Have an Android or iOS build installed on a test target, or prepare a written observation sheet until one is available. Keep the original desktop form layout so the exercise compares the same controls. Device accessibility and layout observations are still needed even when the offscreen desktop event test passes.

## Separate lifetime from storage

QObject parent ownership controls when widgets are destroyed. It does not write application state to durable storage. The profile lab has no save operation. Returning to an existing process may preserve its field, while restarting a new process begins with the initial form. Do not promise retention after termination without implementing and testing an explicit state store.

## Run an input journey

1. Launch the lab and focus Profile name. Record whether the on-screen keyboard leaves Check name and the result reachable.
2. Enter Alice_7, tap Check name and record the exact result.
3. Replace it with ../../other, tap again and confirm the old success disappears.
4. Rotate the device or resize the simulator, then inspect wrapping and focus.
5. Move to the background and return. Record whether the same process survived.
6. Close and relaunch through the target’s normal process controls. Compare the initial state.

## Keep the callback boundary

The current callback owns its QByteArray until the synchronous C call returns. It publishes a result immediately and keeps no borrowed pointer afterward. If future work becomes asynchronous, keeping bytes.constData() after the array is destroyed would be a lifetime defect. Copy data into an owned request and define cancellation when the view closes before adding a worker.

## Exercise and worked answer

A name disappears after relaunch. Is that automatically a persistence bug? In this lab, no persistence contract exists. Record the behavior and the current limit. If a product later requires draft recovery, define what is saved, where it is stored, when it is restored and what happens to rejected input; then implement that reusable behavior in Framework before wiring the view.

## Completion check

Use device accessibility inspection to confirm the input’s accessible name and a usable control order. Record failures with the device, text scale and orientation. Do not report accessibility as passed from object names in source alone. The useful result is a reproducible observation and a specific missing behavior, not a generic claim that mobile support works.

## Read the source

[labs/framework/qt-profile/profile_window.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/profile_window.cpp). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Build and observe the lab on iOS](14-build-and-observe-on-ios.md) · [Next: Compare desktop, web and mobile release evidence](16-compare-desktop-web-and-mobile-evidence.md)
