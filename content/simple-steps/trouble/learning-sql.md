<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-sql.md

PURPOSE:
Give learners an additional practical case for Learning SQL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep both writes within one transaction

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A disposable transaction exercise inserts a fictional attendance row. The following totals update fails a local constraint.

1. Trace the order of BEGIN, the insert, the refused update and ROLLBACK. Mark where a premature commit would accept only the first change.
2. Keep both writes within one transaction and inspect the practice data after rolling back.

**Check your result.** There is no new attendance row and the previous total remains visible after the rollback.

[Step-by-step course guide](../course-guides/learning-sql.md) · [Full course](../../courses/learning-sql/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-sql.md)
