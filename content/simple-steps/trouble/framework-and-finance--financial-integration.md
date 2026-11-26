<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/framework-and-finance--financial-integration.md

PURPOSE:
Give learners an additional practical case for Learning Financial-System Integration.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a decimal amount exact across the adapter

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A mock inbound record gives amount text 8.05 with currency GBP. A practice mapper saved 8050 minor units.

1. Use the mapping-boundary lesson to split the text into pounds and pence. Write the scale beside the field.
2. Compute 8 × 100 + 5 and replace the incorrect value in your scratch mapping.

**Check your result.** The canonical record holds GBP 805 minor units. Converting it back gives GBP 8.05.

[Step-by-step course guide](../course-guides/framework-and-finance--financial-integration.md) · [Full course](../../courses/framework-and-finance/financial-integration/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/framework-and-finance--financial-integration.md)
