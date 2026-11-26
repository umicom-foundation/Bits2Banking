<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-java.md

PURPOSE:
Give learners an additional practical case for Learning Java.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare equal amounts with different scales

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two training amounts are represented by BigDecimal strings 2.0 and 2.00. A comparison using equals rejects them as different.

1. Trace both the amount and its scale using the decimal comparison lesson. Check equals on the two values.
2. Use compareTo for the numeric comparison. Add 2.10 as a third value to check that a different amount remains distinct.

**Check your result.** equals returns false for the two scales. compareTo returns 0 for 2.0 against 2.00 and a positive value for 2.10 against 2.0.

[Step-by-step course guide](../course-guides/learning-java.md) · [Full course](../../courses/learning-java/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-java.md)
