<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/introduction-to-bitcoin-source-code.md

PURPOSE:
Give learners an additional practical case for Introduction to Bitcoin Source Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the first result when a fixture has no inputs

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local reading fixture models a transaction with two outputs and an empty input list.

1. In the fixed source version, locate the initial empty-input check in the basic transaction validation function.
2. Trace the decision for this fixture and compare it with a record that has an input.

**Check your result.** The empty-input fixture takes the rejection branch before output totals are inspected. The second fixture continues past that check.

[Step-by-step course guide](../course-guides/introduction-to-bitcoin-source-code.md) · [Full course](../../courses/introduction-to-bitcoin-source-code/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/introduction-to-bitcoin-source-code.md)
