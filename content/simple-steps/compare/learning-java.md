<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-java.md

PURPOSE:
Give learners an additional practical case for Learning Java.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two explicit tie-rounding methods

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A classroom journal needs to show the number 2.345 to two decimal places.

1. Create the value from its string so its decimal representation is exact. Apply HALF_UP at scale 2.
2. Start again from 2.345 and apply HALF_EVEN at scale 2. Compare the first discarded digit and the kept digit in the second calculation.

**Check your result.** HALF_UP gives 2.35. HALF_EVEN gives 2.34 because the tie keeps an even hundredths digit.

[Step-by-step course guide](../course-guides/learning-java.md) · [Full course](../../courses/learning-java/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-java.md)
