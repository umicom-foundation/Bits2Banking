<!--
Umicom Bits2Banking
File: content/simple-steps/extension/swift-payment-messages.md

PURPOSE:
Give learners an additional practical case for Swift Payment Messages and ISO 20022.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep two amounts separate during review

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fake payment instruction lists 800 cents. A separate synthetic report says fees are 25 cents.

1. Write a line for the instructed amount and another for the report’s fee field. Keep the ID and currency on both rows.
2. Follow the full course’s status review and state which field would need explicit authority before changing the instruction amount.

**Check your result.** The instruction still records 800 cents. The fee is a separate observation of 25 cents.

[Step-by-step course guide](../course-guides/swift-payment-messages.md) · [Full course](../../courses/swift-payment-messages/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/swift-payment-messages.md)
