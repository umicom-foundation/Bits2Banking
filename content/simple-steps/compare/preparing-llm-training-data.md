<!--
Umicom Bits2Banking
File: content/simple-steps/compare/preparing-llm-training-data.md

PURPOSE:
Give learners an additional practical case for Preparing Data for LLM Training.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare source grouping with row grouping

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toy dataset contains three rows from one source and one from a second source.

1. Draw a split that assigns individual rows first. Mark where the first source could straddle training and evaluation.
2. Draw a split assigned by source before its rows. Compare which assignment protects the evaluation boundary.

**Check your result.** Source-first assignment keeps the three related rows together and removes that overlap.

[Step-by-step course guide](../course-guides/preparing-llm-training-data.md) · [Full course](../../courses/preparing-llm-training-data/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/preparing-llm-training-data.md)
