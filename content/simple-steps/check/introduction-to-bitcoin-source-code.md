<!--
Umicom Bits2Banking
File: content/simple-steps/check/introduction-to-bitcoin-source-code.md

PURPOSE:
Give learners an additional practical case for Introduction to Bitcoin Source Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check how two small fixtures reach the output-list guard

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two paper transactions each have one ordinary input. One has an empty output list. The other has a single output with amount zero.

1. In the fixed local source, locate the output-list check and trace the empty-list fixture to its result.
2. Trace the second fixture through that same check and stop the trace at the next rule.

**Check your result.** The empty list is rejected at the output-list check. A list containing a zero-valued output passes that particular check.

[Step-by-step course guide](../course-guides/introduction-to-bitcoin-source-code.md) · [Full course](../../courses/introduction-to-bitcoin-source-code/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/introduction-to-bitcoin-source-code.md)
