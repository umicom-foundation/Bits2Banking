<!--
Umicom Bits2Banking
File: content/simple-steps/extension/framework-and-finance--data-and-messaging.md

PURPOSE:
Give learners an additional practical case for Learning Data and Messaging Services.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect two envelopes to one practice request

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A synthetic payment PAY-27 reached the receiving exercise service. The response timed out. A second envelope has a new transport ID E2 and the same logical request ID PAY-27, correlation C8 and payload as envelope E1.

1. Write an envelope row for E1 and E2, keeping transport ID, correlation ID and business request ID in separate columns.
2. Use the stored PAY-27 receipt for the second envelope. Count logical operations and delivered envelopes separately.

**Check your result.** The trace contains two envelopes E1 and E2 under correlation C8, one request PAY-27 and one applied operation. E2 uses the saved receipt.

[Step-by-step course guide](../course-guides/framework-and-finance--data-and-messaging.md) · [Full course](../../courses/framework-and-finance/data-and-messaging/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/framework-and-finance--data-and-messaging.md)
