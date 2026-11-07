<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/22-read-waveforms-as-evidence.md

PURPOSE:
Explain the lesson: Read waveforms as evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read waveforms as evidence

A waveform records how simulated signals change over time. It helps explain a failed assertion, but it must be interpreted together with the circuit's contract.

## Prepare

Run the timer simulation using the documented --vcd=timer.vcd option. Open the resulting file in a waveform viewer of your choice.

Add clk, reset, start, busy, done and the internal remaining signal if the viewer exposes it. The simulation commands are provided in PARITY-AND-TIMING.md.

## Locate one request

Find the rising edge where start is one and the timer is idle. Mark that as acceptance.

Count the next three rising edges. Compare the observed busy and done values with TIMING-WORKSHEET.md.

Inspect values immediately before and after each sampling edge. A signal change after the edge cannot affect the decision already made at that edge.

## Exercise

Find the extra start pulse while busy. Show why the remaining countdown does not restart. Then locate reset during the second request and verify that no later completion belongs to it.

Write down the exact assertion and time if the run fails.

## Preserve useful evidence

Keep the source revision, simulator version, command and first failing observation with your exercise notes. A waveform without source identity may describe a different circuit than the one currently open in the editor.

Do not turn a failed assertion into a warning merely to obtain a completion message.

## Understand the boundary

The waveform describes a simulation model. It does not include every physical delay, metastability effect or board connection. After simulation, synthesis and timing analysis provide different evidence.

This separation also applies to Umicom software: a static review, a unit check and a real device run answer different questions. Record which one you actually performed.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_request_timer.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](21-distinguish-a-pulse-from-a-level.md)


[Next: Compose existing circuits into a pipeline](23-compose-a-buffered-pipeline.md)
