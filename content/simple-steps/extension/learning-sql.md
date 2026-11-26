<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-sql.md

PURPOSE:
Give learners an additional practical case for Learning SQL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep an earlier step using a savepoint

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local scratch row has value 5. A transaction needs to keep a validated change to 8 while trying another change to 11.

1. Within one transaction, update the row to 8, set a named savepoint, and update it to 11.
2. Roll back to the savepoint, commit the transaction, and query the scratch row.

**Check your result.** The final query returns 8. The earlier change is committed and the trial change is undone.

[Step-by-step course guide](../course-guides/learning-sql.md) · [Full course](../../courses/learning-sql/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-sql.md)
