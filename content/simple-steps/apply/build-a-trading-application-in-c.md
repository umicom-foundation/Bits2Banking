<!--
Umicom Bits2Banking
File: content/simple-steps/apply/build-a-trading-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Trading Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a read-only order timeline

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Paper order C12 asks to buy five units. Event F8 fills two at 110 cents, F9 fills one at 105 cents, and event C8 cancels the remainder.

1. Create an event table with order ID, event ID, outcome, cash effect and remaining quantity. Process each event in order.
2. Write a one-line order summary that a console could show to a user. Keep execution details available in the timeline.

**Check your result.** The two fills add three units at a total paper cost of 325 cents. The cancel closes two remaining units, and open quantity becomes zero.

[Step-by-step course guide](../course-guides/build-a-trading-application-in-c.md) · [Full course](../../courses/build-a-trading-application-in-c/index.html) · [Small projects by course](index.md) · [First practice case](../practice/build-a-trading-application-in-c.md)
