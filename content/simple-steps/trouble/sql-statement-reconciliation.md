<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/sql-statement-reconciliation.md

PURPOSE:
Give learners an additional practical case for SQL Statement Reconciliation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find why a row multiplies in a join

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One fictional account has two movements. A practice comparison joins each movement to two summary rows.

1. Count the number of output rows before adding the amounts. Find which key repeats in the joined input.
2. Build one summary row per account using the lesson’s aggregation pattern. Recheck the joined count.

**Check your result.** The duplicated summary produces four rows when joining movements directly. A unique account summary removes that duplication.

[Step-by-step course guide](../course-guides/sql-statement-reconciliation.md) · [Full course](../../courses/sql-statement-reconciliation/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/sql-statement-reconciliation.md)
