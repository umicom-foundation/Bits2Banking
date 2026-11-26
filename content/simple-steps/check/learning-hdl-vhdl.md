<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-hdl-vhdl.md

PURPOSE:
Give learners an additional practical case for Learning HDL and VHDL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check priority when reset and enable overlap

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice four-bit counter starts at 0101. On the next rising edge enable is high. One case also asserts reset and the other leaves reset low.

1. Use the reset-priority lesson to write expectations for each case before inspecting any simulated output.
2. Replay the two input sets from the same starting count. Compare the first sampled result after the edge with each expectation.

**Check your result.** With reset asserted the next sampled count is 0000. With reset low and enable asserted it is 0110.

[Step-by-step course guide](../course-guides/learning-hdl-vhdl.md) · [Full course](../../courses/learning-hdl-vhdl/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-hdl-vhdl.md)
