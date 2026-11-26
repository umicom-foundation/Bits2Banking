<!--
Umicom Bits2Banking
File: content/simple-steps/extension/distributed-learning.md

PURPOSE:
Give learners an additional practical case for Introduction to Distributed Learning, Blockchain and Verifiable AI.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Return a candidate from two checked deltas

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

For a synthetic one-weight experiment, both workers begin with checkpoint C12 and weight 2.000. Their equally sized training batches report deltas +0.10 and -0.04.

1. Check that both reports name C12 and have equal weight in this average. Add the two signed changes.
2. Divide the sum by two, then add the mean delta to the starting weight. Label that sum the candidate weight.

**Check your result.** The sum of deltas is +0.06 and the average is +0.03. The candidate is 2.030 while checkpoint C12 remains 2.000.

[Step-by-step course guide](../course-guides/distributed-learning.md) · [Full course](../../courses/distributed-learning/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/distributed-learning.md)
