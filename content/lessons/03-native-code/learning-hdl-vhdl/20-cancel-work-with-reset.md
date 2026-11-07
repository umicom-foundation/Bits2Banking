<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/20-cancel-work-with-reset.md

PURPOSE:
Explain the lesson: Cancel pending work with reset.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Cancel pending work with reset

Reset establishes a known state. In the request timer it also cancels any active request, so completion must not appear later for that cancelled work.

## Prepare

Read the second request sequence in tb_request_timer.vhd. The test starts a request, then asserts reset before the countdown completes.

The timer's reset is synchronous: the state changes at a rising clock edge where reset is one.

## Predict the observation

At the reset edge, remaining becomes zero, active becomes zero and done becomes zero. The reset branch takes priority over countdown and start.

The test then releases reset and watches several idle edges. Busy and done must remain zero.

## Why watch afterward?

Checking only the reset edge could miss a stale counter or pending event that produces completion later. The follow-up observations test that cancellation persists.

This is analogous to checking that a cancelled software job does not publish a late result.

## Exercise

Assert reset at the edge where completion would otherwise occur. Write the expected busy and done values.

Then assert start and reset together. The defined priority means reset wins and no request is accepted.

## Run and investigate

Use PARITY-AND-TIMING.md for simulator commands. When a check fails, inspect reset before the rising edge and outputs after scheduled updates have settled.

Do not assume a reset that changed after the sampling edge was observed at that edge.

## Extend carefully

An asynchronous reset has a different timing contract and physical implementation concerns. Changing the sensitivity list alone is not a complete design decision. Keep this lesson's synchronous behavior explicit when connecting it to other circuits.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_request_timer.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](19-specify-busy-time-request-policy.md) · [Next lesson](21-distinguish-a-pulse-from-a-level.md)

