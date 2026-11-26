<!--
Umicom Bits2Banking
File: content/simple-steps/extension/mysql-c23-ledger.md

PURPOSE:
Give learners an additional practical case for MySQL Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a bound filter at its boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional ledger has posted amounts of 100, 200 and 300 cents. Choose a minimum amount of 200.

1. Predict which rows meet an inclusive minimum. Bind the filter with the method shown in the course.
2. Increase the bound to 201 in the same local exercise. Compare both matched counts and totals.

**Check your result.** The inclusive bound at 200 gives two rows and 500 cents. At 201 it gives one row and 300 cents.

[Step-by-step course guide](../course-guides/mysql-c23-ledger.md) · [Full course](../../courses/mysql-c23-ledger/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/mysql-c23-ledger.md)
