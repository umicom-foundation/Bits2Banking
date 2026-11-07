<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/47-test-adapters-and-user-journeys.md

PURPOSE:
Explain the lesson: Test both the shared rule and the user journey.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test both the shared rule and the user journey

## Before you begin

A test compares an observation with an expected result. The host bridge and button tests are ordinary C programs. The browser and phone exercises also need interface checks. Prepare only the platform you will execute; each lab README explains its tools.

## Use two levels of evidence

A model test can call the function directly with unusual inputs. A user-journey check follows the actual button, binding, rule and displayed result. Neither replaces the other.

~~~text
model check:    input -> C function -> expected output
journey check:  tap -> binding -> C function -> visible feedback
~~~

## Build a small matrix

For the shared bridge, check 0, 999, 1000, a negative value and a large value. For the sampled button, check held input, release, another press and two independent states. For each UI, check startup, one accepted action, repeated actions, refusal feedback and closing or reloading.

## Lab

1. Read each assertion in `test_bridge.c`.
2. State what fault it would detect.
3. Trace the same case through one UI.
4. Identify a failure the C test cannot see, such as a button with no event connection.
5. Write an expected visible result before performing the UI check.

## Record useful failures

A report saying “button broken” lacks the stage of failure. Record the source revision, platform, exact steps, expected result, observed result and relevant log excerpt. Keep credentials and personal content out of shared reports.

If the model passes but the UI fails, inspect the adapter and event wiring. If both fail, inspect their common rule and source identity before making platform-specific changes.

## Repeat after a fix

Run the failing case and nearby boundary cases. A fix for negative input should not break zero or the maximum accepted count. Keep the original regression case as evidence of the behavior that must remain protected.

## Completion check

Explain why a test called “opens window” cannot establish that saving, editing or compilation works. A useful test name and assertion describe the actual behavior exercised.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/test_bridge.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](46-build-targets-and-platform-evidence.md)


[Next: Share a C model with a microdevice](48-share-a-model-with-a-microdevice.md)
