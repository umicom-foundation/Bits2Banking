<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/mysql-c23-ledger.md

PURPOSE:
Provide practical first steps and a result to check for MySQL Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# MySQL Ledger Practice in C23

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Write the sample signed amounts in cents and total them on paper. [Store signed cents in a training ledger](../../courses/mysql-c23-ledger/lessons/01-store-ledger-values-as-integers.html)
2. Trace where the query is prepared and where a supplied value is bound in the C example. [Bind a MySQL query parameter from C](../../courses/mysql-c23-ledger/lessons/02-bind-a-parameter-from-c.html)
3. Use the successful and failed fetch examples. For each case, record when a new total may be published. [Qualify every fetch before publishing a ledger total](../../courses/mysql-c23-ledger/lessons/03-qualify-fetches-before-publishing.html)

**Check your result.** A failed fetch leaves the previously checked total available, and the refusal is visible in the report.

[Continue in the full course](../../courses/mysql-c23-ledger/index.html) · [All course guides](index.md)
