<!--
Umicom Bits2Banking
File: content/simple-steps/check/build-a-trading-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Trading Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a new quote and a duplicate quote identity

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two isolated books start with 500 cents and no owned units. Each has an offer of one unit at 90 and one at 95. The first book uses sequences 15 and 16, the second uses 15 twice. Each buy requests one at a limit of 95.

1. Trace quote validation before choosing the best price. Give the caller's Fill a saved value before each case.
2. Write the returned status, end cash, position and whether the saved Fill changes.

**Check your result.** The first returns BOOK_FILLED with one unit on sequence 15 at 90, cash 410 and position one. The second returns BOOK_INVALID and preserves cash 500, position zero and saved Fill.

[Step-by-step course guide](../course-guides/build-a-trading-application-in-c.md) · [Full course](../../courses/build-a-trading-application-in-c/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/build-a-trading-application-in-c.md)
