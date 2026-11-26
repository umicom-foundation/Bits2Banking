<!--
Umicom Bits2Banking
File: content/simple-steps/check/safer-c-programming.md

PURPOSE:
Give learners an additional practical case for Safer C Programming.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check exact capacity and one byte short

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A C input needs six bytes including its terminator. The available capacities are 6 and 5.

1. Trace both bounds before the write. Write the expected status for each case.
2. Use the guarded exercise to compare the new destination after the accepted case and the retained state after refusal.

**Check your result.** Capacity 6 fits exactly. Capacity 5 refuses and leaves the earlier accepted data available.

[Step-by-step course guide](../course-guides/safer-c-programming.md) · [Full course](../../courses/safer-c-programming/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/safer-c-programming.md)
