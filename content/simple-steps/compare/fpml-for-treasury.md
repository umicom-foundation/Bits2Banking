<!--
Umicom Bits2Banking
File: content/simple-steps/compare/fpml-for-treasury.md

PURPOSE:
Give learners an additional practical case for FpML for Treasury and Trade Confirmation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare structural and business refusal points

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One synthetic XML record selects an unsupported view. A second uses the correct practice schema and view, but assigns the same party as payer and receiver.

1. Trace both records through the ordered checkpoints in Read and Validate the Import Boundary.
2. Mark the first rejecting step and which checks are still pending in each trace.

**Check your result.** The first record is rejected at view selection before term mapping. The second reaches mapped terms and is rejected by the distinct-party rule.

[Step-by-step course guide](../course-guides/fpml-for-treasury.md) · [Full course](../../courses/fpml-for-treasury/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/fpml-for-treasury.md)
