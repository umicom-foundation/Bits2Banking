<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/10-diagnose-a-constraint-failure.md

PURPOSE:
Explain the lesson: Diagnose a constraint failure.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Diagnose a constraint failure

A constraint is a rule checked by the database. It protects a relationship even when a caller forgets to check it first.

## Prepare an intentional failure

Create the temporary lab database and read schema.sql and seed.sql. Use interactive mode with `.bail off` for this lesson so you can inspect the result after the deliberate error in constraints.sql.

The file enables foreign-key checking and attempts to insert progress for learner 99. That learner does not exist.

## Identify the rejected relationship

The progress table requires learner_id to reference an existing learner row. The expected observation is a foreign-key error. The subsequent count should still be four.

Enabling foreign keys is a connection setting in SQLite; configure it before beginning the work that needs it. The [SQLite foreign-key guide](https://www.sqlite.org/foreignkeys.html) explains this setting and relationship rules.

## Separate the rules

A foreign key checks existence of a related row. NOT NULL checks that a value is present. CHECK checks a stated expression. The composite primary key prevents two progress rows for the same learner and course.

Each answers a different question; one cannot stand in for all the others.

## Exercise

In the disposable session, try a negative completion count and then a duplicate learner/course pair. Name the violated rule before reading the diagnostic.

Do not “fix” a rejected value by disabling all constraints. Correct the input or explicitly redesign the rule.

## Expected error versus regression

The intentional failure file is separate from checks.sql. A passing verification run should not silently accept unexpected errors just because this course also teaches error handling.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/constraints.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-use-savepoints-for-a-local-experiment.md) · [Next lesson](11-check-application-rules-and-structural-health.md)

