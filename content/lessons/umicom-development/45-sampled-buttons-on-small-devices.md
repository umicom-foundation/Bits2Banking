<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/45-sampled-buttons-on-small-devices.md

PURPOSE:
Explain the lesson: Model a sampled button for a small device.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Model a sampled button for a small device

## Before you begin

No board is required for this first exercise. Open `button.h`, `button.c` and `test_button.c`. A sample is one observation taken at a moment in time. A physical button might be sampled repeatedly while it is held down.

## Count a new press

If every true sample increments the counter, holding a button produces many increments. The adapter remembers the previous sample. A rising edge means the previous sample was false and the current sample is true.

~~~text
sample:     false true true false true
new press:  no    yes  no   no    yes
count:      0     1    1    1     2
~~~

The structure contains the completed count and the remembered pressed state. The sample function updates that remembered state and asks the existing activity rule to advance only on a new press.

## Edge detection is one step

Mechanical contacts can bounce: one press may produce rapid true/false changes. This adapter does not debounce them. A board integration needs a documented debounce policy and tests using its sampling interval. It also needs pin configuration and electrical limits for the specific board.

## Lab

1. Trace the five samples above on paper.
2. Trace true, true, true from an initial false state.
3. Start at 999, press, release and press again.
4. Explain why the last press is rejected without increasing 1000.
5. Inspect the independent-state test: two devices must not share one hidden global count.

Follow the adapter README to build the host tests when ready. These tests use ordinary process memory and no device registers.

## Next integration step

Choose a board, read its pin and voltage documentation, then write a small platform adapter that supplies a logical pressed value. If the hardware is active-low, translate its low electrical level into true at that boundary. Reuse the existing model rather than copying its rule into a pin interrupt.

## Troubleshooting

Multiple increments can come from bounce, duplicate event delivery or shared state. Record the input sequence before changing the rule; otherwise a timing fault can be mistaken for an arithmetic fault.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/button.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](44-mobile-bindings-without-duplicated-rules.md) · [Next lesson](46-build-targets-and-platform-evidence.md)

