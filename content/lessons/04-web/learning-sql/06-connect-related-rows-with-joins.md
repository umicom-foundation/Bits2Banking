<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/06-connect-related-rows-with-joins.md

PURPOSE:
Explain the lesson: Connect related rows with joins.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect related rows with joins

An ID is compact but often difficult to read. A join lets a query show the learner's name and course title beside a progress value.

## Prepare

Read schema.sql and seed.sql in a fresh SQLite session, following the lab README. Open joins.sql in a text editor before executing it.

## Follow one row

The first progress row contains learner_id 1, course_id 1 and completed 3. The first JOIN finds learner 1; the second finds course 1. The resulting display row says Learner A, Learning C, 3, 10.

Aliases shorten table names: `progress AS p` lets the query write `p.completed`. The alias does not rename the stored table.

## Compare two questions

An inner JOIN returns matching combinations. Learner C has no progress row, so the first query does not show that learner.

A LEFT JOIN starts from every learner and includes an unmatched row when necessary. In the second query, Learner C appears with a NULL course ID. NULL here means no matching progress record was found; it does not mean course zero.

## Avoid multiplying results accidentally

The ON condition supplies the relationship. Omitting the intended condition can combine unrelated rows and inflate totals. Always trace one example by its keys.

## Exercise

Add the course title to the second query with another LEFT JOIN. Predict five output rows: two for Learner A, two for Learner B and one unmatched learner.

A repeated learner name is not automatically a duplicate defect. In this result, each row represents one enrolment or the absence of one.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/joins.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-read-filter-and-order-rows.md) · [Next lesson](07-summarise-enrolments-with-aggregates.md)

