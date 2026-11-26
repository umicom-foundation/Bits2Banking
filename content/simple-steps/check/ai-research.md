<!--
Umicom Bits2Banking
File: content/simple-steps/check/ai-research.md

PURPOSE:
Give learners an additional practical case for AI Research Frontiers — Architectures, Training, Data and Native Kernels.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a low-rank parameter count in two sizes

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A classroom LoRA note estimates only the trainable factors for one frozen projection. Both cases use 256 input and 256 output values. Compare rank two with rank four.

1. Assign 256 by rank elements to one factor and rank by 256 to the other. Write a row per rank with both products.
2. Add the two products in each row. Record what the figures count and one measurement needed before accepting a memory claim.

**Check your result.** Rank two uses 1,024 trainable factor elements. Rank four uses 2,048. A peak-memory claim still needs a measured run.

[Step-by-step course guide](../course-guides/ai-research.md) · [Full course](../../courses/ai-research/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/ai-research.md)
