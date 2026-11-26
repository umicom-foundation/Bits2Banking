<!--
Umicom Bits2Banking
File: content/simple-steps/check/mysql-c23-ledger.md

PURPOSE:
Give learners an additional practical case for MySQL Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a complete fetch and one interrupted fetch

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The first fictional query returns two admitted rows. A second fetch sequence fails after the first row.

1. Write the sum expected for the complete result and the state that should be retained if a fetch fails.
2. Use the course’s local execution model to compare publication after both outcomes.

**Check your result.** Only a complete admitted fetch produces a new total. The failed fetch retains the earlier result reference.

[Step-by-step course guide](../course-guides/mysql-c23-ledger.md) · [Full course](../../courses/mysql-c23-ledger/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/mysql-c23-ledger.md)
