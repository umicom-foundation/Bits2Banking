<!--
Umicom Bits2Banking
File: content/simple-steps/check/distributed-learning.md

PURPOSE:
Give learners an additional practical case for Introduction to Distributed Learning, Blockchain and Verifiable AI.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the factor-averaging trap with a tiny pair

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The scalar LoRA lesson treats a dense delta as B times A. In case one both workers use A = 1 and B = 2. In case two one has that pair and the other uses A = 2 and B = 1.

1. For each case take the mean of the two dense products. Then calculate the separate means of A and B and multiply those means.
2. Write one acceptance statement that checks the merged dense update for both cases.

**Check your result.** Both correct dense means are 2. Separate factor averaging yields 2 in case one and 2.25 in case two, so it fails the second check.

[Step-by-step course guide](../course-guides/distributed-learning.md) · [Full course](../../courses/distributed-learning/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/distributed-learning.md)
