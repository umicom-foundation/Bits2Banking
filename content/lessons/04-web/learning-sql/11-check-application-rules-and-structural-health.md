<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/11-check-application-rules-and-structural-health.md

PURPOSE:
Explain the lesson: Check application rules and structural health.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check application rules and structural health

A database can be structurally readable while containing values that do not make sense for an application. Integrity therefore has several layers.

## Prepare

Load the lab schema and seed in SQLite. Read integrity.sql and inspect its three operations.

Quick-check is a structural diagnostic. The foreign-key check looks for broken relationships. The final SELECT looks for completion counts greater than the related course length.

Expected seed observations are `ok`, then no foreign-key rows, then no application-rule rows.

## Find the missing business rule

The progress CHECK restricts completed to 0 through 200. It does not compare the value with another table's lesson_count.

In the temporary session, begin a transaction and set Learner A's Learning C progress to 11. The table accepts that bounded value, but the final SELECT reports it because the course has ten lessons. Roll back the experiment.

## Relate the checks to Framework

Framework's sqlite.h explicitly distinguishes its structural quick-check report from full foreign-key or application-record integrity. Calling one health function does not establish all domain rules.

An application service should validate its own cross-record rule when admitting a change and retain useful diagnostics when examining existing records.

## Exercise

Write three separate headings in your lab notes: storage structure, relationships and application meaning. Put each observed result under the correct heading.

Run checks.sql on a fresh seed with `.bail on`. Its temporary CHECK table turns false expectations into errors. Reaching the final message only counts when no earlier command failed.

## Limit

These exercises do not test simultaneous writers, backups or migration recovery. Keep those as distinct qualification work rather than inferring them from a successful query.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/integrity.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-diagnose-a-constraint-failure.md)

