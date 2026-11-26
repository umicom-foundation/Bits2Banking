<!--
Umicom Bits2Banking
File: content/simple-steps/extension/build-a-trading-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Trading Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Select a second offer after the first is depleted

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper book has cash of 700 cents and owns zero units. Ask 20 offers 2 units at 140, and ask 22 offers one at 150. The buyer requests two units with a 150-cent limit on each of two calls.

1. Follow buy_once for the first call and update cash, position and ask 20's remaining units.
2. Trace the second call from that updated snapshot. Note the ask chosen and the cash left after the fill.

**Check your result.** The first fill is two units on ask 20 for 280 cents and depletes it. The second is one unit on ask 22 for 150 cents. The buyer has 3 units and 270 cents.

[Step-by-step course guide](../course-guides/build-a-trading-application-in-c.md) · [Full course](../../courses/build-a-trading-application-in-c/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/build-a-trading-application-in-c.md)
