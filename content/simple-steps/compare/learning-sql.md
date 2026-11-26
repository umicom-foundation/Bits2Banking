<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-sql.md

PURPOSE:
Give learners an additional practical case for Learning SQL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a row count and a count of known values

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper SQL table has three rows whose optional actual_minutes column contains 10, NULL, and 15.

1. Use the aggregate lesson to trace COUNT(*) for these rows. Then trace COUNT(actual_minutes).
2. Write which rows contribute to each count and match both values to the report headings All rows and Known durations.

**Check your result.** All rows is 3. Known durations is 2 because NULL adds no value to the column count.

[Step-by-step course guide](../course-guides/learning-sql.md) · [Full course](../../courses/learning-sql/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-sql.md)
