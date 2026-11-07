<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/07-waveforms-and-debugging.md

PURPOSE:
Explain the lesson: Use assertions and waveforms to locate a circuit error.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use assertions and waveforms to locate a circuit error

## Prepare
Use the supplied VHDL lab and GHDL. A waveform is a graph of signal values over simulated time. You can inspect it with a compatible viewer; assertions remain useful even without that viewer.

## Preserve the first failure
Run the buffer bench with `--assert-level=error --vcd=buffer.vcd`. If an assertion fails, record the message and time. The first incorrect transition is often more useful than the many values that become wrong afterwards.

## Work backward from the contract
Suppose a waiting output changes from 2A to 77. Ask:
1. Was output_valid high?
2. Was output_ready low at the relevant edge?
3. Did the design nevertheless accept new input?
4. Did the bench change an input exactly at the edge, creating an ambiguous test stimulus?
5. Was reset active?

The supplied bench changes inputs after an edge and waits before observation. It separates stimulus from observation to make the intended sequence readable.

## Practical investigation
Copy the lab into a practice folder. In that copy, deliberately allow the buffer to accept a word whenever input_valid is high. Run the bench and locate the stalled-word failure. Draw the incorrect state transition. Restore the original acceptance expression and rerun.

## A small evidence record
~~~text
Design: lesson_buffer
Tool version: record your installed version
Command: record the complete command
First failure: message and simulated time
Expected: held word remains 2A while receiver waits
Observed: write the actual value
Correction: describe the acceptance condition
Rerun: record the actual result
~~~
A record should distinguish a predicted result from an executed result. The same habit is useful when investigating Umicom build or test failures.

## Useful extensions
Add a check for valid staying asserted throughout the wait. Add a reset while a word is pending. Keep each assertion tied to one public promise.

## Recovery
A trace with no clock transitions may mean the bench did not run, the wrong entity was selected, or the clock source stopped. Inspect the command and selected design before changing the circuit.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/lesson_buffer_tb.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-ready-valid-transfers.md) · [Next lesson](08-from-model-to-hardware.md)

