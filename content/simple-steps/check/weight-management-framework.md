<!--
Umicom Bits2Banking
File: content/simple-steps/check/weight-management-framework.md

PURPOSE:
Give learners an additional practical case for Build a weight-management companion with Umicom Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a precise and over-precise decimal entry

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Test `74.025` and `74.0259` kilograms in the course’s bounded form.

1. Write the expected integer result for the valid precision. Count the fractional digits in the second input before converting it.
2. Trace both through the parser and check whether the last accepted value is preserved after the refused input.

**Check your result.** 74.025 represents 74,025 grams. 74.0259 exceeds the supported precision and does not replace the accepted value.

[Step-by-step course guide](../course-guides/weight-management-framework.md) · [Full course](../../courses/weight-management-framework/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/weight-management-framework.md)
