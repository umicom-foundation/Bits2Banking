<!--
Umicom Bits2Banking
File: content/simple-steps/check/umicom-os-from-scratch.md

PURPOSE:
Give learners an additional practical case for Umicom OS from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check which boot report stays visible

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In the hosted comparison lab, one sample records the transition from starting to ready. A second sample has a malformed report.

1. Run or trace the successful comparison and write down its state change. Identify which variable saves its change flags.
2. Pass the malformed report through the same check. Record its error beside the unchanged flags from the valid comparison.

**Check your result.** The first comparison shows starting to ready. The second is refused and leaves the saved comparison available under its original source label.

[Step-by-step course guide](../course-guides/umicom-os-from-scratch.md) · [Full course](../../courses/umicom-os-from-scratch/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/umicom-os-from-scratch.md)
