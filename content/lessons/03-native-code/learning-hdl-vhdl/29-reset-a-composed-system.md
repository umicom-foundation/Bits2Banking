<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/29-reset-a-composed-system.md

PURPOSE:
Explain the lesson: Reset every stage of a composed system.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reset every stage of a composed system

## Prepare
Open buffer_pipeline_reset_tb.vhd. Its edge procedure waits for a rising clock edge and then allows one nanosecond for outputs to settle.

This exercise fills both storage stages before reset. Resetting an empty design would not prove that pending data is discarded.

## Read the scenario
1. Reset to an empty pipeline.
2. Offer byte 17, then byte 34, with the consumer stopped.
3. Confirm the output presents 17 and input_ready is zero.
4. Assert reset and make the consumer ready.
5. Check that no transfer is advertised during reset.
6. Apply a rising edge to clear stored state.
7. Send byte 51 and verify it is the only result.

The test distinguishes suppression of visible handshakes from clearing internal registers.

## Lab
Draw the two stored bytes immediately before reset and immediately after the reset edge. Then draw the path of 51 through the empty pipeline.

Expected: neither 17 nor 34 appears in the new sequence.

## Why both stages matter
If only the first stage were reset, the second could still expose an old word. If only the second were reset, the first could forward an old word after reset ended. Shared reset wiring is part of the composition contract.

## Troubleshoot
A test that deasserts reset before a rising edge has not necessarily reset synchronous storage. Keep reset asserted across an active edge as the bench does.

## Scope
This reset policy intentionally discards pending work. A software service that promises to finish accepted requests may need draining instead. Document the policy before treating reset as a universal shutdown mechanism.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline_reset_tb.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](28-bound-a-simulation.md) · [Next lesson](30-review-a-hardware-boundary.md)

