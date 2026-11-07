<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/06-ready-valid-transfers.md

PURPOSE:
Explain the lesson: Move a word with ready and valid signals.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Move a word with ready and valid signals

## Before you begin
Read the register example or review its reset and clock-edge rules. Install GHDL for the practical exercise. A buffer temporarily holds data so a producer and consumer can progress at different times.

## Define a transfer
A producer asserts valid when it offers a word. A consumer asserts ready when it can accept a word. A transfer occurs at the agreed clock edge when both signals are 1.
~~~text
producer -> [input word | one stored word | output word] -> consumer
            valid/ready                   valid/ready
~~~
While a word is valid and the consumer is not ready, the stored word must stay unchanged. Otherwise the consumer could receive a different word from the one it was waiting for.

## Study the one-slot design
`full` records whether the buffer contains a word. It accepts input when empty, or when the current output will be accepted at the next edge. This allows an old word to leave while a new word replaces it.

Reset suppresses advertised transfers and clears stored state at the edge. Read the comments in `lesson_buffer.vhd` before changing that contract.

## Run the bench
~~~text
ghdl -a --std=08 lesson_buffer.vhd lesson_buffer_tb.vhd
ghdl -e --std=08 lesson_buffer_tb
ghdl -r --std=08 lesson_buffer_tb --assert-level=error --vcd=buffer.vcd
~~~
Expected observations: capture 2A, keep 2A while waiting, replace it with 77 when the consumer becomes ready, drain, then clear a pending word on reset.

## Lab
1. Make a table with columns edge, input_valid, input_ready, output_valid, output_ready and output_word.
2. Fill it from the bench assignments before running.
3. Mark transfers only when both handshake signals are high at an edge.
4. Compare your table with the waveform.
5. Add three waiting cycles and check stability in each.

## Software connection
Umicom queues also need an explicit acceptance boundary. Offering data does not prove it was consumed. Hardware ready/valid and a software return status are different mechanisms, but both require the caller to distinguish offered, accepted and completed work.

## Limits
This example has one clock domain. Crossing unrelated clocks requires additional synchronization design. Increasing the word width alone does not solve that problem.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/lesson_buffer.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-clocked-storage.md) · [Next lesson](07-waveforms-and-debugging.md)

