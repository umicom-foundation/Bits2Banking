<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/14-reset-a-pending-event.md

PURPOSE:
Explain the lesson: Reset a pending event.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reset a pending event

Reset is a behavior that must be designed. In the composed pulse counter, reset clears both stages and discards any event waiting between them. This is useful when beginning a new counting session.

## Setup recap

Use GHDL and the four circuit files listed in COMPOSITION.md. Read the testbench's final sequence, beginning with the comment about a pending event. A pending event is a detected pulse that the counter has not yet consumed.

## 1. Create the pending event

Start with both stages reset. Release reset and sample 1. The detector produces a pulse, but the counter remains zero because it consumes the previous pulse.

Now assert reset before the next rising edge. Both components see reset 1 at that edge. The detector clears its remembered input and pulse. The counter clears its count instead of consuming the pending pulse.

## 2. Decide what a held input means

The test keeps sampled_input high while reset is released. The detector's remembered value is zero after reset, so this high sample creates a new pulse. One edge later the counter becomes 1.

Another design could require the input to return low before accepting a new rise. That would be a different contract with additional state. Do not change the behavior silently; update the explanation and tests if choosing that policy.

## 3. Separate reset from saturation

Saturation retains the maximum count when additional events arrive. Reset explicitly returns the count to zero. The test reaches the maximum first, checks that it does not wrap, then checks reset and restart.

These cases answer different questions and should remain separate assertions.

## Exercise and explanation

Write expected pulse and count for this sequence: reset; high; reset while high; release reset while high; hold high. The post-edge pairs are (0,0), (1,0), (0,0), (1,0), (0,1).

If the fourth pair contains no pulse, inspect whether the detector retains its previous sample through reset. If the third count is 1, inspect reset priority in the counter. A useful failure report identifies which stage violated the chosen behavior.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_pulse_counter.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-explain-one-clock-of-latency.md)


[Next: Combine bits with XOR](15-combine-bits-with-xor.md)
