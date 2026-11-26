<!--
Umicom Bits2Banking
File: content/simple-steps/compare/framework-and-finance--data-and-messaging.md

PURPOSE:
Give learners an additional practical case for Learning Data and Messaging Services.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare an envelope key and an audit label

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A receiver stores transfers A6 and A7 as separate logical operations while both messages carry correlation C9 because they belong to the same investigation.

1. Write two envelope rows with request identity and correlation in separate columns.
2. Compare the count produced by grouping on the request identity with the count produced by grouping on the audit correlation.

**Check your result.** There are two logical request groups, A6 and A7, and one audit correlation group, C9.

[Step-by-step course guide](../course-guides/framework-and-finance--data-and-messaging.md) · [Full course](../../courses/framework-and-finance/data-and-messaging/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/framework-and-finance--data-and-messaging.md)
