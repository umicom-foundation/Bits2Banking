<!--
Umicom Bits2Banking
File: content/simple-steps/extension/fpml-for-treasury.md

PURPOSE:
Give learners an additional practical case for FpML for Treasury and Trade Confirmation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Exercise the edge of a training rate band

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A valid synthetic SwapTerms record has the course's Cedar currency and direction fields. Compare candidate fixed rates of 4,999, 5,000 and 5,001 basis points.

1. Keep party IDs and notional fixed. Trace each candidate through admit from lowest to highest rate.
2. Record which candidates replace the accepted record and inspect the saved rate after the last check.

**Check your result.** 4,999 and 5,000 are accepted. 5,001 is refused and the accepted record still reports the rate 5,000.

[Step-by-step course guide](../course-guides/fpml-for-treasury.md) · [Full course](../../courses/fpml-for-treasury/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/fpml-for-treasury.md)
