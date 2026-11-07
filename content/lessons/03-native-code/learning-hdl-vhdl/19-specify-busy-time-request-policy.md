<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/19-specify-busy-time-request-policy.md

PURPOSE:
Explain the lesson: Specify what happens to a request while busy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Specify what happens to a request while busy

A circuit must define what happens when new work arrives before earlier work finishes. Ignoring, rejecting, queuing and replacing are different policies.

## Prepare

Open request_timer.vhd. This teaching timer accepts a start pulse only while idle. A pulse while active is ignored and is not saved for later.

Read the comment above the clocked behavior before tracing the code.

## Follow branch priority

Reset is checked first. If reset is inactive, an active request follows the countdown branch. Only an idle timer reaches the start branch.

Therefore a start pulse during active work cannot replace remaining with CYCLES.

## Find the test

tb_request_timer pulses start again while the original countdown is active. Completion must still occur at the original expected edge.

After completion, the test checks that no queued request appears. This verifies both timing and the absence of hidden storage.

## Exercise

Draw two requests, one at acceptance and one two edges later. Mark the second as ignored. Then design a different interface that could report rejection explicitly.

Would you add ready, an accepted pulse, or a queue? Explain the extra state and tests your choice requires.

## Avoid a misleading button model

A physical button held down produces a level over many cycles. It does not automatically produce one start pulse. After the timer becomes idle, a later edge could accept the still-high level as another request.

Use an appropriate edge detector and input-conditioning design when adapting a button. The earlier sampled-pulse lesson explains the synchronous edge concept; physical synchronization and debounce remain separate concerns.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/request_timer.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](18-count-latency-from-acceptance.md) · [Next lesson](20-cancel-work-with-reset.md)

