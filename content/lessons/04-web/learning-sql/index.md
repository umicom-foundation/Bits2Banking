# Learning SQL

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Tables and transactions

Ask questions of rows and treat related changes as one unit.

1. [Tables, rows and questions](01-tables-rows-and-questions.md)
1. [Changes and transactions](02-changes-and-transactions.md)
1. [Read a transaction as one unit of work](03-read-a-transaction-as-a-unit.md)

## Project: a course database

Create a small database, then filter, order, join and summarise its records.

1. [Create a small course database](04-create-a-small-course-database.md)
1. [Read, filter and order rows](05-read-filter-and-order-rows.md)
1. [Connect related rows with joins](06-connect-related-rows-with-joins.md)
1. [Summarise enrolments with aggregates](07-summarise-enrolments-with-aggregates.md)

## Changes and integrity

Practise rollback, savepoints, constraint failures and structural checks.

1. [Change records with rollback](08-change-records-with-rollback.md)
1. [Use savepoints for a local experiment](09-use-savepoints-for-a-local-experiment.md)
1. [Diagnose a constraint failure](10-diagnose-a-constraint-failure.md)
1. [Check application rules and structural health](11-check-application-rules-and-structural-health.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Learning SQL

Store and query a small learning catalogue, then group changes safely.

Understand files and a table of rows and columns. No programming language is required; the first SQL lesson introduces the table.

[Browser course](../../../courses/learning-sql/index.html) · [Choose a subject](../../../start/course-series.md)

## Reading order

1. [Tables, rows and questions](01-tables-rows-and-questions.md)
2. [Changes and transactions](02-changes-and-transactions.md)

## Course outline: later topics

Keys and relationships; joins; parameter binding; transactions and migrations.

Read one topic at a time. The list above links to available lessons; the outline describes further study. Each practical lesson gives its own tool requirements.

## Continue with a practical source study

A database transaction groups changes that should succeed together. This lab reads the existing SQLite task example and then designs a small two-table exercise without adding a new Python script.

- [Read a transaction as one unit of work](03-read-a-transaction-as-a-unit.md)

- [Create a small course database](04-create-a-small-course-database.md)

- [Read, filter and order rows](05-read-filter-and-order-rows.md)

- [Connect related rows with joins](06-connect-related-rows-with-joins.md)

- [Summarise enrolments with aggregates](07-summarise-enrolments-with-aggregates.md)

- [Change records with rollback](08-change-records-with-rollback.md)

- [Use savepoints for a local experiment](09-use-savepoints-for-a-local-experiment.md)

- [Diagnose a constraint failure](10-diagnose-a-constraint-failure.md)

- [Check application rules and structural health](11-check-application-rules-and-structural-health.md)

</details>
