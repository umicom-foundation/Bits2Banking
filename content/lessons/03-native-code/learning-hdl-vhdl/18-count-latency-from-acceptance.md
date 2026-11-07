<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/18-count-latency-from-acceptance.md

PURPOSE:
Explain the lesson: Count latency from request acceptance.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count latency from request acceptance

Latency is the delay between an accepted request and its completion. To measure it, we must identify the acceptance event precisely.

## Prepare

Read request_timer.vhd and TIMING-WORKSHEET.md. The timer has a clock, reset and start input, plus busy and done outputs.

CYCLES is a positive generic: a configuration value chosen when the circuit instance is elaborated. The default is three.

## Identify acceptance

When the timer is idle and start is one at a rising clock edge, it stores CYCLES in remaining and sets active to one. Call this edge A.

The countdown begins on subsequent edges while active is one.

For CYCLES = 3, remaining becomes two at A + 1, one at A + 2 and zero at A + 3. Done becomes one at A + 3.

## Exercise

Fill the worksheet without running a simulator. Then repeat with CYCLES = 1. The request completes at the next rising edge after acceptance.

Do not count the acceptance edge as the first decrement; that would change the specified latency.

## Observe the test

The test checks busy and done after every relevant edge. These checks detect both early completion and a countdown that was unexpectedly restarted.

If only the final done state were checked, the timing error could be missed.

## Relate to a device interface

A peripheral may accept a command and finish later. A driver needs to know whether a request was accepted, whether work remains active and how completion is reported.

This circuit illustrates the timing contract without implementing a physical peripheral. Its inputs must already be synchronous to the clock, and it needs a reset edge before use.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/request_timer.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](17-keep-unknown-signals-visible.md) · [Next lesson](19-specify-busy-time-request-policy.md)

