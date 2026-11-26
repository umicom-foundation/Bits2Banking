<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-hdl-vhdl.md

PURPOSE:
Give learners an additional practical case for Learning HDL and VHDL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace backpressure across two clock edges

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A two-stage simulation has an output word 1010 waiting. The downstream ready signal is low on the first edge and high on the second.

1. Draw valid, ready, and data at both rising edges using the transfer rule from the pipeline lesson.
2. Mark each edge where the word is delivered and add only that edge’s data to a scratch scoreboard.

**Check your result.** The first edge delivers nothing. The second delivers one word, 1010, and the scoreboard contains exactly one entry.

[Step-by-step course guide](../course-guides/learning-hdl-vhdl.md) · [Full course](../../courses/learning-hdl-vhdl/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-hdl-vhdl.md)
