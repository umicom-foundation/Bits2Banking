<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/12-connect-circuits-with-named-ports.md

PURPOSE:
Explain the lesson: Connect circuits with named ports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect circuits with named ports

A larger circuit can be built from smaller circuits with clear contracts. This lesson joins the existing pulse detector and saturating counter. Neither implementation needs to be copied into the other.

## Setup recap

Use the VHDL laboratory and GHDL with VHDL-2008 support. Read the port lists in sampled_pulse.vhd and lesson_counter.vhd. The COMPOSITION.md guide contains the complete simulation commands.

## 1. Identify the connection

pulse_counter declares an internal signal called enable_count. The detector writes it. The counter reads it through its enable input. The top-level detected output exposes the same signal so the testbench can observe the connection.

Named associations such as `enable => enable_count` make the relationship explicit. The name before the arrow belongs to the component; the name after it belongs to this containing architecture.

## 2. Explain the generic

The top-level width is passed to the counter using `generic map(width => width)`. The two occurrences refer to different scopes. The component receives the containing circuit's chosen width.

For width 2, count contains two bits and can represent 0 through 3. This example saturates at 3. The detector still produces pulses even after the counter is full.

## 3. Simulate the complete circuit

Analyze sampled_pulse.vhd, lesson_counter.vhd, pulse_counter.vhd and tb_pulse_counter.vhd in that order. Elaborate and run tb_pulse_counter with the commands in COMPOSITION.md.

An unknown entity error normally means that a dependency has not been analyzed into the working library. Check filenames and the VHDL standard flag before changing circuit logic.

## Exercise and explanation

Draw three boxes: detector, counter and testbench. Label the clock and reset connections shared by both components. Draw enable_count between them. Finally draw count and detected back to the testbench.

Change the order of the two instance declarations in a working copy. Their connections should retain the same meaning. VHDL describes concurrent hardware relationships; it is not a list of calls executed from top to bottom.

Keep the small component tests as well as the composition test. A component can satisfy its own contract while being connected incorrectly in a larger design.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/pulse_counter.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-detect-a-sampled-rising-edge.md) · [Next lesson](13-explain-one-clock-of-latency.md)

