# Changes and transactions

[Course contents](index.md) · [Previous: Tables, rows and questions](01-tables-rows-and-questions.md)

## What you will learn

A transaction groups database changes so that they can be accepted together or undone together. Continue in the temporary database from lesson 1. Re-enter its setup if you closed SQLite. We will practise on lesson lengths, not account balances.

## Inspect before changing

First run `SELECT * FROM lesson ORDER BY id;`. The star requests every column. Confirm that id 1 exists with 12 minutes. Then enter these statements individually:

```sql
BEGIN;
UPDATE lesson SET minutes = 18 WHERE id = 1;
SELECT id, minutes FROM lesson WHERE id = 1;
ROLLBACK;
SELECT id, minutes FROM lesson WHERE id = 1;
```

`BEGIN` starts the transaction. `UPDATE` changes an existing row. Its `WHERE` clause is essential: without it, every row would receive the new duration. The first result should be 18. `ROLLBACK` abandons the transaction's changes, so the final result should be 12. A query inside the transaction can see your provisional change before it is accepted.

## Accept one intended edit

Repeat the same sequence but replace `ROLLBACK` with `COMMIT`. The final result is now 18. Commit makes the edit part of this database's state. Because this database is in memory, it still disappears on closing. A committed change in a file-backed database normally survives reopening; it is not a substitute for backups.

```text
BEGIN -> proposed edit -> inspect -> COMMIT: retain
                              -> ROLLBACK: undo
```

## Exercise and answer

How would you change only the lesson named `Reading a C program`? Look up its id, then use `WHERE id = 2`. Titles can change or repeat; the primary key is the clearer identity. Before committing, inspect the selected row and the full table. A transaction cannot decide whether your chosen id was correct.

## From SQL text to application code

An application should bind user values to prepared statements rather than joining text into SQL. A prepared statement separates the question's structure from its data. We study the C binding API later; there is no input-concatenating example to copy here. Framework owns reusable data rules so Bank, Trader and other clients need not invent their own storage policies.

If `BEGIN` reports an existing transaction, finish that transaction deliberately before starting another. If a constraint rejects an edit, inspect the error and choose to roll back; do not assume every error automatically undid every earlier statement.

[Review the prerequisite course](../../../courses/learning-computer-architecture/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/framework-and-finance/framework-boundaries/lessons/shared-services.html). Path: `content/courses/framework-and-finance/framework-boundaries/lessons/shared-services.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.sqlite.org/quickstart.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-sql/lessons/02-changes-and-transactions.html).

[Course contents](index.md) · [Previous: Tables, rows and questions](01-tables-rows-and-questions.md)

Sammy Hegab · Umicom Foundation · Original learning material.
