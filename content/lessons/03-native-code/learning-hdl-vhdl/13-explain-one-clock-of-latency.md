<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/13-explain-one-clock-of-latency.md

PURPOSE:
Explain the lesson: Explain one clock of latency.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain one clock of latency

Latency is the delay between an accepted input and its visible result. It can be measured in clock cycles. A result arriving one cycle later is correct when that delay is part of the circuit's contract.

## Setup recap

Open pulse_counter.vhd and tb_pulse_counter.vhd in the VHDL laboratory. The simulator commands are in COMPOSITION.md. For a paper trace, start immediately after a reset edge with count 0 and pulse 0.

## 1. Follow the first rise

At the next edge sampled_input is 1. The detector schedules pulse 1. The counter reads the old pulse, which is still 0 for this edge, and holds count 0.

After the simulator applies the scheduled signal updates, the visible values are pulse 1 and count 0. At the following edge the counter reads pulse 1 and schedules count 1.

## 2. Read the test's observation point

The step procedure waits for rising_edge(clk) and then waits another 1 ns. That second wait allows scheduled updates to settle before assertions examine outputs. It is a testbench observation delay, not an extra delay inserted into the hardware.

The clock period is 10 ns, so the observation remains well before the next rising edge. Reducing the period below this observation interval would require reviewing the test.

## 3. Compare two traces

For a held-high input, the first two output pairs are (pulse 1, count 0) and (pulse 0, count 1). Keeping the input high for a third edge leaves count 1.

For samples 1, 0, the count still becomes 1 on the second edge. The second sample can be low while the previously detected event is being counted.

## Exercise and troubleshooting

Change the first expected count from 0 to 1 in a private working copy of the test. Predict which assertion should fail and why. Restore the expected contract after inspecting the result.

Do not repair this mismatch by increasing an arbitrary timeout. The issue is the relationship between two registered stages. Write that relationship into a timing table before editing the implementation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_pulse_counter.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-connect-circuits-with-named-ports.md) · [Next lesson](14-reset-a-pending-event.md)

