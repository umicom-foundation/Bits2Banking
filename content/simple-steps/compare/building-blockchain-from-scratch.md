<!--
Umicom Bits2Banking
File: content/simple-steps/compare/building-blockchain-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Blockchain from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two hash input purposes on paper

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toy chain and a toy export share the same record bytes and previous-digest bytes. Their proposed visible domain labels are chain and export.

1. Draw each hash input as label followed by previous digest and record. Mark which intervals are identical.
2. Compare the two sequences at their first different byte. Record how much of the C label string is included.

**Check your result.** The labels differ at byte zero, c versus e. Each input includes its visible label bytes and omits the terminating C zero.

[Step-by-step course guide](../course-guides/building-blockchain-from-scratch.md) · [Full course](../../courses/building-blockchain-from-scratch/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/building-blockchain-from-scratch.md)
