<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/11-draw-a-state-machine.md

PURPOSE:
Explain the lesson: Draw the states an operation can occupy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Draw the states an operation can occupy

## Prepare
Open BtbTimerState in deadline.h. A state machine is a model of named situations and the operations that move between them.

The timer has IDLE, PENDING, FIRED and CANCELLED states.

## Draw permitted changes
```text
IDLE --arm--> PENDING --fire when due--> FIRED
                  |
                  +--cancel before due--> CANCELLED
FIRED or CANCELLED --arm--> PENDING
```
A pending timer cannot be armed again by this API. The caller must complete or cancel the current wait first.

## Lab
Start with an initialised timer. Write the expected state after arm, fire-too-early, cancel and arm-again.

Expected: PENDING, PENDING, CANCELLED, PENDING. Refused operations do not invent an extra state.

## Read the implementation
BtbDeadlineArm checks for PENDING before constructing its candidate value. BtbDeadlineFire changes state only after Status returns DUE.

These checks make the arrows in the diagram concrete.

## Troubleshoot
A state diagram can be misleading if it omits conditions. Label “fire” with “when due” and “cancel” with “before due.” Otherwise it appears that either operation is always allowed.

## Connect to applications
Documents, build jobs, media renders and broker orders all have lifecycles. Their states and transitions differ, but the method is reusable: list states, permitted transitions, refusal behaviour and observable results before writing event handlers.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-model-a-clock-with-a-record.md) · [Next lesson](12-check-before-at-and-after.md)

