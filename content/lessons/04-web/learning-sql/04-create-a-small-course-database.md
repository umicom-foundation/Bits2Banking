<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/04-create-a-small-course-database.md

PURPOSE:
Explain the lesson: Create a small course database.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Create a small course database

A database keeps related facts in an organised form. In this project the facts are courses, learners and their recorded progress. A table describes one kind of fact; a row is one instance.

## Set up the exercise

Open the course-progress lab README and follow its PowerShell or Bash instructions. Use the temporary database named `:memory:`. Nothing in this exercise requires an application account or personal data.

At the SQLite prompt, read schema.sql and seed.sql. A semicolon ends an SQL statement; a dot command such as `.read schema.sql` belongs to the shell and does not need one.

## Read the schema

```sql
course_id INTEGER PRIMARY KEY,
title TEXT NOT NULL UNIQUE
```

The ID identifies a course even if its title changes. INTEGER describes whole-number values. PRIMARY KEY makes the ID the row's key. NOT NULL requires a value. UNIQUE prevents two course rows from using the same title.

Do not use a row's display position as its identity: sorting changes positions.

## Draw the relationships

```text
learner --< progress >-- course
```

One learner may have progress in several courses. One course may have progress from several learners. The progress table connects the two.

## Exercise and recovery

Inspect the schema with `.schema`. Identify which columns reject an absent value and which use a range check. Why can Learner C exist without a progress row?

If SQLite reports “table already exists”, you probably repeated the setup in the same session. Close the temporary database and start again; do not add deletion commands to a real application database.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/schema.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](05-read-filter-and-order-rows.md)


[Previous: Read a transaction as one unit of work](03-read-a-transaction-as-a-unit.md)
