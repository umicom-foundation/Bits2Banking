<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/25-capacity-and-backpressure.md

PURPOSE:
Explain the lesson: Follow backpressure through two stages.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow backpressure through two stages

## Prepare
Use the existing lesson_buffer and buffer_pipeline sources. The pipeline can retain two bytes, one per stage. Backpressure is the consumer's way of asking upstream stages to wait because it cannot accept more work.

## Fill the pipeline
Start from reset and keep output_ready zero. Offer 17, then 34, advancing only after each input handshake.

After two accepted bytes, stage two holds 17 and stage one holds 34. Neither may overwrite its word. The first stage therefore lowers input_ready.

The producer may offer 51, but it still owns that unaccepted byte. Counting an offered word as accepted would lose it when the pipeline fills.

## Lab
Make a table with columns for offered byte, input handshake, first stored byte, second stored byte and output handshake. Continue the trace while output_ready stays zero for three more edges.

Expected: stored bytes remain 34 and 17, and no additional input is accepted.

## Release capacity
Raise output_ready. The second stage can deliver 17 and accept 34 at the same edge. That permits the first stage to accept 51. Readiness propagates through the combinational connection; storage changes at the edge.

## Connect to software
A bounded software queue also refuses admission when full. In the work-dispatch example, the caller receives a status value. In this circuit, readiness expresses the admission condition. In both designs, the caller must retain an item until acceptance is established.

## Troubleshoot
If output changes while valid is one and ready is zero, inspect the buffer's hold condition. The pipeline scoreboard explicitly checks this requirement after every stalled edge.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](24-read-a-transfer-at-the-clock-edge.md) · [Next lesson](26-latency-and-throughput.md)

