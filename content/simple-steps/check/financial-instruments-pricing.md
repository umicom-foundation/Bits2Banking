<!--
Umicom Bits2Banking
File: content/simple-steps/check/financial-instruments-pricing.md

PURPOSE:
Give learners an additional practical case for Financial Instruments Pricing Using C, C++ and Java.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a present-value output and a refused date

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A source-level Framework fixture calls present value for a future amount of zero and rate 0.05. The two trials use tenor 100 and tenor -1. The caller's output starts at 17 in both.

1. Follow discount_curve.c to identify which input reaches discount arithmetic and where the invalid tenor returns.
2. Record the status and output value expected for each call.

**Check your result.** Tenor 100 returns UMI_STATUS_OK and publishes 0. Tenor -1 returns UMI_STATUS_INVALID_ARGUMENT and preserves 17.

[Step-by-step course guide](../course-guides/financial-instruments-pricing.md) · [Full course](../../courses/financial-instruments-pricing/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/financial-instruments-pricing.md)
