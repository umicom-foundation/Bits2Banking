<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/05-read-filter-and-order-rows.md

PURPOSE:
Explain the lesson: Read, filter and order rows.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read, filter and order rows

A query describes the rows and columns you want to see. It does not need to describe a loop that visits each disk record.

## Prepare the data

Start SQLite as described in the course-progress README, then read schema.sql and seed.sql. This creates three courses and four progress records. No earlier lesson's database is required.

## Select columns

```sql
SELECT title, lesson_count FROM course ORDER BY course_id;
```

SELECT names the output columns. FROM names the source table. ORDER BY makes the displayed order explicit. Without ORDER BY, do not rely on a particular order just because several runs happened to match.

## Filter rows

Read read.sql. Its second query keeps rows whose completed value is greater than zero, then sorts largest completion counts first. Additional keys settle ties consistently.

Predict the result before running it: completed values should be 10, 3 and 2. The row with zero completed lessons is deliberately absent from this query; it has not been deleted.

## Understand an empty result

The third query asks for course 99, which is absent from the seed. Returning no rows is a valid result. It differs from a syntax error and from a row whose value is NULL.

## Exercise

Change a copy of the second query to show only course 1 and order by learner_id. Expect two rows, for Learner A and Learner B. Keep both the query and your expected result in your notes.

If you see “no such table”, check that setup ran in this same connection. Each new `:memory:` connection starts empty.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/read.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-create-a-small-course-database.md) · [Next lesson](06-connect-related-rows-with-joins.md)

