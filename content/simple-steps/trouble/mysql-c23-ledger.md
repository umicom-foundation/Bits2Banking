<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/mysql-c23-ledger.md

PURPOSE:
Give learners an additional practical case for MySQL Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a wrong sign in a synthetic ledger

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two accepted rows show 900 cents received and 170 cents paid. A report says 1,070 cents.

1. Write the expected sign for each direction. Compare them with the values returned by the query.
2. Use a corrected local fixture and compare its sum to the report.

**Check your result.** The paid amount is −170 cents. The corrected total is 730 cents.

[Step-by-step course guide](../course-guides/mysql-c23-ledger.md) · [Full course](../../courses/mysql-c23-ledger/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/mysql-c23-ledger.md)
