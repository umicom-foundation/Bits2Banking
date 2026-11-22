<!--
Umicom Bits2Banking
File: content/lessons/04-web/practical-web-and-data-foundations/06-compare-sql-database-dialects.md

PURPOSE:
Compare SQL database dialects in the Bits2Banking web and data course.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom Foundation">
</picture>

# Compare SQL database dialects

[Course contents](index.md) · [Previous lesson · Add posted cents in a spreadsheet](05-add-posted-cents-in-a-spreadsheet.md) · [Next course · SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)

Use a common SQL query to total the statement, then identify two different ways a database can assign record IDs.

## Move from cells to rows

A database keeps information in an organised form. A relational database uses named tables, with fields in columns and entries in rows. SQL is the language used here to create a table and ask it a question. Some parts of SQL are shared between database programs. A dialect is the particular set of rules and spelling used by one database program.

If you have a local database and know how to use a scratch database, run the following block there once. The lesson works on paper too. Read the statement one line at a time and point to the records it includes.

## Use one common statement query

```sql
-- Create a practice table with explicit IDs for these fictional records.
CREATE TABLE practice_statement (
    id INTEGER PRIMARY KEY,
    status VARCHAR(7) NOT NULL,
    cents INTEGER NOT NULL
);

INSERT INTO practice_statement (id, status, cents) VALUES
    (1, 'posted', 2600),
    (2, 'posted', -850),
    (3, 'pending', 500);

-- Match the spreadsheet condition and give an empty match a zero total.
SELECT COALESCE(SUM(cents), 0) AS posted_cents
FROM practice_statement
WHERE status = 'posted';
```

`WHERE` keeps the rows that match. `SUM(cents)` adds their values. `COALESCE` chooses the first value that is present. If no row matches and the sum is absent, it uses zero. The result is one column named `posted_cents` with value `1750`.

## Compare how two database programs choose IDs

The example above gives every row an ID. A fresh practice table can also ask the database to assign it. PostgreSQL has identity columns. MySQL uses `AUTO_INCREMENT` for this example. Both declare the ID as a primary key so it identifies each row uniquely. Read the statements side by side and find the words that belong to each database.

```sql
-- PostgreSQL form for a new practice table.
CREATE TABLE postgres_practice (
    id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    cents INTEGER NOT NULL
);
```

```sql
-- MySQL form for a new practice table.
CREATE TABLE mysql_practice (
    id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
    cents INTEGER NOT NULL
);
```

The database-specific part is how a new ID is created. The filter and sum are the same idea in both databases. Use the statement that matches the database where you create the table.

## Try it and connect to Umicom

Predict the result if the last query looks for `pending`. Check for `500`. Try a status that none of your rows have. `SUM` alone would be missing, and the `COALESCE` call returns `0`. If the database says the practice table already exists, move to a new scratch database or ask the existing practice table the question without recreating it.

An Umicom Bank or TMS report can check the same few records through a spreadsheet and a query. Write down which database version ran the query and whether it was the portable calculation or the optional ID example. That makes a comparison useful to someone reviewing a data change.

- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [PostgreSQL identity columns](https://www.postgresql.org/docs/current/ddl-identity-columns.html)
- [MySQL AUTO_INCREMENT](https://dev.mysql.com/doc/refman/8.4/en/example-auto-increment.html)

[Open the HTML edition](../../../courses/practical-web-and-data-foundations/lessons/06-compare-sql-database-dialects.html)
