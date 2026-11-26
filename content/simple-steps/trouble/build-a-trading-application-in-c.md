<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/build-a-trading-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Trading Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Ignore an empty offer when selecting a price

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper buy requests 2 units with a 150-cent limit. Sequence 11 has zero units at 140 cents and sequence 12 has two units at 150 cents.

1. Use the checks in Find an eligible offer by price and order. Cross out any candidate that cannot supply a unit.
2. Apply the limit to the remaining offer and compute the fill cost for the chosen quantity.

**Check your result.** Sequence 12 supplies 2 units at 150 cents. The paper fill costs 300 cents.

[Step-by-step course guide](../course-guides/build-a-trading-application-in-c.md) · [Full course](../../courses/build-a-trading-application-in-c/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/build-a-trading-application-in-c.md)
