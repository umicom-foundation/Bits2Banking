<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/28-bound-a-simulation.md

PURPOSE:
Explain the lesson: Make a stalled simulation finish with evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make a stalled simulation finish with evidence

## Prepare
Find the loop from cycle 0 to 199 in the pipeline bench. It supplies up to 64 words while the consumer alternates between ready and waiting.

The loop has a finite budget. A broken design that never delivers its final word must fail with a useful message instead of running forever.

## Understand the two exits
The normal exit happens when received reaches 64. After the loop, an assertion requires both sent and received to equal 64.

If the normal exit never occurs, the loop ends after its budget and the same assertion reports incomplete delivery.

## Lab
On paper, suppose input_ready remains zero throughout. What values remain in sent and received? Both remain zero. The final assertion fails; it does not describe the run as successful merely because simulated time advanced.

Now suppose only 63 words emerge. The assertion again fails and distinguishes incomplete work from a complete drain.

## Choose a budget
The supplied readiness pattern accepts downstream work on three of every five cycles. Two hundred cycles gives this small test room to fill, wait and drain. It is a test budget, not a universal performance guarantee.

## Troubleshoot
Increasing a timeout can conceal a deadlock. First determine whether any handshake continues to occur. Preserve the last accepted input and last delivered output numbers.

## Connect to applications
A build runner, media export service or network request also needs a completion condition and a bounded waiting policy. A timeout should leave evidence about incomplete work. It must not silently convert an unfinished operation into a success result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline_tb.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](27-build-an-independent-scoreboard.md) · [Next lesson](29-reset-a-composed-system.md)

