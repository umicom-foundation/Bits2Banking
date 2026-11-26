<!--
Umicom Bits2Banking
File: content/simple-steps/check/oracle-database-c23-ledger.md

PURPOSE:
Give learners an additional practical case for Oracle Database Ledger Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check which value a named bind receives

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice query filters by `:entry_id`. The fixture has two rows, with IDs 17 and 23 and different amounts.

1. Predict the one row returned for each ID. Follow the course line that supplies the integer to `:entry_id`.
2. Run or trace the query with 17, then with 23. Keep the SQL text unchanged and record both returned IDs.

**Check your result.** The first case returns 17 and the second returns 23. The parameter changes while the query text remains identical.

[Step-by-step course guide](../course-guides/oracle-database-c23-ledger.md) · [Full course](../../courses/oracle-database-c23-ledger/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/oracle-database-c23-ledger.md)
