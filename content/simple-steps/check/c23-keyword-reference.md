<!--
Umicom Bits2Banking
File: content/simple-steps/check/c23-keyword-reference.md

PURPOSE:
Give learners an additional practical case for C23 Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a copy's qualifier before assigning to it

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A C23 source declares const int rate = 3. One scratch copy initializes typeof(rate) copy = 4 and one uses typeof_unqual(rate) copy = 4. Both then attempt copy = 7.

1. Use Check types and representations to write the declared type of copy in each case.
2. Predict the result of translation and the value that may be displayed after assignment in the accepted version.

**Check your result.** The typeof copy retains const and the assignment needs a diagnostic. The typeof_unqual copy permits assignment and its value becomes 7.

[Step-by-step course guide](../course-guides/c23-keyword-reference.md) · [Full course](../../courses/c23-keyword-reference/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/c23-keyword-reference.md)
