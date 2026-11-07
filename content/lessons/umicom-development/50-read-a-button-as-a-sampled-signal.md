<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/50-read-a-button-as-a-sampled-signal.md

PURPOSE:
Explain the lesson: Read a button as a sampled signal.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a button as a sampled signal

Software observes a physical input at particular times. Those observations are samples. An event that begins and ends between two samples may never be seen, and a noisy contact may appear as several changes.

## Setup recap

Read button.c and test_button.c in labs/native/activity-adapters. Their README gives the host build commands and the Framework header requirement. The Pico main.c calls the same function repeatedly and pauses about 10 milliseconds between calls.

## 1. Follow the stored state

BtbActivityButton contains the completed count and was_pressed. For each sample, the adapter compares pressed with was_pressed. Only a false-to-true change asks the activity model to advance.

After considering the sample, the adapter retains the latest input state. This prevents a held button from being counted on every loop iteration.

## 2. Compare logical and physical evidence

The host test supplies exact true and false values. It can check a held input, release and second press, a null state pointer and a full counter.

A real button can bounce between electrical levels during one physical press. The current adapter will count those sampled rises. That is consistent with its sample-level contract and may still be unsuitable for the desired user experience.

## 3. State the missing policy

A debounce policy might require an input to remain stable for a chosen interval. Such a policy needs a time source, a chosen interval and defined behavior at startup. It should be tested independently before replacing the sampling adapter in a device application.

Do not claim a 10-millisecond sleep automatically provides debounce. It changes the sampling rate, but does not prove that contact transitions are filtered.

## Exercise and explanation

Compare the sample sequences 0,1,1,1,0 and 0,1,0,1,0. The first produces one event. The second produces two. Write a sentence explaining why both could arise from different physical behavior.

At the maximum count, additional rises cannot increase the model. Read the returned status before presenting a successful increment. A front end should communicate capacity separately from an input sampling error.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/button.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](49-understand-a-cross-compiled-build.md) · [Next lesson](51-record-a-device-observation.md)

