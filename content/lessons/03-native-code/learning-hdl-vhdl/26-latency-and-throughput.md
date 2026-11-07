<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/26-latency-and-throughput.md

PURPOSE:
Explain the lesson: Measure latency and throughput separately.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Measure latency and throughput separately

## Prepare
Open PIPELINES.md and draw rising edges labelled 1 through 6. Reset both stages before edge 1. Keep the consumer ready throughout this exercise.

Latency describes how long one accepted item takes to reach its destination. Throughput describes how many items a system can deliver over an interval.

## Trace the first word
At edge 1, word A enters stage one. At edge 2, A moves into stage two and B can enter stage one. A is now presented at the external output. At edge 3, the consumer accepts A while B moves forward and C enters.

The two storage stages therefore separate input acceptance from output acceptance by two clock intervals in this trace.

## Continue the table
| Edge | Input accepted | Output accepted |
|---|---|---|
| 1 | A | None |
| 2 | B | None |
| 3 | C | A |
| 4 | D | B |
| 5 | E | C |

Once filled, the design can deliver one byte per edge despite the initial delay.

## Exercise
Introduce two edges with output_ready zero after edge 3. Recalculate the table. Do not add a fixed two-edge delay to every later input: waiting changes when acceptance occurs.

## Troubleshoot
When reporting performance, state whether you measured offered inputs, accepted inputs, presented outputs or accepted outputs. A valid output held for four edges is one waiting word, not four delivered words.

## Hardware boundary
Simulation time comes from the testbench clock. It does not establish the maximum clock frequency of a physical circuit. Synthesis and timing analysis are needed before converting this throughput into a claim about a particular board.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](25-capacity-and-backpressure.md) · [Next lesson](27-build-an-independent-scoreboard.md)

