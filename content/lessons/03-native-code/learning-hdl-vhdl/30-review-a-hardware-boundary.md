<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/30-review-a-hardware-boundary.md

PURPOSE:
Explain the lesson: Review a circuit before moving to a device.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Review a circuit before moving to a device

## Prepare
Use the pipeline source, testbenches and their expected traces. No hardware is required for this review.

A simulator checks a model under chosen inputs. A physical implementation also depends on clocks, pins, timing constraints and electrical connections.

## Make a boundary inventory
List every external signal. For each, identify who drives it, when it changes and which clock samples it. The current pipeline assumes a shared clock for producer, buffers and consumer.

An input from another clock domain requires a separate crossing design. The ready/valid wires alone do not make an asynchronous transfer safe.

## Lab
Draw a producer running on clock A and the pipeline on clock B. Circle each signal crossing that boundary. Explain why merely connecting the clocks' names to different sources changes the assumptions behind the existing testbench.

Expected: input_word and input_valid, plus returning input_ready, need a coherent crossing protocol. Independently synchronising bits of a data word does not establish that they belong to the same transfer.

## Create an implementation checklist
Identify a specific board, supported synthesis tool, oscillator frequency, reset source and pin constraints. Record these choices before generating a bitstream. Keep the portable circuit and board-specific configuration separate.

## Troubleshoot
A simulation pass followed by a board failure does not prove that the simulator is wrong. Check constraints, reset timing and clock-domain assumptions, then inspect the actual design.

## Continue
Use the microdevice examples in Learning Umicom Framework to compare software polling with clocked hardware. Both need explicit ownership and timing, but neither example automatically qualifies the other platform.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](29-reset-a-composed-system.md)


Continue with [Create a CPU simulation project in Studio](31-create-a-cpu-project.md).
