<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-sql.md

PURPOSE:
Give learners an additional practical case for Learning SQL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check if a stale edit keeps a newer saved value

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch table stores venue ID 4 with status Ready and version 3. A checked edit must match the version it previously read.

1. In the first case, update the row while expecting version 3 and write status Reviewed with version 4. Read the changed-row count.
2. Reset to the stated initial fixture. Try the same edit with expected version 2, then read the row and affected-row count.

**Check your result.** The current-version case changes one row to Reviewed and version 4. The stale case changes zero rows and leaves Ready and version 3.

[Step-by-step course guide](../course-guides/learning-sql.md) · [Full course](../../courses/learning-sql/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-sql.md)
