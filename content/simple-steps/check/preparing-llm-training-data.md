<!--
Umicom Bits2Banking
File: content/simple-steps/check/preparing-llm-training-data.md

PURPOSE:
Give learners an additional practical case for Preparing Data for LLM Training.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a clean split and an overlapping split

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A clean classroom list assigns A to training and B to evaluation. A second list assigns A to both.

1. Write the source-ID sets before inspecting record text. Compute the intersection for each list.
2. Use the course’s split review to record whether each input passes the source-isolation requirement.

**Check your result.** The first intersection is empty. The second includes A and fails the requirement.

[Step-by-step course guide](../course-guides/preparing-llm-training-data.md) · [Full course](../../courses/preparing-llm-training-data/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/preparing-llm-training-data.md)
