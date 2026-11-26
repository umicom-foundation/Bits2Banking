<!--
Umicom Bits2Banking
File: content/simple-steps/extension/introduction-to-bitcoin-source-code.md

PURPOSE:
Give learners an additional practical case for Introduction to Bitcoin Source Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish two outputs that hold the same amount

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local transaction fixture called T6 has two output positions. Both positions hold 500 satoshis.

1. In the fixed source version, locate the type for a previous output reference and identify its transaction and output-index fields.
2. Use the two fields to write the reference for each fixture output and compare the two references.

**Check your result.** The references are T6 at index 0 and T6 at index 1. They identify distinct outputs despite the equal amounts.

[Step-by-step course guide](../course-guides/introduction-to-bitcoin-source-code.md) · [Full course](../../courses/introduction-to-bitcoin-source-code/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/introduction-to-bitcoin-source-code.md)
