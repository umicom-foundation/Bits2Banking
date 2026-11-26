<!--
Umicom Bits2Banking
File: content/simple-steps/practice/mysql-c23-ledger.md

PURPOSE:
Give learners an additional practical case for MySQL Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check an amount before using it in a total

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two posted fixture rows have signed amounts of 800 and −350 cents.

1. Calculate the expected posted total on paper. Then follow the prepared statement example for the same posted rows.
2. Trace the fetch result next to each row. Consider what the reader should report if the second fetch fails.

**Check your result.** Both accepted rows give 450 cents. A failed fetch is a separate result and cannot establish a complete new total.

[Step-by-step course guide](../course-guides/mysql-c23-ledger.md) · [Full course](../../courses/mysql-c23-ledger/index.html) · [Practice by course](index.md)
