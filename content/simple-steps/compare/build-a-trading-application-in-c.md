<!--
Umicom Bits2Banking
File: content/simple-steps/compare/build-a-trading-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Trading Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two refusals with identical starting cash

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper buyer has 100 cents and no units. A first book has one offer at 120 and a limit of 110. A second book has the same offer and a limit of 120. Each request asks for one unit.

1. Follow buy_once in the two books and mark whether the offer is eligible by price.
2. Compare the reason returned in each trace. Record buyer cash, units and Fill output for both.

**Check your result.** The first trace returns BOOK_NO_TRADE. The second returns BOOK_CASH_LIMIT. Both preserve 100 cents, zero units and the caller's original Fill.

[Step-by-step course guide](../course-guides/build-a-trading-application-in-c.md) · [Full course](../../courses/build-a-trading-application-in-c/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/build-a-trading-application-in-c.md)
