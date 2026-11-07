<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/03-read-a-transaction-as-a-unit.md

PURPOSE:
  Present "Read a transaction as one unit of work" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a transaction as one unit of work

A database transaction groups changes that should succeed together. This lab reads the existing SQLite task example and then designs a small two-table exercise without adding a new Python script.

Source to open: `Umicom-Bits2Banking/content/labs/sqlite-tasks/tasks_db.py`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\labs\sqlite-tasks\tasks_db.py'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/labs/sqlite-tasks/tasks_db.py'
```

## Understand the idea

A table stores rows with named columns. A transaction gives a group of statements a commit or rollback boundary. A parameter placeholder separates a value from SQL syntax. These ideas solve different problems: parameters protect the meaning of a query, while a transaction controls which changes become committed together.

```text
BEGIN → insert task → insert activity → COMMIT
                         ↓ error
                      ROLLBACK → neither new row remains
```

## Work through the lab

1. Read the database example. Find the connection, CREATE TABLE statement and places where values are supplied separately from SQL text.
2. On paper draw a tasks table with one task and an activity table recording its creation. Give both rows the same task identifier.
3. Trace a transaction that inserts the task and then the activity record. At the second insert, imagine a constraint failure. Mark the point where the application should roll back the entire unit.
4. Write expected observations for two cases: both inserts succeed, or the second fails. Use a disposable database and the course's existing SQL setup when trying the exercise.

## Expected result

The proposed two-table transaction should publish both rows or neither. This is an exercise specification; the current task example does not automatically supply the new activity table.

## If the result differs

If one row remains after a failure, inspect autocommit and the actual transaction boundary. A try block alone is not a database transaction. If apostrophes break input, inspect parameter binding instead of constructing SQL by string concatenation.

## Explain it yourself

Does a successful commit prove the task's title and author were correct?

<details>
<summary>Worked explanation</summary>

No. Commit records accepted changes. Business validation and authorisation must happen at their own boundaries, and tests must distinguish those rules from transaction atomicity.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-sql/lessons/03-read-a-transaction-as-a-unit.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-changes-and-transactions.md) · [Course contents](index.md)


[Next: Create a small course database](04-create-a-small-course-database.md)
