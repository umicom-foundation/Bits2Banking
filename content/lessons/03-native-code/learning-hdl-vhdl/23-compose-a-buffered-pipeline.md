<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/23-compose-a-buffered-pipeline.md

PURPOSE:
Explain the lesson: Compose existing circuits into a pipeline.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compose existing circuits into a pipeline

## Prepare
Open the VHDL laboratory's PIPELINES guide. It contains the GHDL commands for PowerShell and Bash. You need only the source files to complete the first drawing exercise.

A component is a reusable circuit. An instance is one occurrence of that circuit inside a larger design. This example has two instances of lesson_buffer, called first_stage and second_stage. Each instance has its own stored byte and full flag.

## Read the connections
The first stage receives the external input. Its output becomes the second stage's input. Three internal signals connect them: middle_word, middle_valid and middle_ready.

Named port associations make each relationship visible:
```vhdl
output_valid => middle_valid,
output_ready => middle_ready,
output_word => middle_word
```
The names on the left belong to the component; names on the right belong to the surrounding design.

## Lab
Draw two boxes and copy every connection from the source. Mark the external ports at the outside edges. Trace a byte from input_word to output_word, then trace readiness backwards.

Expected: data and validity move towards the consumer; readiness returns towards the producer. No extra data storage exists in the connecting signals.

## Why reuse matters
Changing the buffer's ownership contract should require reviewing one implementation and both instances' integration. Copying the buffer process twice into the pipeline would create independent implementations that could drift apart.

## Troubleshoot
If GHDL cannot find the entity, analyse lesson_buffer.vhd before buffer_pipeline.vhd in the same working directory. The complete commands are in PIPELINES.md. Correct source ordering resolves a missing design unit; changing signal names will not.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](22-read-waveforms-as-evidence.md) · [Next lesson](24-read-a-transfer-at-the-clock-edge.md)

