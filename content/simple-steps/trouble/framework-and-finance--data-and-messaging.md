<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/framework-and-finance--data-and-messaging.md

PURPOSE:
Give learners an additional practical case for Learning Data and Messaging Services.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a change committed on only one side

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local transaction trace starts with A = 900 and B = 100. The process stops after drafting a 250-unit debit and before it drafts the credit.

1. Calculate the intended committed balances and their sum.
2. Trace the same stop within the transaction boundary in Keep related changes together. Write the balances after rollback.

**Check your result.** The intended commit gives A = 650 and B = 350. The interrupted transaction rolls back to A = 900 and B = 100.

[Step-by-step course guide](../course-guides/framework-and-finance--data-and-messaging.md) · [Full course](../../courses/framework-and-finance/data-and-messaging/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/framework-and-finance--data-and-messaging.md)
