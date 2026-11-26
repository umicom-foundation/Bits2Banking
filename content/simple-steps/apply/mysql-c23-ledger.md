<!--
Umicom Bits2Banking
File: content/simple-steps/apply/mysql-c23-ledger.md

PURPOSE:
Give learners an additional practical case for MySQL Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Prepare a signed snapshot for review

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A synthetic ledger has `received 500`, `paid 125` and `received 75`, all in cents.

1. Store the directions as signed amounts in course fixture format. Use a bound query to select the three practice records.
2. Collect IDs, signed values and the checked total into a small report. Compare it with a paper sum.

**Check your result.** The report shows 500, −125 and 75. Its total is 450 cents.

[Step-by-step course guide](../course-guides/mysql-c23-ledger.md) · [Full course](../../courses/mysql-c23-ledger/index.html) · [Small projects by course](index.md) · [First practice case](../practice/mysql-c23-ledger.md)
