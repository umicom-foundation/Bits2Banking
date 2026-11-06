# Tables, rows and questions

[Course contents](index.md) · [Next: Changes and transactions](02-changes-and-transactions.md)

## What you will learn

A database stores organised information. A table contains rows about one kind of thing; each column describes one property. SQL is a language for asking a database to store, change or retrieve information. Start with a learning catalogue rather than a real bank database.

## Open a disposable workspace

Use the SQLite browser fiddle linked in the reference, or install the SQLite command-line tool from its official site. In a terminal run `sqlite3 :memory:`. The special name creates a temporary database that disappears when that connection closes. A terminal accepts commands typed by you; SQLite then displays its own prompt for SQL. Do not type prompt symbols as part of the commands.

```sql
CREATE TABLE lesson (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  minutes INTEGER NOT NULL CHECK (minutes > 0)
);
INSERT INTO lesson VALUES (1, 'Finding a file', 12);
INSERT INTO lesson VALUES (2, 'Reading a C program', 20);
SELECT title, minutes FROM lesson
WHERE minutes <= 15 ORDER BY id;
```

Enter the statements in order. A semicolon ends a statement. `PRIMARY KEY` gives each row a distinct identity. `TEXT` stores characters. `NOT NULL` requires a value; it does not reject an empty string. `CHECK` rejects a row whose duration is not positive. Single quotes delimit text values.

## Read the result

The question asks for two columns from lessons taking at most 15 minutes. Expect one row: `Finding a file`, `12`. `WHERE` selects rows; `ORDER BY` makes their order explicit. A database does not promise the same visible order just because rows were inserted in that order.

```text
Stored rows: 1 (12 minutes), 2 (20 minutes)
Condition:  minutes <= 15
Result:    row 1 only
```

## Exercise and answer

Insert a third row called `Opening a project` lasting 15 minutes. Use id 3, then repeat the query. Expect rows 1 and 3. Try inserting another row with id 3: the key rejects it. Use a fresh id for a genuinely new lesson, rather than removing the constraint.

## Connect this to Umicom

The linked Framework architecture lesson distinguishes shared data services from application screens. Later, a screen can request catalogue rows through such a service. This exercise creates a separate toy table and does not change an Umicom database. If the prompt waits for more input, look for a missing quote or semicolon. Leave SQLite with `.quit` when finished.

[Review the prerequisite course](../../../courses/learning-computer-architecture/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/framework-and-finance/framework-boundaries/lessons/shared-services.html). Path: `content/courses/framework-and-finance/framework-boundaries/lessons/shared-services.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.sqlite.org/quickstart.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-sql/lessons/01-tables-rows-and-questions.html).

[Course contents](index.md) · [Next: Changes and transactions](02-changes-and-transactions.md)

Sammy Hegab · Umicom Foundation · Original learning material.
