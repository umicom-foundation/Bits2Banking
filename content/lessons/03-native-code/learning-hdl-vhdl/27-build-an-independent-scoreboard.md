<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/27-build-an-independent-scoreboard.md

PURPOSE:
Explain the lesson: Check every delivered word with a scoreboard.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check every delivered word with a scoreboard

## Prepare
Read the words array, sent counter and received counter in buffer_pipeline_tb.vhd. A scoreboard is a simple reference record of what should emerge from the circuit.

It records only accepted inputs. It does not infer the internal state of either buffer.

## Follow the reference model
When input_valid and input_ready are both one, the bench stores the offered number in expected(sent) and increments sent.

When output_valid and output_ready are both one, it compares the delivered byte with expected(received), then increments received.

The reference array is deliberately simpler than the hardware. It does not reproduce ready propagation or stage replacement rules.

## Lab
Trace accepted inputs 0, 1 and 2 with output sequence 0, 2, 1. Final counts match, but the second output comparison fails. Then try 0, 1, 1: the third comparison detects duplication.

Expected: both faults are detected even though the output count is three.

## Capacity check
The bench also checks that sent minus received remains at most two. Value order and occupancy are different properties; each catches defects that the other can miss.

## Troubleshoot
A scoreboard can itself be wrong. Check that its list grows only on input handshakes and shrinks only on output handshakes. Recording every cycle with input_valid one would count a stalled word repeatedly.

## Extend the experiment
Change the deterministic readiness pattern, keeping the stimulus bounded. Preserve the original bench and add a separate test if a new pattern exposes a different failure. Record the source revision and waveform for reproducibility; a passing count alone is insufficient evidence.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline_tb.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](26-latency-and-throughput.md) · [Next lesson](28-bound-a-simulation.md)

