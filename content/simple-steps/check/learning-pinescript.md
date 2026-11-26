<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-pinescript.md

PURPOSE:
Give learners an additional practical case for Learning Pine Script.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check whether a value crossed a reference from below

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two synthetic traces end at a confirmed value of 6 and use a reference of 5. Their preceding closes are 4 and 7.

1. Use the history lesson to write a two-bar rule requiring the preceding close below 5 and the current close above 5.
2. Check both traces against both parts of the rule. Verify the same current value alone does not settle the result.

**Check your result.** The first trace marks a crossing. The second shows no crossing because its earlier value was already above 5.

[Step-by-step course guide](../course-guides/learning-pinescript.md) · [Full course](../../courses/learning-pinescript/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-pinescript.md)
