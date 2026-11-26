<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-sql.md

PURPOSE:
Provide practical first steps and a result to check for Learning SQL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning SQL

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Load the course-progress `schema.sql` and `seed.sql` into the training SQLite database in the same session. [Create a small course database](../../courses/learning-sql/lessons/04-create-a-small-course-database.html)
2. Run the second query in `read.sql`. Check the completed counts after filtering and ordering. [Read, filter and order rows](../../courses/learning-sql/lessons/05-read-filter-and-order-rows.html)
3. Change a copy of that query to select course 1 and order by `learner_id`. Run it against the same data. [Read, filter and order rows](../../courses/learning-sql/lessons/05-read-filter-and-order-rows.html)

**Check your result.** The original query returns 10, 3 and 2 completed. The changed query returns Learner A and Learner B.

[Continue in the full course](../../courses/learning-sql/index.html) · [All course guides](index.md)
