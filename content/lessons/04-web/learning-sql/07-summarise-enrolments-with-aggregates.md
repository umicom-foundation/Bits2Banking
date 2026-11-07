<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/07-summarise-enrolments-with-aggregates.md

PURPOSE:
Explain the lesson: Summarise enrolments with aggregates.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Summarise enrolments with aggregates

An aggregate combines several values into one answer. COUNT counts values, SUM adds them, and GROUP BY defines which rows belong together.

## Begin with the lab data

Open SQLite, read schema.sql and seed.sql, then open summary.sql. The query begins with every course and left-joins its progress rows.

## Work out the answer by hand

Learning C has two enrolments and 13 completed lessons across them. Learning RISC-V has one enrolment with zero completed lessons. Learning HDL has one enrolment with two completed lessons.

The total of completed lessons is an activity total across learners. It is not a percentage and does not mean the course contains 13 lessons.

## Count the right thing

`COUNT(p.learner_id)` counts matched non-NULL learner IDs. For a course with no progress rows, a LEFT JOIN still produces an unmatched display row. Counting every joined row with COUNT(*) would count that row too.

`COALESCE(SUM(p.completed), 0)` chooses zero when the sum is NULL. It makes the reporting policy explicit.

## Exercise

In the temporary database, insert a fourth course with no progress. Run summary.sql again. Expect enrolments zero and completed_lessons zero for that course.

Then compare it with Learning RISC-V: both have zero completed lessons, but one has an enrolment and the other does not.

## Recovery

If totals are larger than expected, inspect the underlying joined rows before adding DISTINCT. DISTINCT can hide a faulty relationship while leaving the underlying question unanswered.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/summary.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-connect-related-rows-with-joins.md) · [Next lesson](08-change-records-with-rollback.md)

